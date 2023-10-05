#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *str;
	char *new_str;

	str = calloc(4, sizeof(char));
	printf("str %s\n", str);
	new_str = memset(str, 'z', 3);
	printf("str %s\n", new_str);
	return (0);
}
