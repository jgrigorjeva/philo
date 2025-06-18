/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:02:15 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 20:12:22 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	long	timestamp;

	philo = (t_philo *)arg;
	wait_before_start(philo->table);
	if (philo->table->philo_nbr == 1)
		return (handle_one_philo(philo), NULL);
	think(philo);
	if (philo->id % 2)
		ft_msleep(20);
	while (!is_dead(philo->table) && !all_meals_eaten(philo->table))
	{
		timestamp = get_time() - philo->table->start_time;
		if (philo->table->philo_nbr % 2 == 1 && timestamp - philo->last_fed \
			< 2 * philo->table->tte + philo->table->tts)
			ft_msleep(5);
		if (!is_dead(philo->table) && !all_meals_eaten(philo->table))
			eat(philo);
		if (!is_dead(philo->table) && !all_meals_eaten(philo->table))
			go_sleep(philo);
		if (!is_dead(philo->table) && !all_meals_eaten(philo->table))
			think(philo);
	}
	return (NULL);
}

void	think(t_philo *philo)
{
	if (!is_dead(philo->table))
		print_status(philo, "is thinking");
}

int	go_sleep(t_philo *philo)
{
	if (!is_dead(philo->table))
		print_status(philo, "is sleeping");
	ft_msleep_check(philo->table->tts, philo->table);
	return (0);
}

void	handle_one_philo(t_philo *philo)
{
	print_status(philo, "is thinking");
	print_status(philo, "has taken a fork");
	ft_msleep(philo->table->ttd);
	print_status(philo, "died");
	pthread_mutex_lock(&philo->table->dead_mutex);
	philo->table->someone_died = TRUE;
	pthread_mutex_unlock(&philo->table->dead_mutex);
}
