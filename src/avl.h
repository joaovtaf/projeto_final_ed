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
 * @brief Inicializa uma árvore binária AVL.
 * @return A árvore inicializada.
 */
BinaryTree* create();

/**
 * @brief Calcula o fator de balanceamento de um node.
 * @param node Ponteiro para o node.
 * @return Altura do nó da esquerda menos a altura do nó da direita.
 */
int getBalance(Node* node);

/**
 * @brief Realiza a rotação para a direita de um node.
 * @param y Ponteiro para o node a ser rotacionado.
 * @return Ponteiro para o novo node na posição de y.
 */
Node* rightRotate(Node* y);


/**
 * @brief Realiza a rotação para a esquerda de um node.
 * @param x Ponteiro para o node a ser rotacionado.
 * @return Ponteiro para o novo node na posição de x.
 */
Node* leftRotate(Node* x);

/**
 * @brief Função recursiva auxiliar da insert.
 * @param node Ponteiro para o nó raiz da sub árvore a ser inserida
 * @param word Palavra a ser inserida. Passar por referência.
 * @param documentId Índice do documento de origem da palavra
 * @param numComparisons Ponteiro para retornar o número de comparações. Passar por referência.
 */
Node* insertAVL(Node* node, const std::string& word, int documentId, int& numComparisons);

/**
 * @brief Insere um nó mantendo a árvore balanceada na forma AVL 
 * ou adiciona um novo documentId a um nó ja existente.
 * @param tree Ponteiro para a árvore.
 * @param word Palavra a ser inserida. Passar por referência.
 * @param documentId número do documento de origem da palavra.
 * @return InsertResult contendo número de comparações e tempo de execução.
 */
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

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