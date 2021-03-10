#include "philo_one.h"

static int	check_args(char **s)
{
	int		i;
	int 	j;

	i = 1;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] < '0' || s[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			ft_init(t_args *ar, char **s)
{
	int		i;
	int		temp;

	i = 0;
	temp = check_args(s);
	if (temp)
		return (ft_error("Error: positive numeric lksarguments expected.\n"));
	ar->num = stup_atoi(s[1]);
	ar->die_t = stup_atoi(s[2]);
	ar->eat_t = stup_atoi(s[3]) * 1000;
	ar->sleep_t = stup_atoi(s[4]) * 1000;
	ar->meals_amount = 0;
	if (s[5])
		ar->need_to_eat = stup_atoi(s[5]);
	else
		ar->need_to_eat = -1;
	if (ar->num < 2)
		return (ft_error("Error: should be at least 2 philosophers\n"));
	return (0);
}

int 		ft_init_mutex(t_args *ar, t_mutex *mut)
{
	int i;

	i = -1;
	mut->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ar->num);
	if (!mut->fork)
		return (1);
	while (++i < ar->num)
		pthread_mutex_init(&mut->fork[i], NULL);
	pthread_mutex_init(&mut->mut_wr, NULL);
	pthread_mutex_init(&mut->mut_status, NULL);
	pthread_mutex_init(&mut->mut_meals_amount, NULL);
	return (0);
}



t_philo		*ft_init_thr(t_args *ar, t_mutex *mut)
{
	t_philo	*philo;
	int 	i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * ar->num);
	if (!philo)
		return (NULL);
	while (++i < ar->num)
	{
		philo[i].id = i + 1;
		philo[i].ar = ar;
		philo[i].mutex = mut;
		if (i < 1)
			philo[i].r_fork = &mut->fork[ar->num - 1];
		else
			philo[i].r_fork = &mut->fork[i - 1];
		philo[i].l_fork = &mut->fork[i];
		philo[i].start = get_time();
		philo[i].last = get_time();
	}
	return (philo);
}
