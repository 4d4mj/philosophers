/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 02:40:46 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/24 23:55:11 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define ARG "Invalid arguments"
# define FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

struct	s_data;

typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			t1;
	int					id;
	int					eat_cont;
	int					status;
	int					eating;
	unsigned long		time_to_die;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t			*tid;
	int					philo_num;
	int					meals_nb;
	int					dead;
	int					finished;
	t_philo				*philos;
	unsigned long		death_time;
	unsigned long		eat_time;
	unsigned long		sleep_time;
	unsigned long		start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}	t_data;

//	utils
long			ft_atoi(const char *str);
int				ft_error(char *str, t_data *data);
int				ft_strcmp(char *s1, char *s2);
void			messages(char *str, t_philo *philo);
void			ft_exit(t_data *data, int des_lock);
int				one_philo(t_data *data);

//	time
unsigned long	get_time(void);
int				ft_usleep(unsigned long time);

//	init
int				init(t_data *data, char **argv, int argc);
int				init_thread(t_data *data);

//	checker
int				check_argv(char **argv);

//	actions
void			eat(t_philo *philo);

//	threads
void			*routine(void *philo_pointer);
void			*death_checker(void *philo_pointer);
void			*end_checker(void *data_pointer);

#endif
