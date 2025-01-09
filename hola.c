#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	unsigned long hola = strdup("hola");

	unsigned long arg = hola;

	printf("%p %p\n", hola, arg);


	free(hola);
	hola = NULL;

	printf("%p %p\n", hola, arg);

	// char    *algo;
	// int     a;
	// algo = 11;
	// printf("%p\n", algo);

}