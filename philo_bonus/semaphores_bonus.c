/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:19:12 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/19 20:52:30 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_data *data)
{
	sem_unlink("print");
	sem_unlink("forks");
	data->sprint = sem_open("print", O_CREAT, 0600, 1);
	data->sforks = sem_open("forks", O_CREAT, 0600, data->n_phis);
}

void	end_sem(t_data *data)
{
	sem_close(data->sprint);
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
