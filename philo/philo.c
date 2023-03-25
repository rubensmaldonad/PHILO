/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:18:32 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 23:46:31 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philo)
	{
		pthread_mutex_lock(&prog->l_eat);
		if (prog->philo[i].n_eat == prog->number_eat)
		{
			pthread_mutex_unlock (&prog->l_eat);
			return (NULL);
		}
		if ((time_now(prog->philo) - prog->philo[i].last_eat) > prog->time_die)
		{
			prog->dead = 1;
			pthread_mutex_lock (&prog->m_dead);
			print(DEAD, &prog->philo[i]);
			pthread_mutex_unlock (&prog->m_dead);
			pthread_mutex_unlock (&prog->l_eat);
			return (NULL);
		}
		pthread_mutex_unlock (&prog->l_eat);
		i = (i + 1) % prog->n_philo;
	}
	return (0);
}

void	func(t_philo *philo)
{
	while (check_death(philo->program) == 1)
	{
		pthread_mutex_lock(&philo->program->l_eat);
		if (philo->n_eat == philo->program->number_eat)
		{
			pthread_mutex_unlock(&philo->program->l_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->program->l_eat);
		if (check_death(philo->program) == 1)
			to_take_fork(philo);
		if (check_death(philo->program) == 1)
			eating(philo);
		if (check_death(philo->program) == 1)
			thread_sleep(philo);
		if (check_death(philo->program) == 1)
			print (THINK, philo);
		if (check_death(philo->program) == 0)
		{
			pthread_mutex_unlock(&philo->program->l_eat);
			break ;
		}
	}
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	if (philo->program->n_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if ((philo->id % 2) == 0)
		usleep (1000);
	func(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	*prog;
	t_philo		*philo;

	philo = &(t_philo){0};
	prog = &(t_program){0};
	if (parse(argc, argv) == 1)
	{
		fill_struct(argc, argv);
		return (0);
	}
}
