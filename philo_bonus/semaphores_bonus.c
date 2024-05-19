/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:19:12 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/19 19:51:56 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_data *data)
{
	int	check;

	check = -1;	
	sem_unlink("start");
//	sem_unlink("end");
//	sem_unlink("eaten");
	sem_unlink("print");
	sem_unlink("forks");
//	data->send = sem_open("end", O_CREAT, 0600, 1);
	data->sstart = sem_open("start", O_CREAT, 0600, 1);
//	data->seaten = sem_open("eaten", O_CREAT, 0600, data->n_phis);
	data->sprint = sem_open("print", O_CREAT, 0600, 1);
	data->sforks = sem_open("forks", O_CREAT, 0600, data->n_phis);
//	sem_wait(data->sstart);
}

void	end_sem(t_data *data)
{
//	sem_close(data->send);
	sem_close(data->sstart);
	sem_close(data->sprint);
//	sem_close(data->seaten);
	sem_close(data->sforks);
}

void	wait_everyone(t_data *data)
{
	int		stat;

	while (data->eaten < data->n_phis)
	{
		if (waitpid (-1, &stat, 0) != -1)
		{
			if (WEXITSTATUS(stat) == 0)
				data->eaten++;
			else
				ft_clean(data, data->n_phis);
		}
	}
	sem_wait(data->sprint);
}