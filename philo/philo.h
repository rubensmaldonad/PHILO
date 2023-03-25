/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaldona <rmaldona@student42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:20:42 by rmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 23:37:07 by rmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define EAT 50
# define THINK 51
# define SLEEP 52
# define DEAD 53
# define FORK 54

typedef struct s_philo	t_philo;
typedef struct s_program
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_eat;
	long			start_clock;
	int				dead;
	t_philo			*philo;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	l_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print;
}					t_program;

typedef struct s_philo
{
	int			id;
	int			fork_right;
	int			fork_left;
	int			n_eat;
	long		last_eat;
	pthread_t	threads;
	t_program	*program;
}				t_philo;

int		only_number(char **argv);
int		parse(int argc, char **argv);
void	m_error(void);
long	ft_atol(const char *str);
void	*fill_struct(int argc, char **argv);
void	creater_malloc(t_program *prog);
void	*routine(void *args);
void	init_thread(t_program *prog);
void	init_mutex(t_program *prog);
void	init_join(t_philo *philo);
void	to_take_fork(t_philo *prog);
void	smart_sleep(long duration, t_philo *philo);
void	thread_sleep(t_philo *philo);
void	think(t_philo *philo);
void	*print(int action, t_philo *philo);
long	get_time(void);
long	time_now(t_philo *philo);
int		check_death(t_program *prog);
int		ft_eat(t_program *prog);
void	one_philo(t_philo *philo);
int		ft_isdead(t_program *prog);
void	*monitoring(t_program *prog);
void	eating(t_philo *philo);
void	freeall(t_program *prog);
void	func(t_philo *philo);

#endif
