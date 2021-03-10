#include "philo_two.h"

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
		ar->need_to_eat = stup_atoi(argv[5]);
	return (0);
}


