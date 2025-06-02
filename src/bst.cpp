#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "bst.h"
#include "tree_utils.h"


BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree();
    ptr->root = nullptr;
    ptr->NIL = nullptr; // não é utilizado
    return ptr;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
    int numComparisons = 0;

    if(tree->root == nullptr) {
        tree->root = new Node{word, {documentId}, nullptr, nullptr, nullptr, 0, 0};
        return InsertResult{numComparisons,0}; // IMPORTANTE: colocar o valor de executionTime
    } // se a árvore ainda estiver vazia é criado o root

    Node* current_node = tree->root;
    Node* current_node_parent = nullptr;
    int L_or_R = 0; // -1 de left e +1 se right 

    while (current_node != nullptr) {
        int comparison = word.compare(current_node->word);
        numComparisons++;

        if ( comparison == 0 ) {
            current_node->documentIds.push_back(documentId);
            return InsertResult{numComparisons, 0}; // IMPORTANTE: colocar o valor de executionTime
        }
        if ( comparison < 0 ) {
            current_node_parent = current_node;
            current_node = current_node->left;
            L_or_R = -1;
        }
        if ( comparison > 0 ) {
            current_node_parent = current_node;
            current_node = current_node->right;
            L_or_R = +1;
        }
    }
    
    current_node = new Node{word, {documentId}, current_node_parent, nullptr, nullptr, 0, 0};
    if (L_or_R == -1) current_node_parent->left = current_node;
    if (L_or_R == +1) current_node_parent->right = current_node; 
    return InsertResult{numComparisons,0}; // IMPORTANTE: colocar o valor de executionTime
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