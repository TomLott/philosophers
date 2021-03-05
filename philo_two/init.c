#include "philo_two.h"

int 	ft_check_arg(char *s)
{
	int i;

	i = -1;
	if (!s)
		return (1);
	while (s[++i])
		if (s[i] < '0' || s[i] > '9')
			return (1);
	return (0);
}

int		ft_init_args(char **argv, t_args *ar)
{
	int i;
	int	flag;

	i = 0;
	while (argv[++i])
	{
		flag = ft_check_arg(argv[i]);
		if (flag)
			return (ft_error("Error: ")
	}
}


