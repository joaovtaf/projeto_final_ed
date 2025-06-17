# Makefile for building bst, avl, rbt and test programs
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
RBT_TARGET := rbt
TEST_BST_TARGET := test_bst
TEST_AVL_TARGET := test_avl
TEST_RBT_TARGET := test_rbt

# Platform-specific executable extension
ifeq ($(OS),Windows_NT)
    BST_EXECUTABLE := $(BST_TARGET).exe
    AVL_EXECUTABLE := $(AVL_TARGET).exe
	RBT_EXECUTABLE := $(RBT_TARGET).exe
    TEST_BST_EXECUTABLE := $(TEST_BST_TARGET).exe
    TEST_AVL_EXECUTABLE := $(TEST_AVL_TARGET).exe
	TEST_RBT_EXECUTABLE := $(TEST_RBT_TARGET).exe
else
    BST_EXECUTABLE := $(BST_TARGET)
    AVL_EXECUTABLE := $(AVL_TARGET)
	RBT_EXECUTABLE := $(RBT_TARGET)
    TEST_BST_EXECUTABLE := $(TEST_BST_TARGET)
    TEST_AVL_EXECUTABLE := $(TEST_AVL_TARGET)
	TEST_RBT_EXECUTABLE := $(TEST_RBT_TARGET)
endif

# Object files
BST_OBJS := data.o tree_utils.o bst.o main_bst.o
AVL_OBJS := data.o tree_utils.o avl.o main_avl.o
RBT_OBJS := data.o tree_utils.o rbt.o # add main_rbt.o 
TEST_BST_OBJS := tree_utils.o bst.o test_bst.o
TEST_AVL_OBJS := tree_utils.o avl.o test_avl.o
TEST_RBT_OBJS := tree_utils.o rbt.o test_rbt.o

# Default rule
all: $(BST_EXECUTABLE) $(AVL_EXECUTABLE) $(RBT_EXECUTABLE) $(TEST_BST_EXECUTABLE) $(TEST_AVL_EXECUTABLE) $(TEST_RBT_EXECUTABLE)

# Build executables
$(BST_EXECUTABLE): $(BST_OBJS)
	$(CXX) $(BST_OBJS) -o $(BST_EXECUTABLE)

$(AVL_EXECUTABLE): $(AVL_OBJS)
	$(CXX) $(AVL_OBJS) -o $(AVL_EXECUTABLE)

$(RBT_EXECUTABLE): $(RBT_OBJS)
	$(CXX) $(RBT_OBJS) -o $(RBT_EXECUTABLE)

$(TEST_BST_EXECUTABLE): $(TEST_BST_OBJS)
	$(CXX) $(TEST_BST_OBJS) -o $(TEST_BST_EXECUTABLE)

$(TEST_AVL_EXECUTABLE): $(TEST_AVL_OBJS)
	$(CXX) $(TEST_AVL_OBJS) -o $(TEST_AVL_EXECUTABLE)

$(TEST_RBT_EXECUTABLE): $(TEST_RBT_OBJS)
	$(CXX) $(TEST_RBT_OBJS) -o $(TEST_RBT_EXECUTABLE)

# Object rules
data.o: $(SRCDIR)/data.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/data.cpp -o data.o

tree_utils.o: $(SRCDIR)/tree_utils.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/tree_utils.cpp -o tree_utils.o

bst.o: $(SRCDIR)/bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/bst.cpp -o bst.o

avl.o: $(SRCDIR)/avl.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/avl.cpp -o avl.o

rbt.o: $(SRCDIR)/rbt.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/rbt.cpp -o rbt.o

main_bst.o: $(SRCDIR)/main_bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main_bst.cpp -o main_bst.o

main_avl.o: $(SRCDIR)/main_avl.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main_avl.cpp -o main_avl.o

# add main_rbt

test_bst.o: $(SRCDIR)/test_bst.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/test_bst.cpp -o test_bst.o

test_avl.o: $(SRCDIR)/test_avl.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/test_avl.cpp -o test_avl.o

test_rbt.o: $(SRCDIR)/test_rbt.cpp
	$(CXX) $(CXXFLAGS) $(SRCDIR)/test_rbt.cpp -o test_rbt.o

# Clean rule
clean:
	rm -f $(OBJDIR)/*.o $(BST_EXECUTABLE) $(AVL_EXECUTABLE) $(RBT_EXECUTABLE)  $(TEST_BST_EXECUTABLE) $(TEST_AVL_EXECUTABLE) $(TEST_RBT_EXECUTABLE)

.PHONY: all clean
