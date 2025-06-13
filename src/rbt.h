#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"
#ifndef RBT_H
#define RBT_H

namespace RBT{

/**
 * @brief Inicializa uma árvore binária BRT.
 * @return A árvore inicializada.
 */
BinaryTree* create();

/**
 * @brief Realiza uma busca na árvore e compila estatísticas no SearchResult. 
 * @param tree Ponteiro para a árvore.
 * @param word Palavra a ser inserida. Passar por referência.
 * @return SearchResult traz se a palavra foi achada, em quais documentos está,
 * e estatísticas sobre o desempenho (número de comparações e tempo de execução).
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief Função auxiliar para destroy.
 * @param node Ponteiro para o nó.
 */
void destroyNode(Node* node);

/**
 * @brief Libera toda a memória alocada pela árvore binária.
 * @param tree Ponteiro para a árvore.
 */
void destroy(BinaryTree* tree);

}

#endif
