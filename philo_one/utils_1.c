#include "philo_one.h"

long	get_time(void)
{
	long			temp;
	struct timeval	time;

	gettimeofday(&time, NULL);
	temp = time.tv_sec * 1000L + time.tv_usec / 1000L;
	return (temp);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int 	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int		if_not(char *num)
{
	ft_putstr_fd(num, 2);
	ft_putstr_fd(" is out of range\n", 2);
	exit(1);
}

int		stup_atoi(char *num)
{
	int					i;
	unsigned long long	res;
	int					len;
	int					sign;
	int					fl;

	res = 0;
	sign = 1;
	i = 0;
	fl = 0;
	len = ft_strlen(num);
	if (len > 20)
		fl = 1;
	if ((num[i] == '-' || num[i] == '+') && ++i)
		(num[i - 1] == '-') ? (sign = -1) : 1;
	while (num[i] >= '0' && num[i] <= '9')
		res = res * 10 + (num[i++] - 48);
	if ((len >= 19 && res > 9223372036854775807 && sign == 1) || \
	((res / 10 >= (unsigned long long)(922337203685477580) \
	&& res % 10 > 8) && sign == -1 && len >= 20))
		fl = 1;
	if (fl != 1 && i == len && i != 0)
		return (sign * res);
	return  (if_not(num));
}