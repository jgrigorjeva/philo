#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	time_t	now;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			now = get_time();
			if (now - table->philo_arr[i].last_fed >= table->ttd)
			{
				table->died_id = table->philo_arr[i].id;
				print_status(&table->philo_arr[i], "died");
			}
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	think(philo);
	// if (eat(philo))
		// end_all(philo->table);
	eat(philo);
	go_sleep(philo);
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