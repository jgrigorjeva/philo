/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:09:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/29 18:23:14 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	static int i;

	printf("Hello from philo nr. %d\n", i++);
	(void)arg;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_input		*input;
	pthread_t	*th;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	input = parse_input(argc, argv);
	print_input(input);
	th = malloc(sizeof(pthread_t) * input->philo_nbr);
	i = 0;
	while (i < input->philo_nbr)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (free (input), printf("Failed creating a thread\n"), 1);
		i++;
	}
	i = 0;
	while (i < input->philo_nbr)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (free (input), printf("Failed joining a thread\n"), 2);
		i++;
	}
	free (th);
	free (input);
	return (0);
}

