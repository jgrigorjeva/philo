/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:09:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/11 18:57:05 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_input		*input;
	t_table		*table;

	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments\n"), 1);
	input = parse_input(argc, argv);
	if (!input)
		return (1);
	// print_input(input);
	table = init_all(input);
	free (input);
	if (!table)
		return (printf("Error initializing table\n"), 1);
	end_all(table);
	return (0);
}
