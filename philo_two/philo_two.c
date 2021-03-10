#include "philo_two.h"

void 	ft_finish(t_semafor *sem)
{
	sem_close(sem->sem_wr);
	sem_close(sem->sem_meals_amount);
	sem_close(sem->fork);
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("meals_counter");
}

void	ft_eat(t_philo *p)
{
	sem_wait(p->sem->fork);
	ft_message(" has taken a forks\n", p);
	ft_message(" is eating\n", p);
	//p->last = get_time();
	usleep(p->ar->eat_t);
	p->last = get_time();
	sem_wait(p->sem->sem_meals_amount);
	p->ar->meals_amount++;
	sem_post(p->sem->sem_meals_amount);
	sem_post(p->sem->fork);
}

int		main(int argc, char **argv)
{
	t_philo 	*philo;
	t_semafor 	sem;
	t_args		ar;
	int 		temp;

	if (argc < 5)
		return(ft_error("Error: not enough arguments\n"));
	else
	{
		temp = ft_init_args(argv, &ar);
		if (temp)
			return (1);
		temp = ft_init_sem(&ar, &sem);
		if (temp)
			return (1);
		philo = ft_init_thread(&ar, &sem);
		if (!philo)
			return (1);
		ft_start(philo);
		ft_finish(&sem);
	}
	return (0);
}