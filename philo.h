/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:33:48 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/11 23:17:10 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <pthread.h>
# include <stdio.h> //printf
# include <stdlib.h> //malloc
# include <sys/time.h> // gettimeofday
// # include <sys/types.h> // u_int64_t type
# include <stdint.h> // uint64_t type
# include <unistd.h> // usleep

typedef struct s_input
{
	int	philo_nbr;
	int	ttd;
	int	tte;
	int	tts;
	int	meal_nbr;
}	t_input;

typedef enum e_state
{
	SLEEP,
	EAT,
	THINK,
	DEAD
}	t_state;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

// Ten int stat používám jen kvůli tomu, 
// že vidlička má obsahovat ještě něco dalšího kromě mutexu.
// Pak tam třeba zapíšeme id filosofa, který ji drží
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				stat;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_state			state;
	long		last_fed;
	int				meals_eaten;
	t_bool			now_eating;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				philo_nbr;
	int				max_meals;
	int				ttd;
	int				tte;
	int				tts;
	t_philo			*philo_arr;
	t_fork			*fork_arr;
	long		start_time;
	int				died_id;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		monitor;
}	t_table;

t_input	*parse_input(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	print_input(t_input *input);
t_table	*init_all(t_input *input);
t_table	*init_table(t_input *input);
void	assign_forks(t_table *table);
int		init_mutex(t_table *table);
void		init_philo_arr(t_table *table);

// timing
int		ft_usleep(unsigned int time);
long	get_time(void);

// routine
void	*monitor_routine(void *arg);
void	*routine(void *arg);
void	handle_one_philo(t_philo *philo);
void	print_status(t_philo *philo, const char *msg);
void	think(t_philo *philo);
int		eat(t_philo *philo);
int		go_sleep(t_philo *philo);

// end
int		end_all(t_table *table);

// utils
t_bool	is_dead(t_table *table);
int		ft_strcmp(const char *s1, char *s2);
t_bool	all_meals_eaten(t_table *table);
#endif