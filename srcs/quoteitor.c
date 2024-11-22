#include "minishell.h"

char *maybe_expanded(int *n, char *str, t_env *env)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[1]) == 1)
		return (NULL);
	if (!ft_isalpha(str[1]) && str[i] != '_')
		return (NULL);
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
	{
		i++;
	}
	*n += i;
	printf("in maybe_expanded: str = %s, len str = %d\n", str, i);
	return (ft_getenv(str + 1, env, i - 1));
}

t_token *expand_d_quote(char *start_quote, int length_dq, t_env *env)
{
	t_token	*token_d_quote;
	char	*str_before_dollar;
	char	*new_str;
	char	*expanded;
	char	*temp;
	char	*temp2;
	int		i; //contador de longitud del str literal
	int		n; //marca la posicion

	i = 0;
	n = 1;
	new_str = NULL;
	while (i < length_dq)
	{
		if (start_quote[i] != '$')
			i++;
		else if (start_quote[i + 1] == '$')
		{
			str_before_dollar = ft_substr(start_quote, n, i - n);
			get_pid_expandetor(&expanded);
			n = (i+=2);
			temp = ft_strjoin(str_before_dollar, expanded);
			free(str_before_dollar);
			free(expanded);
			temp2 = ft_strjoin(new_str, temp);
			free(new_str);
			free(temp);
			new_str = temp2;
		}
		else
		{
			str_before_dollar = ft_substr(start_quote, n, i - n);
			expanded = maybe_expanded(&i, &start_quote[i], env);
			n = i;
			temp = ft_strjoin(str_before_dollar, expanded);
			free(str_before_dollar);
			temp2 = ft_strjoin(new_str, temp);
			free(new_str);
			free(temp);
			new_str = temp2;
		}
	}
	str_before_dollar = ft_substr(start_quote, n, i - n - 1);
	token_d_quote = new_token(T_D_QUOTE, start_quote, length_dq);
	token_d_quote->expanded = ft_strjoin(new_str, str_before_dollar);
	token_d_quote->free_expanded = true;
	free(new_str);
	free(str_before_dollar);
	return (token_d_quote);
}

t_token *create_str_quote(char *start_quote, t_env *env)
{
	char	*finish_quote;
	int		length;
	finish_quote = ft_strchr(start_quote + 1, start_quote[0]);
	if (!finish_quote)
		return (NULL);
	length = ((finish_quote + 1) - start_quote);
	if (start_quote[0] == '\"')
		return (expand_d_quote(start_quote, length, env));
	return (new_token(T_S_QUOTE, start_quote, length));
}

void twin_quote(char *line)
{

	int i = 0;
	char quote_type;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i];
			i++;
			while (line[i] != '\0' && line[i] != quote_type)
			{
				i++;
				printf("HOLA YOLANDAA!\n");
			}	
		}
		if (line[i] == '\0')
			exit(22);
		i++;
	}
}

//" hola ' caca" 'hola "caca2'
















































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