#include "minishell.h"


//TODO aqui vamos a crear una funcion che vaya guardado el path del comando en la estuctura del path
//TODO recive el dondo contenete el ipotetico comando y si existe guarda el pat en el mismo nodo


char *is_acces(t_args *arg, t_env *env)
{

}


void path_finder(t_token *token, t_env *env)
{
	t_command *command;
	command = new_command();
	command->args = new_args();

	command->args = ft_ternary(token->expanded, token->str, token->expanded);
	command->path_command = is_acces(command->args, env);
}

/* 
esto es el eejjeemplo para entender la funcion ternaria
#include <stdbool.h>
#include <stdio.h>

int main(void)
{bool genero;
char str[] = "bebe";
genero = false;
	printf("%s\n", ft_ternary("vivo", "muerto", NULL));
} */