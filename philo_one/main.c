/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:20:21 by kycho             #+#    #+#             */
/*   Updated: 2021/03/18 06:29:41 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	destroy(t_simul_info *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&info->action_mutex);
	free(info->fork_mutex);
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
