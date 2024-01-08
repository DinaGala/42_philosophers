/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:11:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/08 22:04:02 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_data *data)
{
	data->phi = malloc(sizeof(t_philo) * (data->n_phis + 1));
	if (!data->phi)
		return (print_error("Allocation failed", data, -1));
	memset(data->phi, NULL, sizeof(t_philo) * (data->n_phis + 1));
	pthread_mutex_init(&data->mprint, NULL);
	pthread_mutex_init(&data->mstart, NULL);
	pthread_mutex_init(&data->mdied, NULL);
	pthread_mutex_init(&data->mfinish, NULL);
	data->threads = malloc(sizeof(t_philo) * (data->n_phis + 1));
	if (!data->threads)
		return (print_error("Allocation failed", data, -1));
	pthread_mutex_lock(&data->mstart);
	init_philos(data);
	init_threads(data);
	gettimeofday(&data->time, NULL);
	pthread_mutex_unlock(&data->mstart);
}

int	parse_args(t_data *data, char **argv)
{
	int	i;

	i = 1;
	data->n_must_eat = -1;
	data->phi = NULL;
	data->threads = NULL;
	if (ft_atoi_philo(argv[i++], &data->n_phis))
		return (print_error("Introduce right number of philosophers", data, -1));
	if (ft_atoi_philo(argv[i++], &data->t_die))
		return (print_error("Introduce right time to die", data, -1));
	if (ft_atoi_philo(argv[i++], &data->t_eat))
		return (print_error("Introduce right time to eat", data, -1));
	if (ft_atoi_philo(argv[i++], &data->t_sleep))
		return (print_error("Introduce right time to sleep", data, -1));
	if (argv[i] && ft_atoi_philo(argv[i], &data->n_must_eat))
		return (print_error\
		("Introduce right times each philosopher must eat", data, -1));
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
	if (init_all(&data))
		return (1);
// monitor
// join loop	
	ft_clean(&data, data.n_phis);
	return (0);
}