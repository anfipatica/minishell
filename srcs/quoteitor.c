#include "minishell.h"

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