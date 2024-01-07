/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:11:54 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/07 18:11:01 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *message)
{
	printf("Introduce right %s\n", message);
	return (1);
}

int	ft_atoi_philo(char *str, int *arg)
{
	int	i;
	int	x;

	if (!str)
	{
		*arg = -1;
		return (0);
	}
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

int	parse_args(t_data *data, char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi_philo(argv[i++], &data->n_phis))
		return (print_error("number of philosophers"));
	if (ft_atoi_philo(argv[i++], &data->t_die))
		return (print_error("time to die"));
	if (ft_atoi_philo(argv[i++], &data->t_eat))
		return (print_error("time to eat"));
	if (ft_atoi_philo(argv[i++], &data->t_sleep))
		return (print_error("time to sleep"));
	if (ft_atoi_philo(argv[i], &data->t_must_eat))
		return (print_error("times each philosopher must eat"));
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
	
}