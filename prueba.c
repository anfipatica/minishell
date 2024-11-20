#include <stdio.h>
#include <string.h>

int main(void)
{
    char *line = strdup("A=vscode");

    char *pos = strchr(line, '=');

    printf("%p\n%p\n%ld\n", line, pos, pos - line);

}