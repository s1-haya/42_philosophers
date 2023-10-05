#include <pthread.h>
#include <stdio.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)

void	*is_pthread(void *arg)
{

}

int main(void)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, is_pthread, )
	return (0);
}