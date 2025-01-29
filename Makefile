# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++98 -Iinclude

# Directories
SRCDIR = src
SERVER_OBJDIR = server
CLIENT_OBJDIR = client

# Source files
SERVER_SRCS = $(SRCDIR)/main_server.cpp $(SRCDIR)/Server/Server.cpp $(SRCDIR)/Socket/Socket.cpp
CLIENT_SRCS = $(SRCDIR)/main_client.cpp $(SRCDIR)/Client/Client.cpp $(SRCDIR)/Socket/Socket.cpp

# Object files
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)

# Output binaries
SERVER_TARGET = ftp_server
CLIENT_TARGET = ftp_client

# Default target: build both programs
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Rule to build server objects
$(SERVER_OBJS)/%.o: $(SERVER_SRCS)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build client objects
$(CLIENT_OBJS)/%.o: $(CLIENT_SRCS)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Server binary
$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Client binary
$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(SERVER_TARGET) $(CLIENT_TARGET)

# Rebuild everything
re: clean all
