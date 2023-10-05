#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
#define N_THREAD 4

// void はポインタのため、32bit環境ではvoidは32bitであり、intも基本的には32bitで同じサイズのため、
// 32bit環境に限れば問題なくコンパイル、実行が出来ます。64bit環境ではvoid *は64bitのため、intが32bitの場合は足りない分が消滅
typedef struct e_num_pthread
{
	int num;
}	t_num_pthread;


void	*test_pthread(void *arg)
{
	t_num_pthread *data;

	data = (t_num_pthread *)arg;
	// printf("id %d\n", (*data).num);
	for (int i = 0; i < N_THREAD; i++){
		printf("id %d, i %d\n", data->num, i);
	}
	return ("finsh");
}

int main(void)
{
	pthread_t		v[N_THREAD];
	t_num_pthread	*data[N_THREAD];
	int				p_create;
	int				p_join;

	// for (int i = 0; i < N_THREAD; i++){
	// 	p_create = pthread_create(&v[i], NULL, test_pthread, (void *)i);
	// 	if (p_create != 0)
	// 		return (0);
	// }

	for (int i = 0; i < N_THREAD; i++){
		data[i] = (t_num_pthread *)malloc(sizeof(t_num_pthread));
		data[i]->num = i;
		p_create = pthread_create(&v[i], NULL, test_pthread, data[i]);
		printf("make thread\n");
		if (p_create != 0)
		{
			perror("pthread_create");
			return (0);
		}
	}

	for (int i = 0; i < N_THREAD; i++){
		char *ret
		p_join = pthread_join(v[i], (void **)&i);
		free(data[i]);
		if (p_join == 0)
			printf("finish ID %d\n", i);
		else
		{
			perror("pthread_join");
			return (0);
		}
	}
	return (0);
}