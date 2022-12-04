CC = gcc

CFLAGS =  -I./inc -I./libft -framework Appkit -framework Opengl -lmlx -fsanitize=address -g

SRCS = 	srcs/main.c srcs/loading_data/import_file.c srcs/loading_data/import_config.c srcs/loading_data/error_handling.c \
		srcs/loading_data/import_utils.c srcs/loading_data/texture_validation.c srcs/loading_data/adjust_map.c \
		srcs/loading_data/map_validation.c srcs/minimap/player.c srcs/minimap/draw_map.c srcs/minimap/player_movement.c \
		srcs/minimap/vertical_rays.c srcs/minimap/horizontal_rays.c srcs/minimap/render_layer.c srcs/launch_game.c

LIBFT = libft/libft.a

NAME = cub3d

all : $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft > /dev/null

clean:
	make fclean -C libft

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus