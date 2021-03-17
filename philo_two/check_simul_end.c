/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simul_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:38:31 by kycho             #+#    #+#             */
/*   Updated: 2021/03/17 03:45:53 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		check_simul_end(t_simul_info *info)
{
	if (info->somebody_dead == TRUE)
		return (TRUE);
	if (info->num_of_times_each_philo_must_eat != NO_DATA)
	{
		if (info->num_of_full_philo == info->num_of_philo)
			return (TRUE);
	}
	return (FALSE);
}
