#include <pthread.h>
#include <stdio.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)

void	*test_pthread(void *arg)
{

}

int main(void)
{
	pthread_t	thread;
	char		*ret;

	pthread_create(&thread, NULL, test_pthread, );
	return (0);
}