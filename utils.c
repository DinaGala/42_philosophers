/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:05:17 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/08 21:43:31 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_strlen(char *str)
{
	int	cont;

	cont = 0;
	if (!str)
		return (0);
	while (str[cont] != '\0')
		cont++;
	return (cont);
}

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

/* If flag = -1 - we don't detach the threads, else - the amount of threads 
to detach */
int	print_error(char *message, t_data *data, int flag)
{
	if (message)
	{
		ft_putstr(message);
		write(1, "\n", 1);	
	}
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
	while (++i < data->n_phis)
	{
		pthread_mutex_destroy(&data->phi[i].mr_fork);
		pthread_mutex_destroy(&data->phi[i].m_t_die);
	}
	pthread_mutex_destroy(&data->mprint);
	pthread_mutex_destroy(&data->mstart);
	pthread_mutex_destroy(&data->mdied);
	pthread_mutex_destroy(&data->mfinish);
	free(data->phi);
	data->phi = NULL;
	i = -1;
	while (data->threads && ++i < flag)
		pthread_detach(&data->threads[i]);
	if (data->threads)
		free(data->threads);
	data->threads = NULL;
}