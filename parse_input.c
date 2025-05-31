#include "philo.h"

t_input	*parse_input(int argc, char **argv)
{
	t_input	*input;

	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 \
	|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (printf("Invalid arguments\n"), NULL);
	input = malloc(sizeof(t_input));
	if (!input)
		return (printf("Error allocating input\n"), NULL);
	input->philo_nbr = ft_atoi(argv[1]);
	input->ttd = ft_atoi(argv[2]);
	input->tte = ft_atoi(argv[3]);
	input->tts = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		input->meal_nbr = ft_atoi(argv[5]);
	else
		input->meal_nbr = -1;
	return (input);
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	i;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		++i;
	}
	if (nptr[i] == '-')
	{
		sign = -1;
		++i;
	}
	else if (nptr[i] == '+')
		++i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		++i;
	}
	num = num * sign;
	return (num);
}

void	print_input(t_input *input)
{
	if (!input)
	{
		printf("Input is empty\n");
		return ;
	}
	printf("Number of philosophers: %d\n", input->philo_nbr);
	printf("Time to die: %d\n", input->ttd);
	printf("Time to eat: %d\n", input->tte);
	printf("Time to sleep: %d\n", input->tts);
	printf("Number of meals: %d\n", input->meal_nbr);
}