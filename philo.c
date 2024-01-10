/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:11:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/10 19:21:57 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_phis)
	{
		if (pthread_create(&data->threads[i], NULL, &routine, &data->phi[i]))
			return (i);
	}
	return (-1);
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
		pthread_mutex_init(&data->phi[i].mr_fork, NULL);
		pthread_mutex_init(&data->phi[i].m_t_die, NULL);
		if (i == 0)
			data->phi[i].ml_fork = &data->phi[data->n_phis - 1].mr_fork;
		else
			data->phi[i].ml_fork = &data->phi[i - 1].mr_fork;
	}
}

int	init_all(t_data *data)
{
	int	check;

	data->end = 0;
	data->eaten = 0;
	data->phi = malloc(sizeof(t_philo) * data->n_phis);
	if (!data->phi)
		return (error("Allocation failed", data, -1));
	pthread_mutex_init(&data->mprint, NULL);
	pthread_mutex_init(&data->mstart, NULL);
	pthread_mutex_init(&data->mend, NULL);
	pthread_mutex_init(&data->meaten, NULL);
	data->threads = malloc(sizeof(pthread_t) * (data->n_phis + 1));
	if (!data->threads)
		return (error("Allocation failed", data, -1));
	memset(data->threads, 0, sizeof(pthread_t) * (data->n_phis + 1));
	pthread_mutex_lock(&data->mstart);
	init_philos(data);
	check = init_threads(data);
	if (check != -1)
		return (error("Error when creating threads", data, check));
//	gettimeofday(&data->time, NULL);
	data->t_start = ft_time();
	pthread_mutex_unlock(&data->mstart);
	return (0);
}

int	parse_args(t_data *data, char **argv)
{
	int	i;

	i = 1;
	data->n_must_eat = -1;
	data->phi = NULL;
	data->threads = NULL;
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

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
	monitor(&data);
	i = -1;
	while (++i < data.n_phis)
	{
		if (pthread_join(data.threads[i], NULL))
			return(error("Error when joining threads", &data, data.n_phis));
	}
	ft_clean(&data, data.n_phis);
	return (0);
}