/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/24 13:03:58 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_error(int argc, char **argv);

#define ERROR_MES_INVALID_ARGUMENT "Invalid argument\n"
#define ERROR_MES_FAILD_INIT "Initialization faild\n"

// bool	is_valid_n(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_atoi(str[i]) <= 0)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

bool	is_error(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (ft_atoi(argv[i]) <= 0)
				return (true);
			i++;
		}
		return (false);
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
		return (NULL);
	philos = create_philos(forks, table);
	if (philos == NULL)
		return (NULL);
	return (philos);
}

int main(int argc, char **argv)
{
	t_philo	**philos;
	int		index;

	philos = set_philos(argc, argv);
	if (philos == NULL)
	{
		printf(ERROR_MES_FAILD_INIT);
		return (ERROR);
	}
	index = start_simulation(philos);
	return (end_simulation(philos, index));
}
