NAME			=	pipex
BONUS 			= 	pipex_bonus

SHARED 			= 	\
					child.c\
					commander.c\
					here_docereitor.c\
					GNL/get_next_line_bonus.c\
					GNL/get_next_line_utils_bonus.c

SRCS			= 	\
					main.c\
					$(SHARED)


SRCS_BONUS		= 	\
					main_bonus.c\
					$(SHARED)


OBJS			=	$(SRCS:.c=.o)
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

CC				=	gcc 

RM				=	rm -f

SANITIZE 		= 	-g3 -fsanitize=address -fsanitize=leak 
CFLAGS			=	-Wall -Wextra -Werror $(SANITIZE)

all				:	$(NAME)

bonus			: 	$(BONUS)

$(NAME)			:	$(OBJS) 
		make -C .. /libft
		$(CC) $(CFLAGS) $(OBJS) -I .. /libft/libft.h .. /libft/libft.a -o $(NAME)

$(BONUS)		:	$(OBJS_BONUS) 
		make -C .. /libft
		$(CC) $(CFLAGS) $(OBJS_BONUS) -I .. /libft/libft.h .. /libft/libft.a -o $(BONUS)

	   
clean			:
					$(RM) $(OBJS) $(OBJS_BONUS)
					make fclean -C ./libft	

fclean			:	clean
					$(RM) $(NAME) $(BONUS)

.PHONY			:	all clean fclean re bonus

re				:	fclean all
