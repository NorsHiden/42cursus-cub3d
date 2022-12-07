CC = gcc

CFLAGS =  -I./inc -I./libft -I./minilibx -framework Appkit -framework Opengl #-fsanitize=address

SRCS = 	srcs/main.c srcs/loading_data/import_file.c srcs/loading_data/import_config.c srcs/loading_data/error_handling.c \
		srcs/loading_data/import_utils.c srcs/loading_data/texture_validation.c srcs/loading_data/adjust_map.c \
		srcs/loading_data/map_validation.c srcs/rendering/player.c srcs/rendering/draw_map.c srcs/rendering/player_movement.c \
		srcs/rendering/vertical_rays.c srcs/rendering/horizontal_rays.c srcs/rendering/render_layer.c srcs/launch_game.c \
		srcs/rendering/draw_line_texture.c srcs/rendering/draw_texture.c srcs/rendering/mouse_movement.c \
		srcs/rendering/display.c srcs/rendering/player_directions.c

LIBFT = libft/libft.a

MINILIBX = minilibx/libmlx.a

NAME = cub3d

all : $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MINILIBX) -o $(NAME)

$(LIBFT):
	make -C libft > /dev/null

$(MINILIBX):
	make -C minilibx &> /dev/null

clean:
	make fclean -C libft

fclean: clean
	rm -f $(NAME)
	make clean -C minilibx

re : fclean all

.PHONY: all clean fclean re bonus