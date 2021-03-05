#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct 	s_mutex
{
	pthread_mutex_t *fork;
	pthread_mutex_t mut_wr;
	pthread_mutex_t mut_status;
	pthread_mutex_t mut_meals_amount;

}				t_mutex;

typedef enum {
	ALIVE,
	DEAD,
	FULL
}	t_status;

typedef struct	s_args
{
	int			num;
	int 		die_t;
	long 		eat_t;
	long 		sleep_t;
	long 		need_to_eat;
	int			meals_amount;
	t_status	status;
}				t_args;



typedef struct	s_philo
{
	t_args				*ar;
	t_mutex				*mutex;
	pthread_t 			pthread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	int 				id;
	long 				last;
	long				start;
}				t_philo;



void			*dead_status(void *p);
long			get_time(void);
void 			*full_status(void *p);
void 			ft_eat(t_philo *p);
int				ft_error(char *str);
void 			ft_finish(t_philo *philo, t_mutex *mut);
int 			ft_init(t_args *ar, char **s);
int 			ft_init_mutex(t_args *ar, t_mutex *mut);
t_philo			*ft_init_thr(t_args *ar, t_mutex *mut);
void 			ft_message(char *s, t_philo *philo);
int				ft_start(t_philo *philo, t_args *ar);
size_t			ft_strlen(const char *string);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				stup_atoi(char *num);

#endif
