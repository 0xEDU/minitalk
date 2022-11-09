NAME = minitalk
SERVER = server
CLIENT = client

CCFLAGS = -Wall -Wextra -Werror -g3
LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

SERVER_SOURCES_PATH = ./sources/server
CLIENT_SOURCES_PATH = ./sources/client
INCLUDES_PATH = ./includes
OBJS_PATH = .

SERVER_SOURCES = $(addprefix $(SERVER_SOURCES_PATH)/, server.c)
CLIENT_SOURCES = $(addprefix $(CLIENT_SOURCES_PATH)/, client.c)

SERVER_OBJS = $(SERVER_SOURCES:$(SERVER_SOURCES_PATH)/%.c=$(OBJS_PATH)/%.o)
CLIENT_OBJS = $(CLIENT_SOURCES:$(CLIENT_SOURCES_PATH)/%.c=$(OBJS_PATH)/%.o)

all: $(NAME)

$(NAME): $(SERVER_OBJS) $(CLIENT_OBJS)
	@make --no-print-directory -C $(LIBDIR)
	@make --no-print-directory -C $(LIBDIR) clean
	@$(CC) $(CCFLAGS) $(SERVER_OBJS) $(LIB) -o $(SERVER)
	@echo -e "\033[32m[Server created]\033[0m"
	@$(CC) $(CCFLAGS) $(CLIENT_OBJS) $(LIB) -o $(CLIENT)
	@echo -e "\033[32m[Server created]\033[0m"
	@echo -e "\033[32m[Minitalk created]\033[0m"

$(SERVER_OBJS): $(SERVER_SOURCES)
	@$(CC) $(CCFLAGS) -c $(SERVER_SOURCES) -I $(INCLUDES_PATH)
	@echo -e "\033[32m[Server objects created]\033[0m"

$(CLIENT_OBJS): $(CLIENT_SOURCES)
	@$(CC) $(CCFLAGS) -c $(CLIENT_SOURCES) -I $(INCLUDES_PATH)
	@echo -e "\033[32m[Client objects created]\033[0m"

clean:
	/bin/rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	/bin/rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
