#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long	getMsTime(struct timeval *tv)
{
	if (gettimeofday(tv, NULL) == -1)
		return (-1);
	return (tv->tv_sec + tv->tv_usec / 1000);
}

// int main(void)
// {
// 	struct timeval tv;
// 	long	ms;

// 	ms = getMsTime(&tv);
// 	if (ms < 0)
// 		return (0);
// 	printf("ms      %ld\n", ms);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	usleep(1000);
// 	printf("ms      %ld\n", getMsTime(&tv) - ms);
// 	return (0);
// }