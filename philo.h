/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:33:48 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/30 19:18:17 by jgrigorj         ###   ########.fr       */
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
	int	
}

typedef struct s_philo
{
	int			id;
	t_state		state;
	t_timing	timing;
}

t_input	*parse_input(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	print_input(t_input *input);

#endif