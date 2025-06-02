#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "bst.h"

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

struct InsertResult {
    int numComparisons;
    double executionTime;
    // <Possíveis outras variáveis>
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
    // <Possíveis outras variáveis>
};

void printIndex(BinaryTree* tree);

void printTree(BinaryTree* tree);

#endif