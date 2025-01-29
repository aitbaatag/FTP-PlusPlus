# Program name
NAME = simple-ftp

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++98 -g3

CLIENT_SRCS = $(addprefix $(SRC_DIR)/Client/, client.cpp)
SERVER_SRCS = $(addprefix $(SRC_DIR)/Server/, Server.cpp)
SOCKET_SRCS = $(addprefix $(SRC_DIR)/Socket/, socket.cpp)
MAIN_SRCS = $(addprefix $(SRC_DIR)/, main_client.cpp main_server.cpp)

# Object files
CLIENT_OBJS = $(CLIENT_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SERVER_OBJS = $(SERVER_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SOCKET_OBJS = $(SOCKET_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJS = $(MAIN_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# All objects
OBJS = $(CLIENT_OBJS) $(SERVER_OBJS) $(SOCKET_OBJS) $(MAIN_OBJS)

# Targets
all: $(NAME)

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(SOCKET_OBJS) $(OBJ_DIR)/main_client.o -o client
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(SOCKET_OBJS) $(OBJ_DIR)/main_server.o -o server

# Cleaning
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f client server

re: fclean all
