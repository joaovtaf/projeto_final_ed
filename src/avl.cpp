#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "avl.h"
#include "tree_utils.h"

namespace BST {

BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree{nullptr, nullptr};
    return ptr; // cria o ponteiro para BinaryTree
}

int max(int a, int b) {
    return (a > b) ? a : b; // retorna o máximo entre dois int
}

Node* rightRotate(Node* y) {
    // inicio
    //     y
    //   x   T3
    // T1 T2
    // fim
    //     x
    //   T1   y
    //      T2 T3
    
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(y->left->height, y->right->height) + 1;
    x->height = max(x->left->height, x->right->height) + 1;

    return x; // faz a rotação para a direita
}

Node* leftRotate(Node* x) {
    // inicio
    //     x
    //  T1     y
    //      T2  T3
    // fim
    //      y
    //   x     T3
    // T1 T2 

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = max(y->left->height, y->right->height) + 1;
    x->height = max(x->left->height, x->right->height) + 1;

    return y; // faz a rotação para a esquerda
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

}