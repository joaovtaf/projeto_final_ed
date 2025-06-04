# Makefile for building bst project
# Works on Linux and Windows with g++

# Compiler and flags
CXX := g++
CXXFLAGS := -c -Wall

# Source files
SRCDIR := src
OBJDIR := .
OBJS := data.o tree_utils.o bst.o main_bst.o

# Executable
TARGET := bst

# Platform-specific executable extension
ifeq ($(OS),Windows_NT)
    EXECUTABLE := $(TARGET).exe
else
    EXECUTABLE := $(TARGET)
endif

# Rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXECUTABLE)

data.o: $(SRCDIR)/data.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/data.cpp -o data.o

tree_utils.o: $(SRCDIR)/tree_utils.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/tree_utils.cpp -o tree_utils.o

bst.o: $(SRCDIR)/bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/bst.cpp -o bst.o

main_bst.o: $(SRCDIR)/main_bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main_bst.cpp -o main_bst.o

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)

.PHONY: all clean
