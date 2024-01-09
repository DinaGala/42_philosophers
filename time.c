/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:41:38 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/09 19:17:37 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int millisec)
{
	int	end;

	end = ft_time() + millisec;
	while (ft_time() < end)
		usleep(200);
}

void	ft_print(char *message, t_philo *phi)
{
	int	time;
	int	end;

	time = ft_time() - phi->data->t_start;
	pthread_mutex_lock(&phi->data->mfinish);
	end = phi->data->end;
	pthread_mutex_unlock(&phi->data->mfinish);
	if (end)
		return ;
	pthread_mutex_lock(&phi->data->mprint);
	printf("%i %i %s\n", time, phi->id, message);
	pthread_mutex_unlock(&phi->data->mprint);
}
