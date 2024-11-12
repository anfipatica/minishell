#include "../inc/minishell.h"

// TOKEN: | < << > >> $ WORD ' '


// crear la funcion IS_CLOSED_QUOTEITOR(puntero a la primera comilla)
	//if (line[i] == '\"')
	//	tenemos que encotrar la otra que cierra
	//if (line[i] == '\'')
	//	tenemos que encotrar la otra que cierra

// crear la funcion TOKEN_SIMBOLIZER que vaya trabajando sobre estos casos:
			//una funcion si el caracter se '<'
			//una funcion si el caracter se '>'
			//una funcion si el caracter se '|'
			//una funcion si el caracter se '$'

t_token	*tokenizer(char *line)
{
	t_token	*token;
	int		i;
	int		word_len;

	i = -1;
	word_len = 0;
	token = NULL;
	while (line[++i])
	{
		if (ft_strchr( "<>|$ ", line[i]) != NULL) //plantear el tema de espacio como token
		{
			//llamamos la funcion TOKEN_SIMBOLIZER(line[i]);
		}
		else if (ft_strchr( "\"\'", line[i]) != NULL) //Ha encontrado una de las comillas " o '
		{
			//llamamos la funcion IS_CLOSED_QUOTEITOR que averigua si las commillas se cierran
		}
		else
		{
			//Es parte de un token word.
			word_len++;
			if (line[i + 1] == '\0')
			{
				token = new_token(T_WORD, &line[i - (word_len - 1)], word_len);
			}
		}
	}
	return (token);
}
