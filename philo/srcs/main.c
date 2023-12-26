/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/26 12:46:21 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ERROR_MES_FAILD_INIT "Initialization faild\n"
#define DIGIT_INT_MAX 9

static bool	is_valid_n(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) > DIGIT_INT_MAX || ft_atoi(argv[i]) < 0)
			return (false);
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
	table = new_table(new_philo_ability(argc, argv));
	if (table == NULL)
		return (NULL);
	forks = create_forks(table->ability.n_philos);
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
