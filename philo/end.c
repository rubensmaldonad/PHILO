/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:14:29 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 21:34:04 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeall(t_program *prog)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&prog->m_dead);
	pthread_mutex_destroy(&prog->l_eat);
	pthread_mutex_destroy(&prog->print);
	while (i < prog->n_philo)
	{
		pthread_mutex_destroy(&prog->mutex[i]);
		i++;
	}
}
