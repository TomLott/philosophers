/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:38:11 by itollett          #+#    #+#             */
/*   Updated: 2021/03/11 13:38:12 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_actions(void *p)
{
	t_philo		*philo;
	pthread_t	status;

	philo = (t_philo *)p;
	pthread_create(&status, NULL, dead_status, (void *)philo);
	pthread_detach(status);
	if (philo->id % 2 != 0)
		usleep(philo->ar->eat_t / 2);
	while (philo->ar->status == ALIVE)
	{
		ft_eat(philo);
		ft_message(" is sleeping\n", philo);
		usleep(philo->ar->sleep_t);
		ft_message(" is thinking\n", philo);
	}
	return (NULL);
}

int		ft_start(t_philo *philo, t_args *ar)
{
	int			i;
	pthread_t	run;
	int			fl;

	i = -1;
	while (++i < ar->num)
	{
		fl = pthread_create(&philo[i].pthread, NULL, ft_actions, &philo[i]);
		if (fl < 0)
			return (ft_error("Error: something went wrong "
			"during thread creation.\n"));
	}
	pthread_create(&run, NULL, &full_status, (void *)philo);
	pthread_detach(run);
	i = -1;
	while (++i < philo->ar->num)
		pthread_join(philo[i].pthread, NULL);
	return (0);
}

void	ft_finish(t_philo *philo, t_mutex *mut)
{
	int i;

	i = -1;
	while (++i < philo->ar->num)
		pthread_mutex_destroy(&(mut->fork)[i]);
	pthread_mutex_destroy(&mut->mut_status);
	pthread_mutex_destroy(&mut->mut_wr);
	pthread_mutex_destroy(&mut->mut_meals_amount);
	free(philo);
	free(mut->fork);
}
