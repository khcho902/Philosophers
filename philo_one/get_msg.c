/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:39:35 by kycho             #+#    #+#             */
/*   Updated: 2021/03/16 21:39:47 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char	*get_msg(int type)
{
	if (type == TAKEN_FORK)
		return ("has taken a fork");
	else if (type == EATING)
		return ("is eating");
	else if (type == SLEEPING)
		return ("is sleeping");
	else if (type == THINKING)
		return ("is thinking");
	else
		return ("died");
}
