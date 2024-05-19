/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:36:05 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/19 20:53:20 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h> 
# include <semaphore.h>
# include <signal.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				left_eat;
	int				eating;
	int				t_die;
	pthread_t		teat;
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
	pid_t			*pids;
	sem_t			*sprint;
	sem_t			*sforks;
}	t_data;

/*********** philo.c - main and initialization *************/
int		parse_args(t_data *data, char **argv);
int		init_all(t_data *data, int check);
void	init_philos(t_data *data);
int		init_threads(t_data *data);
/****************************************/

/*********** routine.c - main *************/
int		philo_routine(t_philo *phi);
int		one_philo_die(t_data *data);
void	try_to_eat(t_philo *phi);
void	*monitor(void	*arg);
void	try_to_sleep_and_think(t_philo *phi);
/****************************************/

/*********** time.c - main ***************/
int		ft_time(void);
void	ft_usleep(int millisec);

/*********** utils.c - additional functions *************/
int		ft_atoi_philo(char *str, int *arg);
int		error(char *message, t_data *data, int flag);
void	ft_clean(t_data *data, int flag);
void	ft_print(char *message, t_philo *phi, int flag);
int		ft_exit(char *message, t_philo *phi, int stat);
/****************************************/

/*********** semaphores.c - sem functions *************/
void	init_sem(t_data *data);
void	end_sem(t_data *data);
void	wait_everyone(t_data *data);
/****************************************/

#endif