#include "philo.h"


int	join_threads(t_table *table);
int	destroy_mutex(t_table *table);

int	end_all(t_table *table)
{
	join_threads(table);
	destroy_mutex(table);
	free (table->fork_arr);
	free (table->philo_arr);
	free (table);
	return (0);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philo_arr[i].thread, NULL))
			return (printf("Failed joining a thread\n"), 1);
		i++;
	}
	if (pthread_join(table->monitor, NULL))
		return (printf("Failed joining monitor thread\n"), 1);
	return (0);
}

int	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->fork_arr[i].mutex);
		pthread_mutex_destroy(&table->philo_arr[i].data_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
	return (0);
}