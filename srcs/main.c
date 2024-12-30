#include "minishell.h"

/* typedef struct s_var
{
	char *name;
	char *value;
} t_var;

char *color;
// Delegado tipo Action
void print_list(void *content)
{
	t_var	*var = (t_var *)content;

	printf("%sname: %s\nvalue: %s\n\n", color, var->name, var->value);
}

// Delegado tipo Predicate
bool find(void *content, void *context)
{
	t_var	*var = (t_var *)content;

	(void)context;
	// if (!ft_strcmp(var->name, context))
	if (ft_strlen(var->name) < 8)
		return true;
	return false;
}

// Delegado tipo Action
void del_node(void *content)
{
	if (!content)
		return ;

	t_var	*var = (t_var *)content;

	printf("Deleting: %s\n", var->name);

	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free (content);
}

int	main(int argc, char **argv, char **env_original)
{
	t_list	*list_vars = NULL;
	t_var	*var;
	t_list  *new_node = NULL;

	int j;
	int i = -1;
	while (env_original[++i] != NULL)
	{
		j = 0;
		while (env_original[i][j] != '=')
			j++;

		var = malloc(sizeof(t_var));
		var->name = ft_substr(env_original[i], 0, j);
		var->value = ft_substr(env_original[i], j + 1, ft_strlen(env_original[i]));
		new_node = ft_lstnew(var);
		ft_lstadd_back(&list_vars, new_node);
	}

	color = RED;
	ft_lstiter(list_vars, print_list);

	t_var *finded_var = ft_lstfind(list_vars, "COLORTERM", find);
	if (finded_var)
		printf("Se encontró\n");
	else
		printf("No se encontró\n");


	ft_lstdel(&list_vars, "COLORTERM", find, del_node);

	color = GREEN;
	ft_lstiter(list_vars, print_list);

	(void)argv;
	(void)argc;

	return (0);
} */

int	main(int argc, char **argv, char **env_original)
{
	t_list	*list_env;

	(void)argv;
	if (argc != 1)
		return (1);
	list_env = copy_env(env_original);
	promptereitor(list_env);
	ft_lstclear(&list_env, ft_free_env);
	return (0);
}
//TODO	da segfoul: revisar list check
//TODO continua modificar las listas desde el list check
//TODO abrazar a yolanda!

//TODO	clasificar las palabras
//TODO	tenemos que implementar las multiridirecions del pipex;
//TODO	hacer los buldings que son relativamente faciles
//TODO	implementar las siñales
//TODO	incrustrarle el pipex que funcione!
//- 	LO TENEMOS!