/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:35:23 by kycho             #+#    #+#             */
/*   Updated: 2021/03/18 07:05:55 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_action(t_philo *philo, int type)
{
	t_simul_info	*info;
	long			cur_time;

	info = philo->info;
	sem_wait(info->action_sem);
	cur_time = gettimeofday_by_millisec();
	if (type == EATING)
	{
		philo->time_of_last_eat = cur_time;
	}
	printf("%7ld  %3d %s\n",
			cur_time - info->program_start_time, philo->id, get_msg(type));
	if (type != DEAD)
		sem_post(info->action_sem);
}

void	*philo_monitor(void *arg)
{
	t_philo			*philo;
	t_simul_info	*info;
	long			cur_time;

	philo = (t_philo *)arg;
	info = philo->info;
	while (TRUE)
	{
		sem_wait(philo->time_of_last_eat_sem);
		cur_time = gettimeofday_by_millisec();
		if (info->time_to_die < (int)(cur_time - philo->time_of_last_eat))
		{
			philo_action(philo, DEAD);
			exit(1);
			sem_post(philo->time_of_last_eat_sem);
			return (NULL);
		}
		sem_post(philo->time_of_last_eat_sem);
		less_error_msleep(3);
	}
	return (NULL);
}

void	eat_proecss(t_philo *philo)
{
	t_simul_info *info;

	info = philo->info;
	sem_wait(info->pair_fork_sem);
	philo_action(philo, TAKEN_FORK);
	philo_action(philo, TAKEN_FORK);
	sem_wait(philo->time_of_last_eat_sem);
	philo_action(philo, EATING);
	sem_post(philo->time_of_last_eat_sem);
	less_error_msleep(info->time_to_eat);
	philo->cnt_of_eat++;
	if (philo->cnt_of_eat == info->num_of_times_each_philo_must_eat)
	{
		sem_wait(info->action_sem);
		sem_post(philo->philo_full_check_sem);
	}
	sem_post(info->pair_fork_sem);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	t_simul_info	*info;
	pthread_t		monitor_thread;

	philo = (t_philo*)arg;
	info = philo->info;
	pthread_create(&monitor_thread, NULL, philo_monitor, philo);
	if (!(philo->id % 2))
		less_error_msleep(philo->info->time_to_eat / 2);
	while (TRUE)
	{
		eat_proecss(philo);
		philo_action(philo, SLEEPING);
		less_error_msleep(philo->info->time_to_sleep);
		philo_action(philo, THINKING);
	}
	pthread_join(monitor_thread, NULL);
	return (NULL);
}

void	execute(t_simul_info *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].pid = fork();
		if (info->philo[i].pid == 0)
			break ;
		i++;
	}
	if (i != info->num_of_philo)
		philo_routine(&(info->philo[i]));
	else
		process_monitor(info);
}
