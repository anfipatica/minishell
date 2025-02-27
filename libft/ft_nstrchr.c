#include "libft.h"

int	ft_nstrchr(const char *s, int c)
{
	int		i;
	char	character;

	character = (char)c;
	i = 0;
	if (character == '\0')
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}