/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:36:05 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/17 19:38:53 by nzhuzhle         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h> 
# include <semaphore.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				left_eat;
	int				eating;
	int				t_die;
	t_data			*data;
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
	pid_t		*pids;
	sem_t	sprint;
	sem_t	sstart;
	sem_t	send;
	sem_t	seaten;
	sem_t	sforks;
}	t_data;

/*********** philo.c - main and initialization *************/
int		parse_args(t_data *data, char **argv);
int		init_all(t_data *data);
void	init_philos(t_data *data);
int		init_threads(t_data *data);
/****************************************/

/*********** routine.c - main *************/
int		philo_routine(t_philo *phi);
int		one_philo_die(t_data *data);
void	try_to_eat(t_philo *phi);
void	try_to_sleep(t_philo *phi);
void	think(t_philo *phi);

void	many_routine(t_philo *phi);
void	monitor(t_data *data);
int		monitor_eaten(t_data *data);
/****************************************/

/*********** time.c - main ***************/
int		ft_time(void);
void	ft_usleep(int millisec);

/*********** utils.c - additional functions *************/
int		ft_atoi_philo(char *str, int *arg);
int		error(char *message, t_data *data, int flag);
void	ft_clean(t_data *data, int flag);
void	ft_print(char *message, t_philo *phi, int flag);
/****************************************/

/*********** semaphores.c - sem functions *************/
void	init_sem(t_data *data);
void	end_sem(t_data *data);
/****************************************/

#endif