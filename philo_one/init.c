/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:23:16 by kycho             #+#    #+#             */
/*   Updated: 2021/03/18 06:22:53 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_fork_mutex(t_simul_info *info)
{
	int i;

	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->fork_mutex)
		return (ERROR);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->fork_mutex[i]), NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		init_philo(t_simul_info *info)
{
	int i;

	if (!(info->philo = malloc(sizeof(t_philo) * info->num_of_philo)))
		return (ERROR);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].fork[0] = i;
		info->philo[i].fork[1] = i + 1;
		if (info->philo[i].fork[1] >= info->num_of_philo)
			info->philo[i].fork[1] -= info->num_of_philo;
		info->philo[i].cnt_of_eat = 0;
		info->philo[i].time_of_last_eat = info->program_start_time;
		info->philo[i].info = info;
		if (pthread_mutex_init(&(info->philo[i].time_of_last_eat_mutex), NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		init(char **argv, t_simul_info *info)
{
	if ((info->num_of_philo = ft_atoi(argv[1])) < 2)
		return (ERROR);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		info->num_of_times_each_philo_must_eat = NO_DATA;
	info->program_start_time = gettimeofday_by_millisec();
	info->num_of_full_philo = 0;
	info->somebody_dead = FALSE;
	if (init_philo(info) == ERROR)
		return (ERROR);
	if (init_fork_mutex(info) == ERROR)
		return (ERROR);
	if (pthread_mutex_init(&(info->action_mutex), NULL))
		return (ERROR);
	if (pthread_mutex_init(&(info->num_of_full_philo_mutex), NULL))
		return (ERROR);
	return (SUCCESS);
}
