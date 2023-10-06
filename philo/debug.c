#include "philo.h"
#include <stdio.h>

void	printf_debug_philo_ability(t_philo_ability ability)
{
	printf("die time: %d, eat time: %d, sleep_time: %d, eat count: %d\n", ability.die_time, ability.eat_time, ability.sleep_time, ability.eat_count);
}

void	printf_debug_philo(t_philo *philo)
{
	printf("--- debug philo %d ---\n", philo->id);
	if (!philo->left_fork->is_used)
		printf("ok left fork\n");
	if (!philo->right_fork->is_used)
		printf("ok right fork\n");
	printf_debug_philo_ability(philo->ability);
	printf("----- debug end -----\n");
	printf("\n");
}

void	printf_debug_philos(t_philo **philos)
{
	size_t	i;

	i = 0;
	while (philos[i] != NULL)
	{
		printf_debug_philo(philos[i]);
		i++;
	}
}

void	printf_debug_table(t_table table)
{
	printf_debug_philos(table.philos);
	// printf_debug_fork(table.forks);
}