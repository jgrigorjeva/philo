#include "philo.h"

t_bool	is_dead(t_table *table)
{
	t_bool	status;

	pthread_mutex_lock(&table->dead_mutex);
	status = table->died_id != 0;
	pthread_mutex_unlock(&table->dead_mutex);

	return (status);
}

int	ft_strcmp(const char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}