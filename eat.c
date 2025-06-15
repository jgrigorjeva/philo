#include "philo.h"

void	pick_forks_right_first(t_philo *philo);
void	pick_forks_left_first(t_philo *philo);
void	drop_forks(t_philo *philo);


int	eat(t_philo *philo)
{
	if (!(philo->id % 2))
		pick_forks_left_first(philo);
	else
		pick_forks_right_first(philo);
	if (!is_dead(philo->table))
		print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data_mutex);
	philo->last_fed = get_time() - philo->table->start_time;
	pthread_mutex_unlock(&philo->data_mutex);

	ft_msleep_check(philo->table->tte, philo->table);
	// ft_msleep(philo->table->tte);
	drop_forks(philo);
	pthread_mutex_lock(&philo->data_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data_mutex);
	return (0);
}

void	pick_forks_left_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->stat = philo->id;
	if (!is_dead(philo->table))
		print_status(philo, "has taken left fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->stat = philo->id;
	if (!is_dead(philo->table))
		print_status(philo, "has taken right fork");
}

void	pick_forks_right_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->stat = philo->id;
	if (!is_dead(philo->table))
		print_status(philo, "has taken right fork");
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->stat = philo->id;
	if (!is_dead(philo->table))
		print_status(philo, "has taken left fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	if (!is_dead(philo->table))
		print_status(philo, "has put down both forks");
}
