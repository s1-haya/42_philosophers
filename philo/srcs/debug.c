#include "philo.h"
#include <stdio.h>

void	printf_debug_philo_ability(t_philo_ability ability)
{
	printf("die time: %d, eat time: %d, sleep_time: %d, eat count: %d\n", ability.die_time, ability.eat_time, ability.sleep_time, ability.eat_count);
}

void	printf_debug_philo(t_philo *philo)
{
	if (philo == NULL)
		return ;
	printf("--- debug philo %d ---\n", philo->id);
	if (!philo->left->is_used)
		printf("left last_eat: %d\n", philo->left->last_eat_philo);
	if (!philo->right->is_used)
		printf("right last_eat: %d\n", philo->right->last_eat_philo);
	// printf_debug_philo_ability(philo->table->ability);
	printf("----- debug end -----\n");
	printf("\n");
}

void	printf_debug_table(int id, t_table *table)
{
	if (table == NULL)
		return ;
	printf("--- debug table %d ---\n", id);
	if (table->is_success)
		printf("ok success\n");
	if (table->is_error)
		printf("ok error\n");
	if (table->is_dead)
		printf("ok dead\n");
	printf("start_time   %ld\n", get_elapsed_ms(table->start_time));
	printf("n_philos_ate %d\n", table->n_philos_ate);
	printf_debug_philo_ability(table->ability);
	printf("----- debug end -----\n");
	printf("\n");
	// printf_debug_fork(table.forks);
}

void	printf_debug_philos(t_philo **philos)
{
	size_t	i;

	i = 0;
	printf_debug_table(philos[i]->id, philos[i]->table);
	while (philos[i] != NULL)
	{
		printf_debug_philo(philos[i]);
		i++;
	}
}

