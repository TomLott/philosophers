#include "philo_two.h"

int main(int argc, char **argv)
{
	t_philo 	*ph;
	t_semafor 	sem;
	t_args		ar;
	int 		temp;

	if (argc < 5)
		write(1, "Error: not enough arguments\n", 28);
	else
	{
		temp = ft_init_args(argv, &ar);
	}

}