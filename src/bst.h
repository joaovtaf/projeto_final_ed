#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"
#ifndef BST_H
#define BST_H

namespace BST{

BinaryTree* create();

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

SearchResult search(BinaryTree* tree, const std::string& word);

void destroy(BinaryTree* tree);
}

#endif