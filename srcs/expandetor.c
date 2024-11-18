#include "minishell.h"

char	*expandetor(char *str)
{
//	printf("string orniginal llegado = %s\n", str);
	int		i;
	char	*temp_word;
	char	*env_exp;

	if (ft_isdigit(str[0]) == 1)
		return (NULL);
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (NULL);
	i = 0;
	while (str[i] && ft_isalnum(str[i]) == 1)
		i++;
	temp_word = ft_substr(str, 0, i);
	printf("temp_wold: %s\n", temp_word);
	env_exp = getenv(temp_word); //getenv no hace malloc, no hay que liberar!!!!
	free(temp_word);
	return (env_exp);
}