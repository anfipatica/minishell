NAME = minishell

CC = cc

CFLAGS	 =	-Wextra -Wall -Werror -Wunreachable-code
CFLAGS	+= -I inc
CFLAGS	+= -I libft
CFLAGS	+= -O3

READLINE	= -lreadline

#DEBUG	 =	-g3 -fsanitize=address

CPPFLAGS =	-MMD
LIBFT	= ./libft

HEADERS = -I ./inc -I $(LIBFT)

LIBS	+=	$(LIBFT)/libft.a


SRCS =											\
		srcs/main.c								\
		srcs/promptereitor.c					\
		srcs/tokenizer.c						\
		srcs/list_token.c						\
		srcs/get_token_name.c					\
		srcs/expandetor.c						\
		srcs/quoteitor.c						\
		srcs/list_env.c							\
		srcs/env.c								\
		srcs/freedom.c							\
		srcs/quote_expandetor.c					\
		srcs/quotes_token_create.c				\
		srcs/automata.c				\



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

.PHONY: all clean fclean re libmlx libft
