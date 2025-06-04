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

    for(int i = 0; i < tree->root->documentIds.size(); i++){
        std::cout << tree->root->documentIds[i];
        if(i < tree->root->documentIds.size()) std::cout << ", ";
        else std::cout << "\n";
    }

    if(tree->root->right != nullptr){
        auxTree->root = tree->root->right;
        printIndex(auxTree);
    }
    auxTree->root = nullptr;
    delete auxTree;
}

void printTreeAux(BinaryTree* tree, const std::string& prefix, bool isLeft) {
    std::cout << prefix;
    std::string newPrefix;
    if(isLeft){
        std::cout << "├── ";
        newPrefix = prefix + "│   ";
    }
    else{
        std::cout << "└── ";
        newPrefix = prefix + "    ";
    }

    std::cout << tree->root->word << "\n";

    if(tree->root->left != nullptr){
        BinaryTree* auxTreeLeft = new BinaryTree;
        auxTreeLeft->root = tree->root->left;
        printTreeAux(auxTreeLeft, newPrefix, true);
        auxTreeLeft->root = nullptr;
        delete auxTreeLeft;
    }
    if(tree->root->right != nullptr){
        BinaryTree* auxTreeRight = new BinaryTree;
        auxTreeRight->root = tree->root->right;
        printTreeAux(auxTreeRight, newPrefix, false);
        auxTreeRight->root = nullptr;
        delete auxTreeRight;
    }
}

void printTree(BinaryTree* tree){
    if(tree->root == nullptr){
        std::cout << "Árvore vazia\n";
        return;
    }
    printTreeAux(tree, "", false);
}
