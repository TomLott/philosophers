#include "philo_two.h"

void	ft_message(char *s, t_philo *philo)
{
	sem_wait(philo->sem->sem_wr);
	if (s && philo && philo->ar->status == ALIVE)
	{
		ft_putnbr_fd((int)(get_time() - philo->start), 1);
		write(1, " ms id ", 7);
		ft_putnbr_fd(philo->id, 1);
		write(1, s, ft_strlen(s));
	}
	sem_post(philo->sem->sem_wr);
}

void	ft_putnbr_fd(int n, int fd)
{
	int temp;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		temp = 45;
		write(fd, &temp, 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10)
	{
		temp = n + 48;
		write(fd, &temp, 1);
	}
	else
	{
		temp = n % 10 + 48;
		ft_putnbr_fd(n / 10, fd);
		write(fd, &temp, 1);
	}
}

size_t	ft_strlen(const char *string)
{
	char	*temp;
	size_t	i;

	temp = (char *)string;
	i = 0;
	while (temp[i] != '\0')
		i++;
	return (i);
}
