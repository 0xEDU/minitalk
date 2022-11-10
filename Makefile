NAME = minitalk
BINARY = client server

CCFLAGS = -Wall -Werror -Wextra

INCLUDES_PATH = includes
LIBFT = ./libft/libft.a

SRCS = ./sources/client.c ./sorces/server.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -I $(INCLUDES_PATH) -c $< -o $@

$(NAME): $(BINARY)

$(LIBFT):
	@make -C libft

client: sources/client.o $(LIBFT)
	@$(CC) $(CCFLAGS) ./sources/client.o -I $(INCLUDES_PATH) $(LIBFT) -o $@

server: sources/server.o $(LIBFT)
	@$(CC) $(CCFLAGS) ./sources/server.o -I $(INCLUDES_PATH) $(LIBFT) -o $@

clean:
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@rm -f $(BINARY)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
