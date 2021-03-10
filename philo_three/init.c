#include "philo_three.h"

void 	ft_finish(t_philo *p)
{
	sem_close(p->sem->fork);
	sem_close(p->sem->sem_wr);
	sem_close(p->sem->sem_meals_amount);
	sem_close(p->sem->each_status);
	sem_close(p->sem->global_status);
	sem_close(p->sem->dead);
	sem_unlink("fork");
	sem_unlink("dead");
	sem_unlink("sem_wr");
	sem_unlink("meals_amount");
	sem_unlink("each_status");
	sem_unlink("global_status");
}

int 	ft_check_arg(char **s)
{
	int i;
	int j;

	i = 0;
	if (!s || !s[0])
		return (1);
	while (s[++i])
	{
		j = 0;
		while (s[i][j])
			if (s[i][j] < '0' || s[i][j++] > '9')
				return (1);
	}
	return (0);
}

int		ft_init_args(char **argv, t_args *ar)
{
	int	flag;

	flag = ft_check_arg(argv);
	if (flag)
		return (ft_error("Error: positive numeric arguments expected.\n"));
	ar->meals_amount = 0;
	ar->status = ALIVE;
	ar->num = (int)stup_atoi(argv[1]);
	if (ar->num < 2)
		return (1);
	ar->die_t = stup_atoi(argv[2]);
	ar->eat_t = stup_atoi(argv[3]) * 1000;
	ar->sleep_t = stup_atoi(argv[4]) * 1000;
	if (!argv[5])
		ar->need_to_eat = -1;
	else
		ar->need_to_eat = (int)stup_atoi(argv[5]);
	return (0);
}

int 	ft_init_sem(t_args *ar, t_sem *sem)
{
	sem_unlink("fork");
	sem_unlink("sem_wr");
	sem_unlink("meals_amount");
	sem_unlink("each_status");
	sem_unlink("global_status");
	sem_unlink("dead");
	sem->dead = sem_open("dead", O_CREAT | O_EXCL, 0755, 1);
	sem->fork = sem_open("fork", O_CREAT | O_EXCL, 0755, ar->num / 2);
	sem->sem_wr = sem_open("sem_wr", O_CREAT | O_EXCL, 0755, 1);
	sem->sem_meals_amount = sem_open("meals_amount", O_CREAT | O_EXCL, 0755, 0);
	sem->each_status = sem_open("each_status", O_CREAT | O_EXCL, 0755, 0);
	sem->global_status = sem_open("global_status", O_CREAT | O_EXCL, 0755, 0);
	if (sem->fork == SEM_FAILED || sem->sem_meals_amount == SEM_FAILED
	|| sem->sem_wr == SEM_FAILED || sem->each_status == SEM_FAILED
	|| sem->global_status == SEM_FAILED || sem->dead == SEM_FAILED)
		return (1);
	return (0);
}

void	*ft_last_init(t_args *ar, t_sem *sem, t_philo *p)
{
	p->pid = (pid_t *)malloc(sizeof(pid_t) * ar->num);
	if (!p->pid)
		return (NULL);
	p->ar = ar;
	p->sem = sem;
	p->start = get_time();
	p->last = get_time();
	return (NULL);
}