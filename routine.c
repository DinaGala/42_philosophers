/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:05:16 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/09 19:17:40 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(void *arg)
{
	t_philo	*phi;
	int		end;

	phi = (t_philo *)arg;
	pthread_mutex_lock(&phi->data->mstart);
	pthread_mutex_unlock(&phi->data->mstart);
	if (phi->id % 2 == 0)
		ft_usleep(1);
	if (phi->data->n_phis == 1)
	{
		pthread_mutex_lock(&phi->mr_fork);
		ft_print("has taken a fork", phi);
	}

	

}