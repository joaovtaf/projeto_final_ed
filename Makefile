# Makefile for building bst project
# Works on Linux and Windows with g++

# Compiler and flags
CXX := g++
CXXFLAGS := -c -Wall

# Source directories
SRCDIR := src
OBJDIR := .

# Target names
BST_TARGET := bst
AVL_TARGET := avl

# Source files for BST
BST_OBJS := data.o tree_utils.o bst.o main_bst.o

# Source files for AVL
AVL_OBJS := data.o tree_utils.o avl.o main_avl.o

# Platform-specific executable extension
ifeq ($(OS),Windows_NT)
    BST_EXECUTABLE := $(BST_TARGET).exe
    AVL_EXECUTABLE := $(AVL_TARGET).exe
else
    BST_EXECUTABLE := $(BST_TARGET)
    AVL_EXECUTABLE := $(AVL_TARGET)
endif

# Default rule
all: $(BST_EXECUTABLE) $(AVL_EXECUTABLE)

# Build BST executable
$(BST_EXECUTABLE): $(BST_OBJS)
	$(CXX) $(BST_OBJS) -o $(BST_EXECUTABLE)

# Build AVL executable
$(AVL_EXECUTABLE): $(AVL_OBJS)
	$(CXX) $(AVL_OBJS) -o $(AVL_EXECUTABLE)

# Object rules for BST
data.o: $(SRCDIR)/data.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/data.cpp -o data.o

tree_utils.o: $(SRCDIR)/tree_utils.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/tree_utils.cpp -o tree_utils.o

bst.o: $(SRCDIR)/bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/bst.cpp -o bst.o

main_bst.o: $(SRCDIR)/main_bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main_bst.cpp -o main_bst.o

# Object rules for AVL
avl.o: $(SRCDIR)/avl.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/avl.cpp -o avl.o

main_avl.o: $(SRCDIR)/main_avl.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main_avl.cpp -o main_avl.o


clean:
	rm -f $(OBJDIR)/*.o $(BST_EXECUTABLE) $(AVL_EXECUTABLE)

.PHONY: all clean
