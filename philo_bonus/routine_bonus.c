/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:05:16 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/19 20:54:02 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_routine(t_philo *phi)
{
	if (pthread_create(&phi->teat, NULL, &monitor, phi))
		ft_exit("error creatng thread", phi, 2);
	pthread_detach(phi->teat);
	if (phi->id > phi->data->n_phis / 2)
		ft_usleep(1);
	while (24)
	{
		try_to_eat(phi);
		try_to_sleep_and_think(phi);
	}
	return (0);
}

int	one_philo_die(t_data *data)
{
	int	time;

	data->t_start = ft_time();
	printf("%i %s\n", 0, "1 has taken a fork");
	ft_usleep(data->t_die);
	time = ft_time() - data->t_start;
	printf("%i %s\n", time, "1 has died");
	ft_clean(data, -1);
	return (1);
}

void	try_to_eat(t_philo *phi)
{
	sem_wait(phi->data->sforks);
	sem_wait(phi->data->sforks);
	phi->t_die = ft_time() - phi->data->t_start + phi->data->t_die;
	ft_print("has taken a fork", phi, 0);
	ft_print("has taken a fork", phi, 0);
	ft_print("is eating", phi, 0);
	ft_usleep(phi->data->t_eat);
	sem_post(phi->data->sforks);
	sem_post(phi->data->sforks);
	if (--phi->left_eat == 0)
		exit (0);
}

void	*monitor(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (24)
	{
		if (phi->t_die <= (ft_time() - phi->data->t_start))
			ft_exit("has died", phi, 1);
		ft_usleep(1);
	}
	return ((void *)0);
}

void	try_to_sleep_and_think(t_philo *phi)
{
	ft_print("is sleeping", phi, 0);
	ft_usleep(phi->data->t_sleep);
	ft_print("is thinking", phi, 0);
}
