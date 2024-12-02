int main(int argc, char **argv)
{
	int i = 0;
	while (i < argc)
	{
		printf("Arg: %d Value: %s\n", i, argv[i]);
		i++;
	}
}