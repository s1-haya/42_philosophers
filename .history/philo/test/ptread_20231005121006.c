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
	printf("id %d\n", (int)arg);
	// for (int i = 0; i < N_THREAD; i++){
	// 	printf("id %d, i %d\n", id, i);
	// }
	return (arg);
}

int main(void)
{
	pthread_t		v[N_THREAD];
	t_num_pthread	data;
	int				p_create;
	int				p_join;

	// for (int i = 0; i < N_THREAD; i++){
	// 	p_create = pthread_create(&v[i], NULL, test_pthread, (void *)i);
	// 	if (p_create != 0)
	// 		return (0);
	// }

	for (int i = 0; i < N_THREAD; i++){
		data.num = i;
		p_create = pthread_create(&v[i], NULL, test_pthread, );
		if (p_create != 0)
			return (0);
	}

	for (int i = 0; i < N_THREAD; i++){
		int id;
		p_join = pthread_join(v[i], (void **)&i);
		if (p_join == 0)
			printf("finish ID %d\n", id);
		else
			return (0);
	}
	return (0);
}