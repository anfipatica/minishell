#include "minishell.h"

int	dup2_openeitor(char *file, int flags, mode_t mode, int system_fd)
{
	int	file_fd;

	file_fd = open(file, flags, mode);
	if (file_fd == -1)
	{
		perror(file);
		return OPEN_ERROR;
	}
	if (dup2(file_fd, system_fd) == -1)
		return (perror(file), OPEN_ERROR);
	close(file_fd);
	return (file_fd);
}

int	handle_files(t_redirect *file)
{
	int	state;

	state = 0;
	while (file && state != OPEN_ERROR)
	{
		if (file->redirect_type == T_REDIRECT_RIGHT)
			state = dup2_openeitor(file->name, O_REDIRECT_RIGHT, STD_PERMISSIONS, OUT_FILE);
		else if (file->redirect_type == T_APPEND)
			state = dup2_openeitor(file->name, O_REDIRECT_APPEND, STD_PERMISSIONS, OUT_FILE);
		else if (file->redirect_type == T_HERE_DOC)
			state = dup2_openeitor(file->name, O_HERE_DOC, 0, IN_FILE);
		else if (file->redirect_type == T_REDIRECT_LEFT)
			state = dup2_openeitor(file->name, O_REDIRECT_LEFT, 0, IN_FILE);
		if (file->redirect_type == T_HERE_DOC)
			unlink(file->name);
		file = file->next;
	}
	return (state);
}