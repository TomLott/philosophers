#ifndef PHILO_THREE_H
#define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>


typedef enum
{
	DEAD,
	FULL,
	ALIVE
}		t_status;

typedef struct 	s_sem
{
	sem_t		*fork;
	sem_t		*sem_wr;
	sem_t		*sem_meals_amount;
	sem_t		*each_status;
	sem_t		*global_status;
}				t_sem;

typedef struct	s_args
{
	int 		num;
	int 		meals_amount;
	t_status 	status;
	long 		die_t;
	long 		eat_t;
	long 		sleep_t;
	int 		need_to_eat;
}				t_args;

typedef struct	s_philo
{
	pid_t		*pid;
	t_args		*ar;
	t_sem 		*sem;
	long 		start;
	long 		last;
	long 		finish;
	int 		id;


}				t_philo;

int 		ft_error(char *str);
void		ft_putstr_fd(char *s, int fd);
long		get_time(void);
long		stup_atoi(char *num);
void		ft_message(char *s, t_philo *philo);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_strlen(const char *string);
int			ft_init_args(char **argv, t_args *ar);
int 		ft_check_arg(char **s);
int 		ft_init_sem(t_args *ar, t_sem *sem);
void		*ft_last_init(t_args *ar, t_sem *sem, t_philo *p);
void 		*ft_dead(void *philo);
void 		*ft_full(void *);
void 		*ft_status_child(void *philo);
void 		*ft_status_parent(void *philo);
void 		ft_finish(t_philo *p);
int			ft_strcmp(const char *s1, const char *s2);

#endif