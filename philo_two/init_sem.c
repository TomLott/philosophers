#include "philo_two.h"

int 		ft_init_sem(t_args *ar, t_semafor *semafor)
{
	sem_unlink("fork");
	semafor->fork = sem_open("fork", O_CREAT | O_EXCL, 0755, ar->num / 2 + (ar->num % 2));
	sem_unlink("write");
	semafor->sem_wr = sem_open("write", O_CREAT | O_EXCL, 0755, 1);
	sem_unlink("meals_counter");
	semafor->sem_meals_amount = sem_open("meals_counter", O_CREAT | O_EXCL, 0755, 1);
	if (semafor->fork == SEM_FAILED || semafor->sem_meals_amount == SEM_FAILED || semafor->sem_wr == SEM_FAILED)
		return (1);
	return (0);
}

t_philo		*ft_init_thread(t_args *ar, t_semafor *sem)
{
	t_philo *p;
	int		i;

	i = -1;
	p = (t_philo *)malloc(sizeof(t_philo) * ar->num);
	if (!p)
		return (NULL);
	while (++i < ar->num)
	{
		p[i].id = i + 1;
		p[i].sem = sem;
		p[i].ar = ar;
		p[i].start = get_time();
		p[i].last = get_time();
	}
	return (p);
}