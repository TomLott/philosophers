/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:32:59 by itollett          #+#    #+#             */
/*   Updated: 2021/03/11 12:33:01 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct	s_semafor
{
	sem_t		*fork;
	sem_t		*sem_wr;
	sem_t		*sem_meals_amount;
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
	long		die_t;
	long		eat_t;
	long		sleep_t;
	long		need_to_eat;
	long		meals_amount;
}				t_args;

typedef struct	s_philo
{
	pthread_t	thread;
	t_semafor	*sem;
	t_args		*ar;
	int			id;
	long		start;
	long		last;
}				t_philo;

long			get_time(void);
void			ft_eat(t_philo *p);
int				ft_error(char *str);
int				ft_init_args(char **argv, t_args *ar);
int				ft_init_sem(t_args *ar, t_semafor *semafor);
t_philo			*ft_init_thread(t_args *ar, t_semafor *sem);
void			ft_message(char *s, t_philo *philo);
int				ft_start(t_philo *p);
size_t			ft_strlen(const char *string);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
long			stup_atoi(char *num);

#endif
