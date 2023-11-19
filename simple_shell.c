#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main(void)
	{
	char command[MAX_COMMAND_LENGTH];
	int status;

	while (1)
	{
	printf("#$ ");
	if (fgets(command, sizeof(command), stdin) == NULL)
	{
	printf("\n");
	break;
}

	/* Remove the trailing newline character*/
	command[strcspn(command, "\n")] = 0;

	pid_t pid = fork();

	if (pid == -1)
	{
	perror("fork");
	exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	/*Child process*/
	execlp(command, command, NULL);
	/* If exec returns, an error occurred*/
	perror(command);
	exit(EXIT_FAILURE);
	}
	else
	{

	/* Parent process */
	waitpid(pid, &status, 0);
	}
}
	return (EXIT_SUCCESS);
}
