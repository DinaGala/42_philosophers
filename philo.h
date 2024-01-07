/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:36:05 by nzhuzhle          #+#    #+#             */
/*   Updated: 2024/01/07 17:35:27 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{

}	t_philo;

typedef struct s_data
{
	int	n_phis;
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	t_must_eat;
	t_philo	*phi;
}	t_data;

#endif