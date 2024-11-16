#include "minishell.h"

char	*expandetor(char *str)
{
//	printf("string orniginal llegado = %s\n", str);
	int		i;
	char	*temp_word;
	char	*env_exp;

	i = 0;
	if (str[i - 1] != '$')
		return (NULL);
//	printf("ES UN $?: %c\n", str[i - 1]);
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (NULL);		
//	printf("ES UN H?: %c\n", str[i]);
	while (ft_strchr("\0<>|$-", str[i]) == NULL && str[i] != ' ')
			i++;
	temp_word = (ft_substr(str, 0, i));
	env_exp = getenv(temp_word);
//	printf("Plabra da expandir = %s\n", temp_word);
	free(temp_word);
//	printf("env_exp = %s\n", env_exp);	
	return (env_exp);
}