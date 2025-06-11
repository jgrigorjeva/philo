#include "philo.h"

void	pick_forks_right_first(t_philo *philo);
void	pick_forks_left_first(t_philo *philo);
void	drop_forks_right_first(t_philo *philo);
void	drop_forks_left_first(t_philo *philo);

int	eat(t_philo *philo)
{
	if (philo->id % 2)
		pick_forks_left_first(philo);
	else
		pick_forks_right_first(philo);
	print_status(philo, "is eating");
	philo->last_fed = get_time();
	ft_usleep(philo->table->tte);
	philo->state = EAT;
	philo->meals_eaten++;
	if (philo->id % 2)
		drop_forks_right_first(philo);
	else
		drop_forks_left_first(philo);
	if (philo->table->max_meals > 0 \
		&& philo->meals_eaten < philo->table->max_meals)
		return (0);
	else
		return (1);
}

void	pick_forks_left_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->stat = philo->id;
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->stat = philo->id;
	print_status(philo, "has taken a fork");
}

void	pick_forks_right_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->stat = philo->id;
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->stat = philo->id;
	print_status(philo, "has taken a fork");
}

void	drop_forks_right_first(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	print_status(philo, "has put down both forks");
}

void	drop_forks_left_first(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	print_status(philo, "has put down both forks");
}
