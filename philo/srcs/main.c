/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/15 23:20:47 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

#define ERROR_MES_FAILD_INIT "Initialization faild\n"
#define SUCCESS 0
#define ERROR 1

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

static bool	is_valid_n(int argc, char **argv)
{
	int		i;
	long	data;
	char	*end_ptr;

	i = 1;
	while (i < argc)
	{
		data = ft_strtol(argv[i], &end_ptr, 10);
		if (*end_ptr != '\0')
			return (false);
		(void)data;
		i++;
	}
	return (true);
}

static bool	is_error(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (is_valid_n(argc, argv))
			return (false);
		return (true);
	}
	return (true);
}

t_philo	**set_philos(int argc, char **argv)
{
	t_philo			**philos;
	t_fork			**forks;
	t_table			*table;

	if (is_error(argc, argv))
		return (NULL);
	table = new_table(new_config(argc, argv));
	if (table == NULL)
		return (NULL);
	forks = create_forks(table->config.n_philos);
	if (forks == NULL)
	{
		delete_table(table);
		return (NULL);
	}
	philos = create_philos(forks, table);
	if (philos == NULL)
	{
		delete_forks(forks);
		delete_table(table);
		return (NULL);
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_philo	**philos;
	int		index;

	philos = set_philos(argc, argv);
	if (philos == NULL)
	{
		write(STDERR_FILENO, ERROR_MES_FAILD_INIT,
			ft_strlen(ERROR_MES_FAILD_INIT));
		return (ERROR);
	}
	index = start_simulation(philos);
	return (end_simulation(philos, index));
}
