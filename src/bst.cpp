#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "bst.h"
#include "tree_utils.h"


BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree();
    return ptr;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
    
}

SearchResult search(BinaryTree* tree, const std::string& word){

}

void destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
    return; // recursivamente deleta todos os nós
}

void destroy(BinaryTree* tree) {

    if (tree == nullptr) return; // se a arvore for null retorna direto

    destroyNode(tree->root); // recursivamente deleta os nós
    
    delete tree; 
    return; // deleta a tree e root, e retorna
}