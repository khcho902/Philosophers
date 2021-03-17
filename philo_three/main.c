/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:20:21 by kycho             #+#    #+#             */
/*   Updated: 2021/03/18 05:04:25 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	destroy(t_simul_info *info)
{
	int i;

	sem_close(info->pair_fork_sem);
	sem_close(info->action_sem);
	sem_close(info->num_of_full_philo_sem);
	i = 0;
	while (i < info->num_of_philo)
	{
		sem_close(info->philo[i].time_of_last_eat_sem);
		sem_post(info->philo[i].philo_full_check_sem);
		sem_close(info->philo[i].philo_full_check_sem);
		i++;
	}
	free(info->philo);
}

int		is_fine_args(int argc, char **argv)
{
	int i;
	int j;

	if (!(argc == 5 || argc == 6))
		return (FALSE);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!('0' <= argv[i][j] && argv[i][j] <= '9'))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int		main(int argc, char **argv)
{
	t_simul_info info;

	if (!is_fine_args(argc, argv))
	{
		printf("Argument Error!\n");
		return (1);
	}
	if (init(argv, &info) == ERROR)
	{
		printf("init fail!!\n");
		return (1);
	}
	execute(&info);
	destroy(&info);
	return (0);
}
