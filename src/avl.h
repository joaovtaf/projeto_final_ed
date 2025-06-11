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
 * @brief Libera toda a memória alocada pela árvore binária.
 * @param *tree Ponteiro para a árvore
 */
void destroy(BinaryTree* tree);
}

#endif