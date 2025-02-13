NAME = minishell

CC = cc

#CFLAGS	 =	-Wextra -Wall -Werror -Wunreachable-code
CFLAGS	+= -I inc
CFLAGS	+= -I libft
CFLAGS	+= -O3
CFLAGS	+= -g3

READLINE	= -lreadline

#DEBUG	 =	-fsanitize=address

CPPFLAGS =	-MMD
LIBFT	= ./libft

HEADERS = -I ./inc -I $(LIBFT)

LIBS	+=	$(LIBFT)/libft.a

SRC_DIR = srcs/
LIST_DIR = list_functions/
PRINT_DIR = printers/
PEPEX_DIR = srcs/pepex/

SRCS =											\
		$(SRC_DIR)$(LIST_DIR)list_token.c		\
		$(SRC_DIR)$(LIST_DIR)list_env.c			\
		$(SRC_DIR)$(LIST_DIR)list_command.c		\
		$(SRC_DIR)$(LIST_DIR)list_redirect.c	\
		$(SRC_DIR)$(LIST_DIR)list_args.c		\
		$(SRC_DIR)$(PRINT_DIR)get_token_name.c	\
		$(SRC_DIR)$(PRINT_DIR)printers.c		\
		$(SRC_DIR)/built-ins/cd.c				\
		$(SRC_DIR)/built-ins/echo.c				\
		$(SRC_DIR)/built-ins/env.c				\
		$(SRC_DIR)/built-ins/exit.c				\
		$(SRC_DIR)/built-ins/export.c			\
		$(SRC_DIR)/built-ins/pwd.c				\
		$(SRC_DIR)/built-ins/unset.c			\
		$(SRC_DIR)main.c						\
		$(SRC_DIR)promptereitor.c				\
		$(SRC_DIR)tokenizer.c					\
		$(SRC_DIR)expandetor.c					\
		$(SRC_DIR)quoteitor.c					\
		$(SRC_DIR)env.c							\
		$(SRC_DIR)freedom.c						\
		$(SRC_DIR)quote_expandetor.c			\
		$(SRC_DIR)quotes_token_create.c			\
		$(SRC_DIR)automata.c					\
		$(SRC_DIR)automata_func.c				\
		$(SRC_DIR)list_checker.c				\
		$(PEPEX_DIR)commander.c					\
		$(PEPEX_DIR)here_dokeitor.c				\
		$(SRC_DIR)executor.c					\
		$(SRC_DIR)error.c						\
		$(SRC_DIR)builtins_handler.c				\
		$(SRC_DIR)fd_handler.c					\
		$(SRC_DIR)signals.c					\


OBJS = $(patsubst srcs/%.c, objs/srcs/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(DEBUG) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(READLINE) && printf "Linking: $(NAME)\n"

objs/srcs/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf objs
	@rm -rf $(LIBMLX)/build
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

-include $(DEPS)

r: run
run: all
	@./$(NAME)

v: valgrind
valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
#@valgrind --leak-check=full --track-fds=yes --trace-children=yes ./$(NAME)

.PHONY: all clean fclean re libmlx libft r run v valgrind
