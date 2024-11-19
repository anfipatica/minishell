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
		{
			printf("ENTRAMOS ACÁAAA\n");
			return (get_pid_expandetor());
		}
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
	//el resto de condiciones

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
		if (ft_strchr("<>|$-", line[i]) != NULL) //plantear el tema de espacio como token
		{	
			//seguro tenemos token de simbolo:
			fresh_token = token_chooser(&line[i], env);
			add_token_back(&first_token, fresh_token);
			i += fresh_token->length;
		}
		else if (ft_strchr("\"\'", line[i]) != NULL) //Ha encontrado una de las comillas " o '
		{
			//llamamos la funcion IS_CLOSED_QUOTEITOR que averigua si las commillas se cierran
		}
		else if (' ' == line[i])
			i++;
		else
		{
			printf("line es: '%s'\n", &line[i]);
			word_len = 0;
			//Es parte de un token word.
			// while(ft_strchr( " \t", line[i]) != NULL)
			// 	i++;
			while (line[i + word_len] && ft_strchr("\"\'<>|$- ", line[i + word_len]) == NULL)
				word_len++;
			printf("longitud palabras:%d\n", word_len);
			fresh_token = new_token(T_WORD, &line[i], word_len);
			add_token_back(&first_token, fresh_token);
			i += word_len;
		}
	}
	return (first_token);
}
