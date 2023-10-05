#include <pthread.h>
#include <stdio.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)

void	*pthread(void *arg)
{

}

int main(void)
{
	pthread_t	thread;
	char		*ret;

	pthread_create(&thread, NULL, is_pthread, ret);
	return (0);
}