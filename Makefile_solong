MAKEFLAGS	= --no-print-directory --silent

NAME	 = so_long

CC = cc

CFLAGS	 =	-Wextra -Wall -Werror -Wunreachable-code
CFLAGS	 += -I includes
CFLAGS	 += -I libft
CFLAGS	 += -I GNL
CFLAGS	 += -O3

DEBUG	 =	-g3 -fsanitize=address

CPPFLAGS =	-MMD

LIBMLX	= ./libs/MLX42
LIBFT	= ./libs/libft

HEADERS = -I ./includes -I $(LIBMLX)/include -I $(LIBFT)

LIBS	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS	+=	$(LIBFT)/libft.a


SRCS =						\
		srcs/main.c			\
							\
		srcs/animations/animation_next_texture.c \
		srcs/animations/animations_player.c \
		srcs/animations/animation_update.c \
							\
		srcs/animations/destroy_animation.c \
		srcs/animations/init_animation.c \
							\
		srcs/player/collisions.c \
		srcs/player/destroy_player.c \
		srcs/player/init_player.c \
		srcs/player/movements.c \
		srcs/player/speed_movements.c \
		srcs/player/update_player.c \
							\
		srcs/map/check_map.c \
		srcs/map/check_res.c \
		srcs/map/destroy_map.c \
		srcs/map/init_map.c \
		srcs/map/paint_map.c \
		srcs/map/parser_map.c \
		srcs/map/query_map_coordinate.c \
							\
		srcs/other/destroy_all.c \
		srcs/other/if_colectable.c \
		srcs/other/keys.c \
		srcs/other/print_error.c \
		srcs/other/update_game.c \



OBJS = $(patsubst srcs/%.c, objs/srcs/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: libmlx libft $(NAME)

libmlx:
	@cmake -DDEBUG=0 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(DEBUG) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && printf "Linking: $(NAME)\n"

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
