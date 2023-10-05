#include <pthread.h>
#include <stdio.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
#define N_THREAD 4

void	*test_pthread(void *arg)
{

}

int main(void)
{
	pthread_t	v[N_THREAD];
	for (i = 0; i < N_THREAD; i++){
		pthread_create(&thread, NULL, test_pthread, (void *)i));
	}
	return (0);
}