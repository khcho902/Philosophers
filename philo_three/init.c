/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:23:16 by kycho             #+#    #+#             */
/*   Updated: 2021/03/18 06:55:12 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	set_sem_name(char *dest_name, char *common_name, int id)
{
	int		i;
	int		j;
	char	*id_str;

	i = 0;
	while (common_name[i])
	{
		dest_name[i] = common_name[i];
		i++;
	}
	dest_name[i] = '_';
	i++;
	j = 0;
	id_str = ft_itoa(id);
	while (id_str[j])
	{
		dest_name[i + j] = id_str[j];
		j++;
	}
	dest_name[i + j] = '\0';
	free(id_str);
}

void	init_sem(t_simul_info *info)
{
	sem_unlink("pair_fork");
	info->pair_fork_sem = sem_open(
		"pair_fork", O_CREAT | O_EXCL, 0644, info->num_of_philo / 2);
	sem_unlink("action");
	info->action_sem = sem_open("action", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("num_of_full_philo");
	info->num_of_full_philo_sem = sem_open(
		"num_of_full_philo", O_CREAT | O_EXCL, 0644, 1);
}

int		init_philo(t_simul_info *info, int i)
{
	t_philo	*philo;

	if (!(info->philo = malloc(sizeof(t_philo) * info->num_of_philo)))
		return (ERROR);
	while (i < info->num_of_philo)
	{
		philo = &info->philo[i];
		philo->id = i + 1;
		philo->cnt_of_eat = 0;
		philo->time_of_last_eat = info->program_start_time;
		philo->info = info;
		set_sem_name(
			philo->time_of_last_eat_sem_name, "time_of_last_eat", philo->id);
		sem_unlink(philo->time_of_last_eat_sem_name);
		philo->time_of_last_eat_sem = sem_open(
			philo->time_of_last_eat_sem_name, O_CREAT | O_EXCL, 0644, 1);
		set_sem_name(
			philo->philo_full_check_sem_name, "philo_full_check", philo->id);
		sem_unlink(philo->philo_full_check_sem_name);
		philo->philo_full_check_sem = sem_open(
			philo->philo_full_check_sem_name, O_CREAT | O_EXCL, 0644, 1);
		sem_wait(philo->philo_full_check_sem);
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
	info->simul_end = FALSE;
	info->num_of_full_philo = 0;
	if (init_philo(info, 0) == ERROR)
		return (ERROR);
	init_sem(info);
	return (SUCCESS);
}
