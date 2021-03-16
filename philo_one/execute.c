/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:35:23 by kycho             #+#    #+#             */
/*   Updated: 2021/03/17 00:20:38 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_action(t_philo *philo, int type)
{
	t_simul_info	*info;
	long			cur_time;

	info = philo->info;
	pthread_mutex_lock(&info->action_mutex);
	if (check_simul_end(info) == TRUE)
	{
		pthread_mutex_unlock(&info->action_mutex);
		return ;
	}
	cur_time = gettimeofday_by_millisec();
	if (type == EATING)
	{
		philo->time_of_last_eat = cur_time;
	}
	else if (type == DEAD)
		info->somebody_dead = TRUE;
	printf("%7ld  %3d %s\n",
			cur_time - info->program_start_time, philo->id, get_msg(type));
	pthread_mutex_unlock(&info->action_mutex);
}

void	*philo_monitor(void *arg)
{
	t_philo			*philo;
	t_simul_info	*info;
	long			cur_time;

	philo = (t_philo *)arg;
	info = philo->info;
	while (check_simul_end(info) == FALSE)
	{
		pthread_mutex_lock(&(philo->time_of_last_eat_mutex));
		cur_time = gettimeofday_by_millisec();
		if (info->time_to_die < (int)(cur_time - philo->time_of_last_eat))
		{
			philo_action(philo, DEAD);
			pthread_mutex_unlock(&(philo->time_of_last_eat_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->time_of_last_eat_mutex));
		less_error_msleep(1);
	}
	return (NULL);
}

void	eat_proecss(t_philo *philo)
{
	t_simul_info *info;

	info = philo->info;
	pthread_mutex_lock(&(info->fork_mutex[philo->fork[0]]));
	philo_action(philo, TAKEN_FORK);
	pthread_mutex_lock(&(info->fork_mutex[philo->fork[1]]));
	philo_action(philo, TAKEN_FORK);
	pthread_mutex_lock(&(philo->time_of_last_eat_mutex));
	philo_action(philo, EATING);
	pthread_mutex_unlock(&(philo->time_of_last_eat_mutex));
	less_error_msleep(info->time_to_eat);
	philo->cnt_of_eat++;
	if (philo->cnt_of_eat == info->num_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&(info->num_of_full_philo_mutex));
		info->num_of_full_philo++;
		pthread_mutex_unlock(&(info->num_of_full_philo_mutex));
	}
	pthread_mutex_unlock(&(info->fork_mutex[philo->fork[0]]));
	pthread_mutex_unlock(&(info->fork_mutex[philo->fork[1]]));
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
	while (check_simul_end(info) == FALSE)
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
		pthread_create(
			&(info->philo[i].thread), NULL, philo_routine, &(info->philo[i]));
		i++;
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
}
