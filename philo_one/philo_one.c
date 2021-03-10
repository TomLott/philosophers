#include "philo_one.h"

void	ft_eat(t_philo *p)
{
	//long temp;

	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(p->r_fork);
	ft_message(" has taken a forks\n", p);
	ft_message(" is eating\n", p);
	usleep(p->ar->eat_t);
	p->last = get_time();
	//temp = get_time();
	//p->last = (temp + p->last) / 2;
	pthread_mutex_lock(&p->mutex->mut_meals_amount);
	p->ar->meals_amount++;
	pthread_mutex_unlock(&p->mutex->mut_meals_amount);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

int		main(int argc, char **argv)
{
	t_args		ar;
	t_mutex		mutex;
	t_philo		*philo;
	int			temp;

	if (argc < 5)
		return (ft_error("Error: wrong amount of arguments.\n"));
	else
	{
		temp = ft_init(&ar, argv);
		if (temp)
			return (1);
		temp = ft_init_mutex(&ar, &mutex);
		if (temp)
			return (1);
		philo = ft_init_thr(&ar, &mutex);
		ft_start(philo, &ar);
		ft_finish(philo, &mutex);
	}
	return (0);
}
