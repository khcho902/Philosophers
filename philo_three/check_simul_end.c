/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simul_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:38:31 by kycho             #+#    #+#             */
/*   Updated: 2021/03/17 22:13:37 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_simul_end(t_simul_info *info)
{
	/*
	if (info->somebody_dead == TRUE)
		return (TRUE);
	if (info->num_of_times_each_philo_must_eat != NO_DATA)
	{
		if (info->num_of_full_philo == info->num_of_philo)
			return (TRUE);
	}*/
	if (info == NULL)
		return (TRUE);
	return (FALSE);
}
