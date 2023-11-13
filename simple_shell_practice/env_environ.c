#include <stdio.h>

//eternal variable defined in the system library
extern char **environ;

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(void)
{
  char **env;
  
// iterating through the environment variables
  for (env = environ; *env != NULL; env++)
    {
    // printing the environment variables
      printf("%s\n", *env);
    }
  
    return (0);
}
