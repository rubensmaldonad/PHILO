/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:26:43 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 23:40:56 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	m_error(void)
{
	printf("Error \n");
	exit(0);
}

int	only_number(char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (!(argv[j][i] >= '0' && argv[j][i] <= '9'))
				m_error();
			i++;
			if (i > 10)
				m_error();
		}
		if ((argv[j][0] == '-' || argv[j][0] == '+') && i == 1)
			m_error();
		j++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	i;
	long	number;

	number = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m_error();
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10;
		number = number + str[i] - 48;
		i++;
	}
	if (number > 2147483647)
		m_error();
	return (number);
}

int	parse(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		only_number(argv);
		while (argv[i])
		{
			if (ft_atol(argv[i]) == 0)
				m_error();
			i++;
		}
		return (1);
	}
	else
		m_error();
	return (0);
}

void	*fill_struct(int argc, char **argv)
{
	t_program	prog;

	if (argc == 5 || argc == 6)
	{
		prog.n_philo = ft_atol(argv[1]);
		prog.time_die = ft_atol(argv[2]);
		prog.time_eat = ft_atol(argv[3]);
		prog.time_sleep = ft_atol(argv[4]);
		prog.start_clock = get_time();
		prog.dead = 0;
	}
	if (argc == 6)
		prog.number_eat = ft_atol(argv[5]);
	else
		prog.number_eat = -1;
	creater_malloc(&prog);
	return (0);
}
