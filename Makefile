NAME = philo
SRC = $(wildcard ./*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

FLAGS = -Wall -Wextra -Werror
CC = cc

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
