/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:05:16 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/10 19:48:10 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*phi;
	int		end;

	phi = (t_philo *)arg;
	pthread_mutex_lock(&phi->data->mstart);
	pthread_mutex_unlock(&phi->data->mstart);
	if (phi->id % 2 == 0)
		ft_usleep(1);
	if (phi->data->n_must_eat == 0)
		return ((void *)0);
	if (phi->data->n_phis == 1)
		return (one_routine(phi));
	pthread_mutex_lock(&phi->data->mend);
	end = phi->data->end;
	pthread_mutex_unlock(&phi->data->mend);
	while (!end)
	{
		many_routine(phi);
		pthread_mutex_lock(&phi->data->mend);
		end = phi->data->end;
		printf("{ROUT} in routine end: %i\n", end); //erase
		pthread_mutex_unlock(&phi->data->mend);
	}
	return ((void *)0);
}

void	*one_routine(t_philo *phi)
{
	pthread_mutex_lock(&phi->mr_fork);
	ft_print("has taken a fork", phi);
	ft_usleep(phi->t_die);
	ft_print("died", phi);
	phi->data->end = 1;
	pthread_mutex_unlock(&phi->mr_fork);
	return ((void *)0);
}

void	many_routine(t_philo *phi)
{
	pthread_mutex_lock(&phi->mr_fork);
	pthread_mutex_lock(phi->ml_fork);
	ft_print("has taken a fork", phi);
	ft_print("has taken a fork", phi);
	pthread_mutex_lock(&phi->m_t_die);
	phi->t_die = ft_time() - phi->data->t_start + phi->data->t_die;
	phi->eating = 1;
	pthread_mutex_unlock(&phi->m_t_die);
	ft_print("is eating", phi);
	ft_usleep(phi->data->t_eat);
	phi->left_eat--;
	printf("{MANY ROUT} left eat: %i\n", phi->left_eat); //erase
	if (phi->left_eat == 0)
	{
		pthread_mutex_lock(&phi->data->meaten);
		phi->data->eaten++;
		printf("{MANY ROUT} eaten: %i\n", phi->data->eaten); //erase
		pthread_mutex_unlock(&phi->data->meaten);
	}
	phi->eating = 0;
	pthread_mutex_unlock(&phi->mr_fork);
	pthread_mutex_unlock(phi->ml_fork);
	ft_print("is sleeping", phi);
	ft_usleep(phi->data->t_sleep);
	ft_print("is thinking", phi);
}

void	monitor(t_data *data)
{
	int	i;
	int	aux;

	i = -1;
	printf("{MONITOR} ENTERED MONITOR\n"); //erase
	while (++i < data->n_phis)
	{
		printf("{MONITOR} ENTERED MONITOR\n"); //erase
		pthread_mutex_lock(&data->phi[i].m_t_die);
		aux = data->phi[i].t_die;
		pthread_mutex_unlock(&data->phi[i].m_t_die);
		printf("{MONITOR} AFTER FIRST MUTEX\n"); //erase
		if (aux < (ft_time() - data->t_start))
		{
			ft_print("died", &data->phi[i]);
			pthread_mutex_lock(&data->mend);
			data->end = 1;
			pthread_mutex_unlock(&data->mend);
			break ;
		}
		printf("{MONITOR} AFTER SECOND MUTEX\n"); //erase
		if (data->n_must_eat > 0 && monitor_eaten(data))
			break ;
		if (i == data->n_phis)
			i = -1;
	}
}

int	monitor_eaten(t_data *data)
{
	int	eaten;

	pthread_mutex_lock(&data->meaten);
	eaten = data->eaten;
	pthread_mutex_unlock(&data->meaten);
	if (eaten == data->n_phis && data->n_must_eat >= 0)
	{
		pthread_mutex_lock(&data->mend);
		data->end = 1;

		pthread_mutex_unlock(&data->mend);
		return (1);
	}
	return (0);
}