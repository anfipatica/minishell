#include "minishell.h"
/* 
	printf("position_of_equal: %lu\n", position_of_equal);
	printf("str_with_equal + 1: %lu\n", str_with_equal);
	printf("position_of_equal - str_with_equal + 1: %lu\n", position_of_equal - str_with_equal + 1); */

#define KERMIT "\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡴⠞⠛⠉⠉⠉⠛⠓⢦⣄⠀⠀⢀⣤⣤⣄⠀⠀⠀⣀⣠⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡞⠋⠀"WHITE"⣀⣤⣤⣤⣤⣤"GREEN"⠀⠀⠘⢶⡀⠀⠀⠀⠀⣠⡶⠛⠉⠀⠀⠀⠀⠀⠙⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡏⠀⠀"WHITE"⢸⣿⣿⣿⡟⠉⠉"GREEN"⠀⠀⠀⣠⡇⠀⠀⠀⠀⢿⡇⠀⠀⠀"WHITE"⠸⣿⣦⣄⣀⡀"GREEN"⠈⢷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀"WHITE"⢤⣿⡟⠉⠉⠁"GREEN"⠀⠀⢀⣠⠾⠛⠁⠀⠀⠀⠀⠀⠷⣄⠀⠀⠀"WHITE"⠨⢿⣿⣿⣷⢀"GREEN"⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀"WHITE"⠈⠉"GREEN"⠀⠀⠀⢀⣤⠶⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⡀⠀⠀"WHITE"⠈⠛⢿⣇⢠"GREEN"⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⠞⠉⠙⣇⣀⣀⣀⣤⠴⠚⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⡀⠀"WHITE"⠀⠸⠿⠘⡀"GREEN"⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⣠⠜⠛⠁⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⣄⠀⠀⠀⣱⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⢁⣶⠀⠀⢀⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠶⠶⠋⠓⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⣾⢁⡟⣻⠀⠀⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢶⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢰⡏⣸⠀⢿⣇⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠘⡇⣿⠀⢸⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠁⢻⡆⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⣷⢻⣧⠈⠉⢻⣧⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⢴⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⢹⡌⣿⠀⠀⠳⢿⡀⠀⠉⠳⢦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⡿⠉⣼⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⡘⣇⠀⠀⠘⣷⡀⠀⠀⠀⠉⠓⢷⣶⣦⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠚⠉⠀⠀⠀⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣨⣧⢹⡀⠀⠀⠈⢷⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠛⠻⠿⠿⠛⠛⠛⠛⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣥⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⢀⣤⠴⠛⠉⢀⣄⣠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣵⠃⠀⡀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⣀⡴⠞⠉⠁⠀⣠⣴⡿⠻⠉⣷⠀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡼⣫⠟⠁⢀⡾⠁⠀⠀⠀⠀⠀⠀⠀\n\
⠚⣉⢤⣶⡶⢖⡿⠟⠁⠀⠀⠀⣿⡇⠈⢷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⠾⠋⠞⠁⠀⡰⠏⠁⠀⣀⠀⠀⠀⠀⠀⠀\n\
⣫⠗⠛⠁⠀⠉⠀⠀⠀⠀⠀⠀⣿⣷⠀⢠⡙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡿⠛⠉⠀⠀⠀⠀⠀⣀⣤⠞⠁⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⡀⠀⢷⣌⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣼⡿⠋⠀⠀⠀⠀⠀⣠⡴⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣽⣿⣇⠀⠀⠹⣦⡘⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⣿⡏⠀⠀⠀⠀⢀⣴⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⢀⡰⠖⠀⠂⠀⢬⠹⣿⣿⡄⠀⠀⠸⣧⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠏⢠⡟⠁⠀⠀⠀⢠⡿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⢹⣿⡇⠀⠀⠀⠙⢷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⣸⡇⠀⠀⠀⠀⠈⢻⡙⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⠀⠀⠀⠀⠀⠙⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠇⠀⠀⢿⡇⠀⠀⠀⠀⠀⠀⠳⢻⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠃⠀⢀⠀⠺⣇⠀⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡄⠀⠀⠀⠹⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡿⠃⠀⠀⠈⢧⡀⢿⡀⠀⠀⠀⠀⠀⠀⠀⠈⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⢀⣀⣀⡤⠶⠖⠊⠉⠉⣿⠁⠀⠀⠀⠀⠈⠛⠻⣶⠶⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠈⢇⢸⣧⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠉⠛⠛⠗⠒⠒⠂⠀⠒⠂⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⢻⡆⠀⠀⠀⠀⠀⠀⠀⠘⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠈⢷⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⣄⡀⠀⠀⠀⠀⢸⣇⠀⠀⠀⠀⠀⠀⠀⠈⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢀⡾⠀⠀⠀⠀⠀⠀⠀⢀⣴⠞⢹⡆⠀⠀⠀⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣶⣄⡀⠀⠀⢻⡆⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⢀⡾⠁⠀⠀⠀⠀⠀⢀⣴⠏⠁⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⣰⣿⡀⠀⠀⠀⠀⢸⣿⡟⠛⠁⠉⠙⠻⠶⣤⣈⣧⠀⠀⠀⠀⠀⠀⠀⠀⠷⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⣾⠁⠀⠀⠀⠀⣠⡴⠋⠁⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⢠⡟⠘⣷⠀⠀⠀⢀⡿⢿⣇⠀⠀⠀⠀⠀⠀⠀⠙⢿⡆⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⣾⠃⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⣾⠃⢀⣿⡄⠀⠀⣼⠁⠀⢻⣧⠀⠀⠀⠀⠀⠀⠀⠘⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⢀⣴⡟⠀⠀⣠⠾⠉⠀⠀⠀⠀⠀⠀⠀⠀⢠⡇⠀⠀⠀⠀⠀⣼⠇⠀⠀⠻⣇⠀⠀⣿⠀⠀⠈⢻⣧⠀⠀⠀⠀⠀⠀⠀⢹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠸⣿⠁⣠⡾⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⣸⠏⠀⡄⡀⠀⣿⠀⠀⡇⠀⠀⠀⣠⣿⣇⠀⠀⠀⠀⠀⠀⠈⠿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⣿⡼⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⢰⡇⠀⠀⠀⠀⢸⣿⠀⢰⡇⢀⣤⣾⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⢠⡏⠀⠀⠀⠀⠀⠰⣿⠀⣸⣷⣿⣿⣿⡿⠛⠹⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⢠⡟⠀⠀⠀⠀⠀⠀⠀⣿⢠⣿⣿⣿⣿⠏⠀⠀⠀⠘⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠇⣰⠟⠀⠀⠀⠀⠀⠀⠀⠀⠉⣾⣿⡿⡿⠁⠀⠠⠀⠀⠀⠈⠅⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣧⠀⠀⠀⠈⠀⠀⠀⠀⠶⠚⢻⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⢠⡶⠄⠀⣀⣠⣤⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠏⢀⠀⠀⣤⣦⡴⢛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣤⣤⣤⣶⣶⣾⣿⣿⣿⣿⣧⣭⣤⣤⣤⣤⣤⣤⣤⣼⣤⣤⣤⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀\n"

