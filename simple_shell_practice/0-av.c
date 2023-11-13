#include <stdio.h>
#include <unistd.h>

int main(int ac, char *av[])
{
	while(*av)
	{
		printf("%s ", *av);
		av++;
	}
	printf("\n");
	return (0);
} 
