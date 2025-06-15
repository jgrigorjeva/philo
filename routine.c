#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	now;
	long	timestamp;

	table = (t_table *)arg;
	while (get_time() < table->start_time)
		ft_msleep(1);
	while (!is_dead(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			now = get_time();
			timestamp = now - table->start_time;
			if (should_die(timestamp, &table->philo_arr[i]))
			{
				pthread_mutex_lock(&table->dead_mutex);
				table->someone_died = TRUE;
				pthread_mutex_unlock(&table->dead_mutex);
				if (!all_meals_eaten(table))
					print_status(&table->philo_arr[i], "died");
				return (NULL);
			}
			i++;
		}
		ft_msleep(1);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	long	timestamp;

	philo = (t_philo *)arg;
	if (philo->table->philo_nbr == 1)
		return (handle_one_philo(philo), NULL);
	while (get_time() < philo->table->start_time)
		ft_msleep(1);
	think(philo);
	if (philo->id % 2)
		ft_msleep(20);
	while (!is_dead(philo->table) && !all_meals_eaten(philo->table))
	{
		// think(philo);
		timestamp = get_time() - philo->table->start_time;
		if (philo->table->philo_nbr % 2 == 1 \
		&& timestamp - philo->last_fed < 2 * philo->table->tte + philo->table->tts)
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
	// ft_msleep_check(philo->table->tts, philo->table);
	 ft_msleep(philo->table->tts);
	return (0);
}

void	handle_one_philo(t_philo *philo)
{
	print_status(philo, "is thinking");
	print_status(philo, "has taken a fork");
	ft_msleep(philo->table->ttd);
	print_status(philo, "died");
	philo->table->someone_died = TRUE;
}