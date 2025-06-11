#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"
#ifndef AVL_H
#define AVL_H

namespace AVL {

/**
 * @brief Cria uma árvore avl
 */
BinaryTree* create();

/**
 * @brief retorna o valor máximo entre dois int.
 * @param a, b inteiros
 * @return int, maior entre a e b
 */
int max(int a, int b);

/**
 * @brief realiza a rotação para a direita do nó y
 * @param y, nó a ser rotacionado
 * @return retorna o novo nó na posição de y
 */
Node* rightRotate(Node* y);

/**
 * @brief realiza a rotação para a esquerda do nó x
 * @param x, nó a ser rotacionado
 * @return retorna o novo nó na posição de x
 */
Node* leftRotate(Node* x);

/**
 * @brief Função recursiva auxiliar da insert
 * @param *node nó da sub árvore a ser inserida
 * @param & word palavra a ser inserida
 * @param documentId número do documento de origem da palavra
 * @param & numComparisons ponteiro para retornar o número de comparações
 */
Node* insertAVL(Node* node, const std::string& word, int documentId, int& numComparisons);

/**
 * @brief Insere um nó mantendo a árvore balanceada, na forma AVL 
 * ou adiciona um novo documentId a um nó ja existente
 * @param *tree Ponteiro para a árvore
 * @param & word palavra a ser inserida
 * @param documentId número do documento de origem da palavra
 */
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

/**
 * @brief Realiza uma busca na árvore. Retornando um SearchResult 
 * @param *tree Ponteiro para a árvore
 * @param & word palavra a ser inserida
 * @return SearchResult trás se a palavra foi achada, em quais documentos está,
 * e estatísticas sobre o desempenho (número de comparações e tempo de execução).
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief função auxiliar para destroy
 * @param *node ponteiro para o nó
 */
void destroyNode(Node* node);

/**
 * @brief Libera toda a memória alocada pela árvore binária.
 * @param *tree Ponteiro para a árvore
 */
void destroy(BinaryTree* tree);
}

#endif