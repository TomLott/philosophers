#include "philo_three.h"

void 	ft_eat(t_philo *p)
{
	sem_wait(p->sem->fork);
	ft_message(" has taken forks\n", p);
	ft_message(" is eating\n", p);
	p->last = get_time();
	usleep(p->ar->eat_t);
	p->last = get_time();
	p->ar->meals_amount++;
	sem_post(p->sem->fork);
	sem_post(p->sem->sem_meals_amount);
}

int 	ft_action(t_philo *p)
{
	pthread_t		status;
	pthread_t 		dead_status;

	pthread_create(&dead_status, NULL, &ft_dead, (void *)p);
	pthread_detach(dead_status);
	pthread_create(&status, NULL, &ft_status_child, (void *)p);
	pthread_detach(status);
	while (p->ar->status == ALIVE)
	{
		ft_eat(p);
		ft_message(" is sleeping\n", p);
		usleep(p->ar->sleep_t);
		ft_message(" is thinking\n", p);
	}
	return (0);
}

void 	ft_start(t_philo *p, t_args *ar)
{
	int 			i;
	pthread_t		status;
	pthread_t		run;

	i = -1;
	while (++i < ar->num)
	{
		p->pid[i] = fork();

		if (p->pid[i] == 0)
		{
			p->id = i + 1;
			ft_action(p);
			exit(0);
		}
		else if (p->pid[i] == -1)
			return ;
	}
	pthread_create(&run, NULL, ft_full, p);
	pthread_create(&status, NULL, ft_status_parent, (void *)p);
	pthread_join(run, NULL);
	pthread_join(status, NULL);
	i = -1;
	waitpid(-1, NULL, 0);
	while (++i < ar->num)
		kill(p->pid[i], SIGTERM);
	free(p->pid);
}

int		main(int argc, char **argv)
{
	t_philo philo;
	t_args	ar;
	t_sem 	sem;
	int 	temp;

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
		ft_last_init(&ar, &sem, &philo);
		ft_start(&philo, &ar);
		ft_finish(&philo);

	}
	return (0);
}
