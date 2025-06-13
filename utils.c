#include "philo.h"

t_bool	is_dead(t_table *table)
{
	t_bool	status;

	pthread_mutex_lock(&table->dead_mutex);
	status = table->died_id != 0;
	pthread_mutex_unlock(&table->dead_mutex);

	return (status);
}

t_bool	should_die(long timestamp, t_philo *philo)
{
	t_bool	status;
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->data_mutex);
	status = timestamp - philo->last_fed >= table->ttd && table->philo_nbr > 1;
	pthread_mutex_unlock(&philo->data_mutex);
	return (status);
}

t_bool	all_meals_eaten(t_table *table)
{
	int		i;
	int		count;

	if (table->max_meals < 0)
		return (FALSE);
	i = 0;
	count = 0;
	while (i < table->philo_nbr)
	{
		if (philo_max_fed(&table->philo_arr[i], table))
			count++;
		i++;
	}
	return (i == count);
}

t_bool	philo_max_fed(t_philo *philo, t_table *table)
{
	t_bool	status;

	pthread_mutex_lock(&philo->data_mutex);
	status = philo->meals_eaten >= table->max_meals;
	pthread_mutex_unlock(&philo->data_mutex);
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