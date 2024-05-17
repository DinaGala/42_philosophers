/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:05:17 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/17 17:51:04 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi_philo(char *str, int *arg)
{
	int	i;
	int	x;

	if (!str)
		return (1);
	i = 0;
	x = 0;
	while (str[i] && ((str[i] > 8 && str[i] < 14) || str[i] == 32))
		i++;
	while (str[i] && str[i] > 47 && str[i] < 58)
		x = x * 10 + (str[i++] - 48);
	if (str[i])
		return (1);
	*arg = x;
	return (0);
}

/* If flag = -1 - we don't kill the processes, else - the amount of processes 
to kill */
int	error(char *message, t_data *data, int flag)
{
	if (message)
		printf("%s\n", message);
	if (data && data->phi)
		ft_clean(data, flag);
	if (!message)
		return (0);
	return (1);
}

void	ft_clean(t_data *data, int flag)
{
	int	i;

	i = -1;
	if (!data || !data->phi)
		return ;
	free(data->phi);
	if (!data->pids)
		return ;
	end_sem(data);
	while (++i < flag)
		kill(data->pids[i], SIGKILL);
	free(data->pids);
}

void	ft_print(char *message, t_philo *phi, int flag)
{
	int	time;
	int	end;

	sem_wait(&phi->data->sprint);
	time = ft_time() - phi->data->t_start;
///	pthread_mutex_lock(&phi->data->mend);
//	end = phi->data->end;
//	pthread_mutex_unlock(&phi->data->mend);
	if (!end || flag)
		printf("%i %i %s\n", time, phi->id, message);
	sem_post(&phi->data->sprint);
}
