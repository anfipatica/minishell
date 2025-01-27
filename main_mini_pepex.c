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

	// char *path = "/bin/cat";
	// char *args[] = {"cat", "-e", NULL};

	// char *outs[] = {"file2", NULL};

	// int i = 0;
	// while (outs[i])
	// {
	// 	int new_fd = open(outs[i], O_RDONLY);
	// 	if (new_fd == -1)
	// 	{
	// 		perror(outs[i]);
	// 		exit(1);
	// 	}
	// 	dup2(new_fd, 0);
	// 	close(new_fd);
	// 	dprintf(2, "delete now!!!\n");
	// 	sleep(10);
	// 	dprintf(2, "resume\n");

	// 	//unlink(outs[i]);
	// 	i++;
	// }
	

	// execve(path, args, env);
	char *path = "/bin/cat";
	char *args[] = {"cat", "-e", NULL};

	char	buffer[50] = {0};

	int fd0 = open("hola", O_RDONLY);
	int fd1 = open("hola", O_WRONLY + O_APPEND);
	perror("before");
	dup2(fd0, 0);
	write(fd1, "0123456789\n", 11);
	read(fd0, buffer, 4);
	close(fd0);
	printf("---> [%s]\n", buffer);
	unlink("hola");
	execve(path, args, env);

	int fd2 = open("hola", O_RDONLY);
	perror("after");


}