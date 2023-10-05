#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
#define N_THREAD 4

void	*test_pthread(void *arg)
{
	int id;

	id = (int)arg;
	printf("id %d \n");
	// for (int i = 0; i < N_THREAD; i++){
	// 	printf("id %d, i %d\n", id, i);
	// }
	return ((void *)id);
}

int main(void)
{
	pthread_t	v[N_THREAD];
	int			p_create;
	int			p_join;

	for (int i = 0; i < N_THREAD; i++){
		p_create = pthread_create(&v[i], NULL, test_pthread, (void *)i);
		if (p_create != 0)
			return (0);
	}

	for (int i = 0; i < N_THREAD; i++){
		int id;
		p_join = pthread_join(v[i], (void **)&i);
		if (p_join == 0)
			printf("finish ID %d\n", id);
		else
			return (0)

	}
	return (0);
}