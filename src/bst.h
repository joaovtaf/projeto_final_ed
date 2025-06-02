#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"
#ifndef BST_H
#define BST_H

namespace BST{

struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
};

struct BinaryTree {
    Node* root;
};

BinaryTree* create();

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

SearchResult search(BinaryTree* tree, const std::string& word);

void destroy(BinaryTree* tree);
}

#endif