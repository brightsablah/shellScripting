#include <stdio.h>

//eternal variable defined in the system library
extern char **environ;

/**
 * main - compares environment variable addresses
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
  printf("environ address = %p\n", environ);
  printf("env address = %p\n", env);

    return (0);
}
