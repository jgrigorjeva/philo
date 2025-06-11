#include "philo.h"

t_bool	is_dead(t_table *table)
{
	t_bool	status;

	pthread_mutex_lock(&table->dead_mutex);
	status = table->died_id != 0;
	pthread_mutex_unlock(&table->dead_mutex);

	return (status);
}