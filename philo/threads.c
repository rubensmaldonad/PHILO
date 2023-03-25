/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:21:56 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 23:44:55 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creater_malloc(t_program *prog)
{
	prog->philo = malloc(sizeof(t_philo) * prog->n_philo);
	prog->mutex = malloc(sizeof(pthread_mutex_t) * prog->n_philo);
	init_mutex(prog);
	init_thread(prog);
	init_join(prog->philo);
	freeall(prog);
}

void	init_thread(t_program *pr)
{
	int	i;

	i = 0;
	while (i < pr->n_philo)
	{
		pr->philo[i].id = i + 1;
		pr->philo[i].program = pr;
		pr->philo[i].fork_left = i;
		pr->philo[i].last_eat = 0;
		pr->philo[i].n_eat = 0;
		if (pr->philo[i].id == pr->n_philo)
			pr->philo[i].fork_right = 0;
		else
			pr->philo[i].fork_right = i + 1;
		i++;
		if (i == pr->n_philo)
			break ;
	}
	i = -1;
	while (++i < pr->n_philo)
		pthread_create(&pr->philo[i].threads, NULL, &routine, &pr->philo[i]);
	if (pr->n_philo != 1)
		monitoring(pr);
}

void	init_mutex(t_program *prog)
{
	int	i;

	i = 0;
	pthread_mutex_init(&prog->print, NULL);
	pthread_mutex_init(&prog->l_eat, NULL);
	pthread_mutex_init(&prog->m_dead, NULL);
	while (i != prog->n_philo)
	{
		pthread_mutex_init(&prog->mutex[i], NULL);
		i++;
	}
}

void	init_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->program->n_philo)
	{
		pthread_join(philo[i].threads, NULL);
		i++;
	}
	free(philo);
	free(philo->program->mutex);
}
