#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	now;
	long	timestamp;

	table = (t_table *)arg;
	while (!is_dead(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			// printf("i %d, table->philo_nbr %d\n", i, table->philo_nbr);
			now = get_time();
			timestamp = now - table->start_time;
			// printf("monitor: now %ld last fed %ld difference %ld ttd %d tte %d tts %d\n", \
				// timestamp, table->philo_arr[i].last_fed, timestamp - table->philo_arr[i].last_fed, table->ttd, table->tte, table->tts);
			if (timestamp - table->philo_arr[i].last_fed >= table->ttd)
			{
				pthread_mutex_lock(&table->dead_mutex);
				table->died_id = table->philo_arr[i].id;
				print_status(&table->philo_arr[i], "died");
				pthread_mutex_unlock(&table->dead_mutex);
		
				break;
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	long	now;
	long	timestamp;

	philo = (t_philo *)arg;

	now = get_time();
	timestamp = now - philo->table->start_time;
	
	
	while (!is_dead(philo->table))
	{
		think(philo);
		if (!is_dead(philo->table))
			eat(philo);
		if (!is_dead(philo->table))
			go_sleep(philo);
	}
	
	return (NULL);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	philo->state = THINK;
}

int	go_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	philo->state = SLEEP;
	ft_usleep(philo->table->tts);
	return (0);
}