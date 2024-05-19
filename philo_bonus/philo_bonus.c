/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:11:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/05/19 20:54:47 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_pids(t_data *data)
{
	int		i;
	pid_t	pid;

	i = -1;
	data->t_start = ft_time();
	while (++i < data->n_phis)
	{
		pid = fork();
		if (pid < 0)
			return (i);
		if (pid == 0)
			philo_routine(&data->phi[i]);
		else
			data->pids[i] = pid;
	}
	return (data->n_phis);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_phis)
	{
		data->phi[i].id = i + 1;
		data->phi[i].left_eat = data->n_must_eat;
		data->phi[i].eating = 0;
		data->phi[i].t_die = data->t_die;
		data->phi[i].data = data;
	}
}

int	init_all(t_data *data, int check)
{
	data->phi = malloc(sizeof(t_philo) * data->n_phis);
	if (!data->phi)
		return (error("Allocation failed", data, -1));
	data->pids = malloc(sizeof(pid_t) * data->n_phis);
	if (!data->pids)
		return (error("Allocation failed", data, -1));
	init_sem(data);
	init_philos(data);
	check = init_pids(data);
	if (check != data->n_phis)
		return (error("Error when creating pids", data, check));
	return (0);
}

int	parse_args(t_data *data, char **argv)
{
	int	i;

	i = 1;
	data->n_must_eat = -1;
	data->phi = NULL;
	data->pids = NULL;
	if (ft_atoi_philo(argv[i++], &data->n_phis))
		return (error("Introduce right number of philosophers", data, -1));
	if (ft_atoi_philo(argv[i++], &data->t_die))
		return (error("Introduce right time to die", data, -1));
	if (ft_atoi_philo(argv[i++], &data->t_eat))
		return (error("Introduce right time to eat", data, -1));
	if (ft_atoi_philo(argv[i++], &data->t_sleep))
		return (error("Introduce right time to sleep", data, -1));
	if (argv[i] && ft_atoi_philo(argv[i], &data->n_must_eat))
		return (error("Introduce right times \
		each philosopher must eat", data, -1));
	if (data->n_must_eat == 0)
		return (1);
	if (data->n_phis == 1)
		return (one_philo_die(data));
	data->end = 0;
	data->eaten = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Introduce 4 or 5 arguments: 1. number of philosophers;\n");
		printf("2. time to die; 3. time to eat; 4. time to sleep;\n");
		printf("5. number of times each philosopher must eat (optional);\n");
		return (1);
	}
	if (parse_args(&data, argv))
		return (1);
	if (init_all(&data, -1))
		return (1);
	wait_everyone(&data);
	ft_clean(&data, data.n_phis);
	return (0);
}
