#include "philo_two.h"

void 	*full_status(void *philo)
{
	int 	i;
	t_philo *p;

	p = (t_philo *)philo;
	while (p[0].ar->status == ALIVE)
	{
		i = -1;
		while (++i < p->ar->num && p[0].ar->status == ALIVE)
		{
			if (p[i].ar->meals_amount == (p->ar->num * p->ar->need_to_eat))
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

void 	*ft_dead(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	while(p[0].ar->status == ALIVE)
	{
		if (get_time() > p[0].last + p[0].ar->die_t)
		{
			ft_message(" is died\n", p);
			p[0].ar->status = DEAD;
		}
	}
	return (NULL);
}

void 	*ft_action(void *philo)
{
	t_philo *p;
	pthread_t status;

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
	int 		flag;
	int 		i;
	pthread_t	run;

	i = -1;
	while (++i < p->ar->num)
	{
		flag = pthread_create(&p[i].thread,NULL, ft_action, &p[i]);
		if (flag)
			return (ft_error("Error: thread creating error\n"));
		usleep(20);
	}
	pthread_create(&run, NULL, full_status, (void *)p);
	pthread_detach(run);
	i = -1;
	while (++i < p->ar->num)
		pthread_join(p[i].thread, NULL);
	return (0);
}