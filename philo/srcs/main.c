/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/09 16:05:00 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_error(int argc, char **argv);

bool	is_error(int argc, char **argv)
{
	(void)argv;
	if (argc != 4 && argc != 5)
		return (true);
	return (false);
}

void	init(t_table **table, int argc, char **argv)
{
	int	n_philo;

	n_philo = atoi(argv[1]);
	if (is_error(argc, argv))
		*table = NULL;
	else
		*table = new_table(argc, argv, n_philo);
}

// void	exec(t_table *table)
// {
// 	create_pthread(table);
// }

int main(int argc, char **argv)
{
	t_table	*table;

	init(&table, argc, argv);
	// exit(0);
	printf_debug_table(table);
	// exec(table);
	delete_table(table);
	// free_table(table);
	return (0);
}


