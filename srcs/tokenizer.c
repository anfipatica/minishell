#include "minishell.h"

// TOKEN: | < << > >> $ WORD ' '


// crear la funcion IS_CLOSED_QUOTEITOR(puntero a la primera comilla)
	//if (line[i] == '\"')
	//	tenemos que encotrar la otra que cierra
	//if (line[i] == '\'')
	//	tenemos que encotrar la otra que cierra

// crear la funcion TOKEN_SIMBOLIZER que vaya trabajando sobre estos casos:
			//va encasquetando segun el simbolo e tipo de token:
				//una funcion si el caracter se '<'
				//una funcion si el caracter se '<< + identificador'
				//una funcion si el caracter se '>'
				//una funcion si el caracter se '>>'
				//una funcion si el caracter se '|'
				//una funcion si el caracter se '$'

t_token	*symbol_tokenizer(t_token_value type, char *line, int n_symbol)
{
	int		i;

	i = 0;
	if (line[i + n_symbol] != '\0' && line[i + n_symbol] <= ' ')
		i++;
	while (line[i + n_symbol] && ft_strchr(SYMBOLS, line[i + n_symbol]) == NULL)
	{
		i++;
	}
	return (new_token(type, line, i + n_symbol));
}

t_token *create_str_quote(char *start_quote)
{
	char	*finish_quote;
	int		length;
	finish_quote = ft_strchr(start_quote + 1, start_quote[0]);
	if (!finish_quote)
		return (NULL);
	length = ((finish_quote + 1) - start_quote);
		printf("length: %d\n", length);



	if (start_quote[0] == '\"')
		return (new_token(T_D_QUOTE, start_quote, length));
	return (new_token(T_S_QUOTE, start_quote, length));
}

t_token	*token_chooser(char *line, char **env)
{
	(void) env;
	if (line[0] == '<')
	{
		if (line[1] && line[1] == '<')
			return (new_token(T_HERE_DOC, line, 2));
		else
			return (new_token(T_REDIRECT_LEFT, line, 1));
	}
	if (line[0] == '>')
	{
		if (line[1] && line[1] == '>')
			return (new_token(T_APPEND, line, 2));
		else
			return (new_token(T_REDIRECT_RIGHT, line, 1));
	}
	if (line[0] == '|')
		return (new_token(T_PIPE, line, 1));
	if (line[0] == '$')
	{
		if (line[1] && line[1] == '$')
			return (get_pid_expandetor());
		else
			return (expandetor(line));
	}
	if (line[0] == '-')
	{
		if (line[1] && line[1] == '-')
			return (new_token(T_FLAG, line, 2));
		else
			return (new_token(T_FLAG, line, 1));
	}
	if (line[0] == '\'' || line[0] == '\"')
		return (create_str_quote(line));
	return (NULL);
}	

t_token	*tokenizer(char *line, char **env)
{
	t_token	*fresh_token;
	t_token	*first_token;
	int		i;
	int		word_len;

	i = 0;
	first_token = NULL;
	while (line[i])
	{
		if (ft_strchr("<>|$-\"\'", line[i]) != NULL) //plantear el tema de espacio como token
		{	
			//seguro tenemos token de simbolo:
			fresh_token = token_chooser(&line[i], env);
//			SI FERSH_TOKEN ES NULL free(TODO);
			add_token_back(&first_token, fresh_token);
			i += fresh_token->length;
		}
/*		else if (ft_strchr("\"\'", line[i]) != NULL) //Ha encontrado una de las comillas " o '
		{
			//llamamos la funcion IS_CLOSED_QUOTEITOR que averigua si las commillas se cierran
		}*/
		else if (' ' == line[i])
			i++;
		else
		{
			word_len = 0;
			while (line[i + word_len] && ft_strchr("\"\'<>|$- ", line[i + word_len]) == NULL)
				word_len++;
			fresh_token = new_token(T_WORD, &line[i], word_len);
			add_token_back(&first_token, fresh_token);
			i += word_len;
		}
	}
	return (first_token);
}
