#ifndef PHILO_TWO_PHILO_TWO_H
#define PHILO_TWO_PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_semafor
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*sem_wr;
	pthread_mutex_t	*sem_meals_amount;
}				t_semafor;

typedef enum
{
	ALIVE,
	DEAD,
	FULL
}	t_status;

typedef struct	s_args
{
	t_status	status;
	int			num;
	int 		die_t;
	int 		eat_t;
	long 		sleep_t;
	long 		need_to_eat;
	long		meals_amount;
}				t_args;

typedef struct	s_philo
{
	pthread_t 	thread;
	t_semafor	*sem;
	t_args		*ar;
	int			id;
	long 		start;
	long 		last;
}				t_philo;

long			get_time(void);
int 			ft_error(char *str);
int				ft_init_args(char **argv, t_args *ar);
void			ft_message(char *s, t_philo *philo);
size_t			ft_strlen(const char *string);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
long			stup_atoi(char *num);

#endif //PHILO_TWO_PHILO_TWO_H
