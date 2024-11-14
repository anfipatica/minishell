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

t_token	env_expander(char **env)
{

}

t_token	*token_chooser(char *line, char **env)
{
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
		return (new_token(T_ENV, line, 1));
	//el resto de condiciones

	return (NULL);
}


t_token	*tokenizer(char *line)
{
	t_token	*fresh_token;
	t_token	*first_token;
	int		i;
	int		word_len;

	i = 0;
	first_token = NULL;
	while (line[i])
	{
		if (ft_strchr("<>|$", line[i]) != NULL) //plantear el tema de espacio como token
		{	
			//seguro tenemos toke de simbolo:
			//llamamos la funcion TOKEN_SIMBOLIZER(line[i]);
			fresh_token = token_chooser(&line[i]);
			add_token_back(&first_token, fresh_token);
			i += fresh_token->length;
		}
		else if (ft_strchr("\"\'", line[i]) != NULL) //Ha encontrado una de las comillas " o '
		{
			//llamamos la funcion IS_CLOSED_QUOTEITOR que averigua si las commillas se cierran
		}
		else if (ft_strchr(" ", line[i]) != NULL)
			i++;
		else
		{
			word_len = 0;
			//Es parte de un token word.
			// while(ft_strchr( " \t", line[i]) != NULL)
			// 	i++;
			while (line[i + word_len] && ft_strchr("\"\'<>|$ \0", line[i + word_len]) == NULL)
				word_len++;
			fresh_token = new_token(T_WORD, &line[i], word_len);
			add_token_back(&first_token, fresh_token);
			printf("longitud palabras:%d\n", word_len);
			i += word_len;
		}
	}
	return (first_token);
}
