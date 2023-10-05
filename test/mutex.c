#include <pthread.h>

void	*test_mutex(void *arg)
{
	
}

int main(void)
{
	pthread_mutext_t mutex;

	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (0);
	}

	if (pthread_mutex_lock(&mutex) != 0){
		perror("pthread_mutex_lock");
		return (0);
	}
	return (0);
}
