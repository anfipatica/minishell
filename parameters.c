#include <stdio.h>

int main(int argc, char **v)
{
	int i = 0;

	while(i < argc)
	{
		printf("Param %d: %s\n", i, v[i]);
		i++;
	}
}

/*
prev: export z='a a' && gcc helpers/parameters.c -o params
- ./params $z 	 		2 params
- ./params "$z"			1 param
- ./params "$z"$z"$z"	2 params	
- ./params $z$z$z		4 params
- ./params "$z"$z$z		3 params
*/