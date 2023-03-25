/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:46:46 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 23:40:06 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print(THINK, philo);
}

void	to_take_fork(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(&philo->program->mutex[philo->fork_left]);
		print(FORK, philo);
		pthread_mutex_lock(&philo->program->mutex[philo->fork_right]);
		print(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->program->mutex[philo->fork_right]);
		print(FORK, philo);
		pthread_mutex_lock(&philo->program->mutex[philo->fork_left]);
		print(FORK, philo);
	}
}

void	eating(t_philo *philo)
{
	philo->last_eat = time_now(philo);
	if (((philo->id % 2) == 0) && philo->id + 1 != philo->program->n_philo)
	{
		print(EAT, philo);
		pthread_mutex_lock(&philo->program->l_eat);
		philo->n_eat += 1;
		pthread_mutex_unlock(&philo->program->l_eat);
		smart_sleep(philo->program->time_eat, philo);
		pthread_mutex_unlock(&philo->program->mutex[philo->fork_right]);
		pthread_mutex_unlock(&philo->program->mutex[philo->fork_left]);
	}
	else
	{
		print(EAT, philo);
		pthread_mutex_lock(&philo->program->l_eat);
		philo->n_eat += 1;
		pthread_mutex_unlock(&philo->program->l_eat);
		smart_sleep(philo->program->time_eat, philo);
		pthread_mutex_unlock(&philo->program->mutex[philo->fork_left]);
		pthread_mutex_unlock(&philo->program->mutex[philo->fork_right]);
	}
}

int	check_death(t_program *prog)
{
	pthread_mutex_lock(&prog->m_dead);
	if (prog->dead == 0)
	{
		pthread_mutex_unlock(&prog->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&prog->m_dead);
	return (0);
}

void	one_philo(t_philo *philo)
{
	printf("%ld\t%d has taken a fork\n", get_time()
		- philo->program->start_clock, philo->id);
	usleep(philo->program->time_die * 1000);
	printf("%d\t%d died\n", philo->program->time_die, philo->id);
}
