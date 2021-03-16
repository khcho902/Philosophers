/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:31:18 by kycho             #+#    #+#             */
/*   Updated: 2021/03/17 00:38:41 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE			1
# define FALSE			0

# define NO_DATA		-1

# define SUCCESS		1
# define ERROR			-1

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

typedef struct			s_simul_info
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_times_each_philo_must_eat;

	long				program_start_time;

	int					num_of_full_philo;
	int					somebody_dead;

	t_philo				*philo;

	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		action_mutex;
	pthread_mutex_t		num_of_full_philo_mutex;

}						t_simul_info;

int						init(char **argv, t_simul_info *info);
void					execute(t_simul_info *info);
int						check_simul_end(t_simul_info *info);
char					*get_msg(int type);

long					gettimeofday_by_millisec(void);
int						ft_atoi(const char *str);
void					less_error_msleep(long milliseconds);

#endif
