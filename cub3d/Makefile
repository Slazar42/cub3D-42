NAME = cub3D
SRC = parsing/main.c parsing/get_next_line.c parsing/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
ARG = -Wall -Wextra -Werror #-Imlx -lmlx -framework OpenGL -framework AppKit
CC = cc
RM = rm -rf

all: $(NAME)

%.o: %.c
	$(CC) $(ARG) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(ARG) $(OBJ) -o $(NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
