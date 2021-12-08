# Compiler settings
CC = g++
CFLAGS = -Wall -Wpedantic -g3 -std=c++17

# Directories
ODIR = obj
SDIR = src
INC = -Iinc 

# Source files and objects
SOURCES = main.cpp BingoBoard.cpp functions.cpp
OBJS = $(patsubst %, $(ODIR)/%, $(SOURCES:.cpp=.o))
OUT = Solution

# Rules
.PHONY: all
all : $(OUT)
$(OUT) : $(OBJS)
	$(CC) -o $@ $^ 

# General rule for objects
$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CC) -c $(INC) $(CFLAGS) -o $@ $<

# Clean
clean :
	rm obj/*.o
