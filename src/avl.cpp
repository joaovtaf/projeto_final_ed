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
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(y->left->height, y->right->height) + 1;
    x->height = max(x->left->height, x->right->height) + 1;

    return x; // faz a rotação para a direita
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = max(y->left->height, y->right->height) + 1;
    x->height = max(x->left->height, x->right->height) + 1;

    return y; // faz a rotação para a esquerda
}


}