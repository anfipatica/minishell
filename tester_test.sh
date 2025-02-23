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
printf "${MAGENTA}Insert the command you want to test${STD}\n";
read -e command

result_bash=$(echo $command | bash 2>bash_error_log.txt)
result_minishell=$(echo $command | ./minishell 2>minishell_error_log.txt | tail +2 | head -n -1)

if [[ -s bash_error_log.txt || -s minishell_error_log.txt ]]; then
	printf "${GRAY}- · - · - · - · - · -< BASH ERROR EXIT >- · - · - · - · - · -${STD}\n"
	cat bash_error_log.txt
	printf "\n";
	printf "${GRAY}- · - · - · - · - ·< MINISHELL ERROR EXIT >- · - · - · - ·- -${STD}\n"
	cat minishell_error_log.txt
	printf "\n";
fi

if [[ -n $result_bash || -n $result_minishell ]]; then
	printf "${MAGENTA}- · - · - · - · - · -< BASH >- · - · - · - · - · -${STD}\n"
	echo "$result_bash"

	printf "${MAGENTA}· - · - · - · - · -< MINISHELL >- · - · - · - · - ${STD}\n"
	echo "$result_minishell"
else
	printf "${MAGENTA}Neither bash nor minishell had any ok output\n${STD}\n"
fi


if [ "$result_bash" == "$result_minishell" ]; then
	printf "${GREEN}NICE!${STD}\n"
else
	printf "${RED}KO :(!${STD}\n"
fi

rm bash_error_log.txt minishell_error_log.txt