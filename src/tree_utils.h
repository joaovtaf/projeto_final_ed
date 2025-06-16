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
    Node* NIL;  // usado na RBT (Opcional) // zero para preto, 1 para vermelho
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
 * @param tree Ponteiro para a árvore.
 */
void printIndex(BinaryTree* tree);


/**
 * @brief Função interna para formatar a impressão das palavras armazenadas em tree em formato de árvore.
 * @param node Ponteiro para o nó raiz.
 * @param prefix Prefixo atual. Passar por referência.
 * @param isLeft True se o nó raiz está na esquerda de seu nó pai. False caso contrário.
 */
void printTreeAux(Node* node, const std::string& prefix, bool isLeft);

/**
 * @brief Imprime as palavras armazenadas em tree em formato de árvore.
 * @param tree Ponteiro para a árvore.
 */
void printTree(BinaryTree* tree);

/**
 * @brief Calcula o valor máximo entre dois inteiros.
 * @param a Primeiro inteiro a ser comparado.
 * @param b Segundo inteiro a ser comparado.
 * @return Maior valor entre a e b.
 */
int max(int a, int b);

/**
 * @brief Calcula a altura de um nó.
 * @param node Ponteiro para o nó a ser descoberto a altura.
 * @return Altura do nó.
 */
int height(Node* node);

#endif