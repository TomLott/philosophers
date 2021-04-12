/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:33:05 by itollett          #+#    #+#             */
/*   Updated: 2021/03/11 12:33:06 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*full_status(void *philo)
{
	int		i;
	long	limit;
	t_philo	*p;

	p = (t_philo *)philo;
	limit = p->ar->num * p->ar->need_to_eat;
	if (limit < 0)
		limit = 10000000000;
	while (p[0].ar->status == ALIVE)
	{
		i = -1;
		while (++i < p->ar->num && p[0].ar->status == ALIVE)
		{
			if (p[i].ar->meals_amount >= limit)
			{
				p[i].ar->status = FULL;
				sem_wait(p[i].sem->sem_wr);
				write(1, "All philosophers are full\n", 26);
				sem_post(p[i].sem->sem_wr);
			}
		}
	}
	return (NULL);
}

void	*ft_dead(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->ar->status == ALIVE)
	{
		if (get_time() > (p->last + p->ar->die_t) + 1)
		{
			ft_message(" is died\n", p);
			p->ar->status = DEAD;
		}
	}
	return (NULL);
}

void	*ft_action(void *philo)
{
	t_philo		*p;
	pthread_t	status;

	p = (t_philo *)philo;
	pthread_create(&status, NULL, ft_dead, p);
	pthread_detach(status);
	while (p->ar->status == ALIVE)
	{
		ft_eat(p);
		ft_message(" is sleeping\n", p);
		usleep(p->ar->sleep_t);
		ft_message(" is thinking\n", p);
	}
	return (NULL);
}

int		ft_start(t_philo *p)
{
	int			flag;
	int			i;
	pthread_t	run;

	i = -1;
	while (++i < p->ar->num)
	{
		flag = pthread_create(&p[i].thread, NULL, ft_action, &p[i]);
		if (flag)
			return (ft_error("Error: thread creating error\n"));
	}
	pthread_create(&run, NULL, full_status, (void *)p);
	pthread_detach(run);
	i = -1;
	while (++i < p->ar->num)
		pthread_join(p[i].thread, NULL);
	return (0);
}
