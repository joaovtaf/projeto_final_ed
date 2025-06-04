#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

struct BinaryTree {
    Node* root;
    Node* NIL;  // usado na RBT (Opcional)
};

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

/**
 * @brief Imprime as palavras armazenadas em tree, em ordem lexicográfica, seguidas dos
 * índices dos arquivos aos quais elas pertencem.
 * @param *tree Ponteiro para a árvore
 */
void printIndex(BinaryTree* tree);


/**
 * @brief Função interna para formatar a impressão das palavras armazenadas em tree em formato de árvore.
 * @param *tree Ponteiro para a árvore
 * @param &prefix Endereço do prefixo atual
 * @param isLeft True se o nó raiz está na esquerda de seu nó pai. False caso contrário.
 */
void printTreeAux(BinaryTree* tree, const std::string& prefix, bool isLeft);

/**
 * @brief Imprime as palavras armazenadas em tree em formato de árvore.
 * @param *tree Ponteiro para a árvore
 */
void printTree(BinaryTree* tree);

#endif