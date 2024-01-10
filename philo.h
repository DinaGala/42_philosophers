/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:36:05 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/10 19:22:18 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				left_eat;
	int				eating;
	int				t_die;
	pthread_mutex_t	mr_fork;
	pthread_mutex_t	*ml_fork;
	pthread_mutex_t	m_t_die;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n_phis;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	int				t_start;
	int				end;
	int				eaten;
	t_philo			*phi;
	pthread_t		*threads;
	struct timeval	time; //?
	pthread_mutex_t	mprint;
	pthread_mutex_t	mstart;
	pthread_mutex_t	mend;
	pthread_mutex_t	meaten;
}	t_data;

/*********** philo.c - main and initialization *************/
int		parse_args(t_data *data, char **argv);
int		init_all(t_data *data);
void	init_philos(t_data *data);
int		init_threads(t_data *data);
/****************************************/

/*********** routine.c - main *************/
void	*routine(void *arg);
void	*one_routine(t_philo *phi);
void	many_routine(t_philo *phi);
void	monitor(t_data *data);
int		monitor_eaten(t_data *data);
/****************************************/

/*********** time.c - main ***************/
int		ft_time(void);
void	ft_usleep(int millisec);
void	ft_print(char *message, t_philo *phi);

/*********** utils.c - additional functions *************/
void	ft_putstr(char *str);
int		ft_strlen(char *str);
int		ft_atoi_philo(char *str, int *arg);
int		error(char *message, t_data *data, int flag);
void	ft_clean(t_data *data, int flag);
/****************************************/

#endif