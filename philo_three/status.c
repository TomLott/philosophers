#include "philo_three.h"


void 	*ft_status_child(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	sem_wait(p->sem->each_status);
	p->ar->status = DEAD;
	sem_post(p->sem->each_status);

	return (NULL);
}

void 	*ft_status_parent(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	sem_wait(p->sem->global_status);
	p->ar->status = DEAD;
	return (NULL);
}

void 	*ft_full(void *philo)
{
	int 	res;
	t_philo *p;

	p = (t_philo *)philo;
	res = 0;
	while (p->ar->status == ALIVE)
	{
		sem_wait(p->sem->sem_meals_amount);
		res++;
		if (res == p->ar->need_to_eat * p->ar->num)
		{
			p->ar->status = FULL;
			sem_post(p->sem->each_status);
			sem_post(p->sem->global_status);
			//usleep(100);
			sem_wait(p->sem->sem_wr);
			printf("All philosophers are full\n");
			sem_post(p->sem->sem_wr);
			return (NULL);
		}
	}
	return (NULL);
}

void 	*ft_dead(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	while (p->ar->status == ALIVE)
	{
		if (get_time() > (p->last + p->ar->die_t))
		{
			sem_wait(p->sem->dead);
			ft_message(" died\n", p);
			p->ar->status = DEAD;
			sem_post(p->sem->global_status);
			sem_post(p->sem->each_status);
			sem_post(p->sem->sem_meals_amount);
			sem_close(p->sem->dead);
			//sem_post(p->sem->dead);
			//sem_post(p->sem->sem_wr);
			//exit(1);
			return (NULL);
		}
	}
	return (NULL);
}
