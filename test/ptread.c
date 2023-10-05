#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
#define N_THREAD 4

// void はポインタのため、32bit環境ではvoidは32bitであり、intも基本的には32bitで同じサイズのため、
// 32bit環境に限れば問題なくコンパイル、実行が出来ます。64bit環境ではvoid *は64bitのため、intが32bitの場合は足りない分が消滅
typedef struct e_num_pthread
{
	int					num;
	long				ms_init;
	pthread_mutex_t	mutex;
}	t_num_pthread;

long	getMsTime(struct timeval *tv);

void	*test_pthread(void *arg)
{
	t_num_pthread	*data;
	struct timeval	tv;

	data = (t_num_pthread *)arg;

	// printf("id %d\n", (*data).num);
	for (int i = 0; i < N_THREAD; i++){
		printf("id %d, time %ld\n", data->num, getMsTime(&tv) - data->ms_init);
		usleep(1000);
	}

	printf("waiting N %d...\n", data->num);
	if (pthread_mutex_lock(&data->mutex) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	printf("pthread N %d\n", data->num);
	if (pthread_mutex_unlock(&data->mutex) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
	return (data);
}

int main(void)
{
	pthread_t		v[N_THREAD];
	t_num_pthread	*data[N_THREAD];
	int				p_create;
	int				p_join;
	long		ms;
	struct timeval	tv;

	pthread_mutex_t mutex;

	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (0);
	}

	ms = getMsTime(&tv);
	for (int i = 0; i < N_THREAD; i++){
		data[i] = (t_num_pthread *)malloc(sizeof(t_num_pthread));
		data[i]->num = i;
		data[i]->ms_init = ms;
		data[i]->mutex = mutex;
		p_create = pthread_create(&v[i], NULL, test_pthread, data[i]);
		if (p_create != 0)
		{
			perror("pthread_create");
			return (0);
		}
	}

	for (int i = 0; i < N_THREAD; i++){
		char *ret;
		p_join = pthread_join(v[i], (void **)&ret);
		free(data[i]);
		if (p_join == 0)
			printf("finish ID %d, %s\n", i, ret);
		else
		{
			perror("pthread_join");
			return (0);
		}
	}

	if (pthread_mutex_destroy(&mutex) != 0)
	{
		perror("pthread_mutex_destroy");
		return (0);
	}
	return (0);
}