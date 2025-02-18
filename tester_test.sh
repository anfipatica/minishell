#!/bin/bash

STD='\033[0;39m'
BLACK='\033[0;30m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
GRAY='\033[0;90m'
WHITE='\033[0;97m'

FILE=./minishell

if [ -x "$FILE" ]; then
	printf "${GREEN}Todo correcto mi pana.${STD}\n"
else
	printf "${RED}MINISHELL EXECUTABLE NOT FOUND.${STD}\n";
	exit 1
fi

clear
printf "${MAGENTA}Insert the command you want bash to test${STD}\n";

read command

result_bash=$(echo $command | bash)
result_minishell=$(echo $command | ./minishell | tail +2 | head -n -1)

printf "${MAGENTA}- · - · - · - · - · -< BASH >- · - · - · - · - · -${STD}\n"
echo "$result_bash"
printf "${MAGENTA}- · - · - · - · - · - · - · - · - · - · - ·  - · -${STD}\n"


printf "${MAGENTA}· - · - · - · - · -< MINISHELL >- · - · - · - · - ${STD}\n"
echo "$result_minishell"
printf "${MAGENTA}- · - · - · - · - · - · - · - · - · - · - ·  - · -${STD}\n"

if [ "$result_bash" == "$result_minishell" ]; then
	printf "${GREEN}NICE!${STD}\n"
else
	printf "${RED}KO :(!${STD}\n"
fi

