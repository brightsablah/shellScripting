#include <stdio.h>
#include <unistd.h>

int main()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t getline_return;

	printf("$ ");

	getline_return = getline(&line, &len, stdin);

	if (getline_return != -1)
		printf("%s", line);
	else
		printf("Error reading input.\n");

return (0);
}
