# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stddef.h>

int main(int argc, char **argv, char **env)
{
	(void)argc, (void)argv;

	char *path = "/bin/ls";
	char *args[] = {"ls", "-la", NULL};

	char *outs[] = {"salida1", "salida2", "salida3", NULL};

	int i = 0;
	while (outs[i])
	{
		int new_fd = open(outs[i], O_WRONLY | O_CREAT, 0666);
		if (new_fd == -1)
		{
			perror(outs[i]);
			exit(1);
		}
		dup2(new_fd, 1);
		close(new_fd);
		i++;
	}
	

	execve(path, args, env);
}