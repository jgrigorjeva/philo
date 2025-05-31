/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:33:48 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/31 20:12:01 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <pthread.h>
# include <stdio.h> //printf
# include <stdlib.h> //malloc

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

typedef struct s_timing
{
	time_t	last_fed;	
}	t_timing;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philo
{
	int			id;
	pthread_t	*thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_state		state;
	t_timing	timing;
	int			meals_eaten;
	t_bool		now_eating;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_table
{
	int		philo_nbr;
	t_philo	*philo_arr;
	t_fork	*fork_arr;
}	t_table;

t_input	*parse_input(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	print_input(t_input *input);

#endif