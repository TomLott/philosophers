#include "philo_one.h"

void 	*full_status(void *p)
{
	t_philo	*philo;
	int 	limit;
	int 	i;

	philo = (t_philo *)p;
	limit = philo[0].ar->num * philo[0].ar->need_to_eat;
	if (limit <= 0)
		limit = 1000000000;
	while (philo[0].ar->status == ALIVE)
	{
		i = 0;
		while (i < philo->ar->num && philo->ar->status == ALIVE)
		{
			if (philo[i].ar->meals_amount >= limit)
			{
				pthread_mutex_lock(&philo[i].mutex->mut_wr);
				ft_putstr_fd("All philosophers are full.\n", 1);
				pthread_mutex_lock(&philo->mutex->mut_status);
				philo[i].ar->status = FULL;
				pthread_mutex_unlock(&philo->mutex->mut_status);
				pthread_mutex_unlock(&philo[i].mutex->mut_wr);
			}
			i++;
		}
	}
	return (NULL);
}


void 	*dead_status(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	while (philo->ar->status == ALIVE)
	{
		if (get_time() > (philo->last + philo->ar->die_t) + 1)
		{
			ft_message(" dead\n", philo);
			pthread_mutex_lock(&philo->mutex->mut_status);
			philo->ar->status = DEAD;
			pthread_mutex_unlock(&philo->mutex->mut_status);
			break;
		}
	}
	return (NULL);
}