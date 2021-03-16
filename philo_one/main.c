/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:20:21 by kycho             #+#    #+#             */
/*   Updated: 2021/03/16 20:34:47 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// utils.c  start // 
long	gettimeofday_by_millisec(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int		ft_atoi(const char *str)
{
	size_t	i;
	int		res;
	int		sign;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	i += (str[i] == '-' || str[i] == '+') ? 1 : 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (sign * res);
}

void			less_error_msleep(long milliseconds)
{
	long	base_time;

	base_time = gettimeofday_by_millisec();
	while (TRUE)
	{
		if (milliseconds <= gettimeofday_by_millisec() - base_time)
			return ;
		usleep(500);
	}	
}
// utils.c   end  // 



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
		philo->cnt_of_eat++;
		philo->time_of_last_eat = cur_time;
		if (philo->cnt_of_eat == info->num_of_times_each_philo_must_eat)
			info->num_of_full_philo++;
	}
	else if (type == DEAD)
		info->somebody_dead = TRUE;
	printf("%7ld  %3d %s\n", cur_time - info->program_start_time, philo->id, get_msg(type));
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

void	run(t_simul_info *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_create(&(info->philo[i].thread), NULL, philo_routine, &(info->philo[i]));
		i++;
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
}

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

void	init(char **argv, t_simul_info *info)
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		info->num_of_times_each_philo_must_eat = NO_DATA;
	
	info->program_start_time = gettimeofday_by_millisec();
	info->num_of_full_philo = 0;
	info->somebody_dead = FALSE;

	// TODO : 말록 가드해야함 
	info->philo = malloc(sizeof(t_philo) * info->num_of_philo);

	int i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].fork[0] = i;
		info->philo[i].fork[1] = i + 1;
		if (info->philo[i].fork[1] >= info->num_of_philo)
		{
			info->philo[i].fork[1] -= info->num_of_philo;
		}
		info->philo[i].cnt_of_eat = 0;
		info->philo[i].time_of_last_eat = info->program_start_time;
		info->philo[i].info = info;
		pthread_mutex_init(&(info->philo[i].time_of_last_eat_mutex), NULL);
		i++;
	}

	// TODO : 말록 가드해야함 
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_init(&(info->fork_mutex[i]), NULL);
		i++;
	}

	pthread_mutex_init(&(info->action_mutex), NULL);
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
	init(argv, &info);
	run(&info);
	destroy(&info);
	return (0);
}
