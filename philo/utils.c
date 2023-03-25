/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:33:48 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 21:45:12 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

long	time_now(t_philo *philo)
{
	long	start_program;

	start_program = philo->program->start_clock;
	return (get_time() - start_program);
}

void	*print(int action, t_philo *philo)
{
	pthread_mutex_lock(&philo->program->print);
	if (action == DEAD && philo->program->dead == 1)
	{
		pthread_mutex_unlock(&philo->program->print);
		printf("%ld\t%d died\n", time_now(philo), philo->id);
		return (NULL);
	}
	pthread_mutex_lock(&philo->program->m_dead);
	if (action == SLEEP && philo->program->dead == 0)
		printf("%ld\t%d is sleeping\n", time_now(philo), philo->id);
	else if (action == THINK && philo->program->dead == 0)
		printf("%ld\t%d is thinking\n", time_now(philo), philo->id);
	else if (action == FORK && philo->program->dead == 0)
		printf("%ld\t%d has taken a fork\n", time_now(philo), philo->id);
	else if (action == EAT && philo->program->dead == 0)
		printf("%ld\t%d is eating\n", time_now(philo), philo->id);
	pthread_mutex_unlock(&philo->program->m_dead);
	pthread_mutex_unlock(&philo->program->print);
	return (0);
}

void	thread_sleep(t_philo *philo)
{
	print(SLEEP, philo);
	smart_sleep(philo->program->time_sleep, philo);
}

void	smart_sleep(long duration, t_philo *philo)
{
	long	start_time;

	start_time = time_now(philo);
	while (start_time + duration > time_now(philo))
		usleep(100);
}
