/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:31:18 by kycho             #+#    #+#             */
/*   Updated: 2021/03/16 20:27:14 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define TRUE		1
# define FALSE		0
# define NO_DATA	-1

# define TAKEN_FORK		0
# define EATING			1
# define SLEEPING		2
# define THINKING		3
# define DEAD			4

struct s_simul_info;

typedef struct			s_philo
{
	int					id;
	int					fork[2];
	int					cnt_of_eat;
	long				time_of_last_eat;
	
	pthread_t			thread;
	struct s_simul_info	*info;

	pthread_mutex_t		time_of_last_eat_mutex;

}						t_philo;

typedef struct		s_simul_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;

	long			program_start_time;

	int				num_of_full_philo;  // 관리대상
	int				somebody_dead;      // 관리대상

	t_philo			*philo;
	
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	action_mutex;
	
}					t_simul_info;

#endif
