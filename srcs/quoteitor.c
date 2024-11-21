#include "minishell.h"

char *maybe_expanded(int *n, char *str, t_env *env)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[1]) == 1)
		return (NULL);
	if (ft_isalpha(str[1]) == 0 && str[i] != '_')
		return (NULL);
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
	{
		i++;
	}
	*n += i;
	if (str)
		printf("str = %s, i = %d\n", str, i);
	return (ft_getenv(str + 1, env, i - 1));
}

t_token *expand_d_quote(char *start_quote, int length, t_env *env)
{
	t_token	*token;
	char	*substr;
	char	*new_str;
	char	*expanded;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	substr = NULL;
	new_str = NULL;
	while (start_quote[i])
	{
		if (start_quote[i] == '$')
		{
			printf("j = %d, i = %d\n", j, i);
			printf("%c - %c\n", start_quote[j], start_quote[i]);
			substr = ft_substr(start_quote, j, i - j);
			printf("substr = %s\n", substr);
			expanded = maybe_expanded(&i, &start_quote[i], env);
			printf("expanded = %s\n", expanded);
			j = i;
			temp = ft_strjoin(substr, expanded);
			printf("temp = %s\n", temp);
			new_str = ft_strjoin(new_str, temp);
			printf("new_str = %s\n", new_str);
			free(substr);
			substr = NULL;
			printf("--------------------\n");
	
		}
		else
			i++;
	}
	// if (!substr)
	// {
	// 	printf("ENTRO AQUÍ POR QUÉ ENTRO AQUÍ\n");
	substr = ft_substr(start_quote, j, i - j - 1);
	//}
	printf("FUERA DEL BUCLE OLÉ\n");
	token = new_token(T_D_QUOTE, start_quote, length);
	printf("new_str = %s, substr = %s\n", new_str, substr);
	token->expanded = ft_strjoin(new_str, substr);
	printf("token_expanded = %s\n", token->expanded);
	token->free_expanded = true;
	free(new_str);
	free(substr);
	return (token);
}



t_token *create_str_quote(char *start_quote, t_env *env)
{
	char	*finish_quote;
	int		length;
	finish_quote = ft_strchr(start_quote + 1, start_quote[0]);
	if (!finish_quote)
		return (NULL);
	length = ((finish_quote + 1) - start_quote);
		printf("length: %d\n", length);



	if (start_quote[0] == '\"')
		return (expand_d_quote(start_quote, length, env));
	return (new_token(T_S_QUOTE, start_quote, length));
}


// void is_even_quote(char *line)
// {
// 	int	i;
// 	int	doble_quote_n;
// 	int	single_quote_n;

// 	i = 0;
// 	doble_quote_n = 0;
// 	single_quote_n = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\"')
// 			doble_quote_n++;
// 		if (line[i] == '\'')
// 			single_quote_n++;
// 		i++;
// 	}
// 	printf("DOBLE: %d\n", doble_quote_n);
// 	printf("SINGLE: %d\n", single_quote_n);

// 	if (doble_quote_n % 2 != 0 || single_quote_n % 2 != 0)
// 		exit(77);
//  }

// bool is_closed_quote(char *line)
// {
// 	int	i;

// 	i = 1;
// 	while (line[i] != '\0' && line[i] != line[0])
// 		i++;
// /*
// 	if (line[i] == '\"')
// 	{

// 	}
// 	else
// 		exit(88);
// 	*/
// }
// void twin_quote(char *line)
// {
	
	
// int len_expanded(char *var)
// {
// 	return (ft_strlen(getenv(var)));
// }