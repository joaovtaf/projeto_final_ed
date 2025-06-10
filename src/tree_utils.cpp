#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"

void printIndex(BinaryTree* tree){
    if(tree->root == nullptr){
        std::cout << "Árvore vazia\n";
        return;
    }
    BinaryTree* auxTree = new BinaryTree;
    if(tree->root->left != nullptr){
        auxTree->root = tree->root->left;
        printIndex(auxTree);
    }
    std::cout << tree->root->word << ": ";

    for(int i = 0; i < int(tree->root->documentIds.size()); i++){
        std::cout << tree->root->documentIds[i];
        if(i < int(tree->root->documentIds.size() - 1)) std::cout << ", ";
        else std::cout << "\n";
    }

    if(tree->root->right != nullptr){
        auxTree->root = tree->root->right;
        printIndex(auxTree);
    }
    auxTree->root = nullptr;
    delete auxTree;
    auxTree = nullptr;
}

void printTreeAux(Node* node, const std::string& prefix, bool isLast) {
    if (node == nullptr) return;

    std::cout << prefix;
    if(prefix != "") std::cout << (isLast ? "└── " : "├── ");
    else std::cout << "    ";
    std::cout << node->word << std::endl;

    bool hasLeft = node->left != nullptr;
    bool hasRight = node->right != nullptr;

    std::string newPrefix = prefix + (isLast ? "    " : "│   ");

    if (hasLeft && hasRight) {
        printTreeAux(node->left, newPrefix, false); 
        printTreeAux(node->right, newPrefix, true); 
    } else if (hasLeft) {
        printTreeAux(node->left, newPrefix, true);
    } else if (hasRight) {
        printTreeAux(node->right, newPrefix, true);
    }
}

void printTree(BinaryTree* tree){
    if(tree->root == nullptr){
        std::cout << "Árvore vazia\n";
        return;
    }
    printTreeAux(tree->root, "", true);
}