// TODO: export ?=hi

void	print_kermit(void)
{
	printf(GREEN""KERMIT""STD);
	printf(RED
		"\n%22sSorry, the manual says:\n"
		"%5sWhen no arguments are given, the results are unspecified.\n"
		"%8sSo this is the result our minishell implements <3\n\n"
		STD"%20sFollow link (ctrl + click)\n"
		"%5s"PURPLE"https://www.man7.org/linux/man-pages/man1/export.1p.html\n"STD,
		"", "", "", "", "");
}


bool	valid_var_name(char	*name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) == 1)
		return (false);
	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	if_exist_var_overwrite(t_env *env, t_env *var)
{
	while (env)
	{
		if (ft_strcmp(env->name, var->name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(var->value);
			ft_free_one_env(var);
			return true;
		}
		env = env->next;
	}
	return (false);
}

int ft_export(t_command *command)
{
	t_env		*var;
	t_args		*arg;
	bool		error;

	arg = command->args->next;
	if (arg == NULL)
		return (print_kermit(), 0);
	while (arg)
	{
		var = create_node_env(arg->name);
		if (!var)
		{
			print_error(arg->name, INVALID_EXPORT_IDENTIFIER);
			error = true;
		}
		else if (if_exist_var_overwrite(command->env, var) == false)
		{
			add_env_back(&command->env, var);
		}
		arg = arg->next;
	}
	return (error);
}
