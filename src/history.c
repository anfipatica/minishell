#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while ((s1[i] || s2[i]) && i < n)
		{
			if (s1[i] != s2[i])
				return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
			i++;
		}
	}
	return (0);
}

int	main(void)
{
	char	*line;
	line = readline("Prompt > ");
	while (ft_strncmp(line, "q", 2))
	{
		
		if (*line)
			add_history(line);
		rl_on_new_line();
		free(line);
		line = readline("Prompt > ");
	}
	free(line);
	rl_clear_history();
	return (0);
}

