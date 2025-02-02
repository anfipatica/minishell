#include "libft.h"

char	*ft_ternary( bool condition, char *true_case, char *false_case)
{
	if (condition)
		return (true_case);
	return (false_case);
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