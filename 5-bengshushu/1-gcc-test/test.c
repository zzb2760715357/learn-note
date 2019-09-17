#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096
#define MAX_SIZE 100*4096

int main()
{
	char *buf = (char *)malloc(MAX_SIZE);
	memset(buf,0,MAX_SIZE);
	printf("buffer address = %p\n",buf);

	free(buf);

	return 0;
}
