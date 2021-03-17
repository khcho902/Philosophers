/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:05:24 by kycho             #+#    #+#             */
/*   Updated: 2021/03/18 07:07:33 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	kill_process(t_simul_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		kill(info->philo[i].pid, SIGKILL);
		i++;
	}
}

void	*full_monitor_thread(void *arg)
{
	t_philo			*philo;
	t_simul_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	sem_wait(philo->philo_full_check_sem);
	sem_wait(info->num_of_full_philo_sem);
	info->num_of_full_philo++;
	if (info->num_of_full_philo == info->num_of_philo)
		info->simul_end = TRUE;
	else
		sem_post(info->action_sem);
	sem_post(info->num_of_full_philo_sem);
	return (NULL);
}

void	full_monitor(t_simul_info *info)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_create(&thread, NULL, full_monitor_thread, &info->philo[i]);
		pthread_detach(thread);
		i++;
	}
}

void	process_monitor(t_simul_info *info)
{
	int			i;
	int			status;

	full_monitor(info);
	i = 0;
	while (info->simul_end == FALSE)
	{
		status = -1;
		waitpid(info->philo[i].pid, &status, WNOHANG);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			info->simul_end = TRUE;
		i++;
		if (i == info->num_of_philo)
			i = 0;
	}
	kill_process(info);
}
