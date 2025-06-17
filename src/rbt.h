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
 * @brief Realiza a rotação para a direita de um node.
 * @param y Ponteiro para o node a ser rotacionado.
 * @param NIL Ponteiro para o NIL.
 * @return Ponteiro para o novo node na posição de y.
 */
Node* rightRotate(Node* y, Node *NIL);


/**
 * @brief Realiza a rotação para a esquerda de um node.
 * @param x Ponteiro para o node a ser rotacionado.
 * @param NIL Ponteiro para o NIL.
 * @return Ponteiro para o novo node na posição de x.
 */
Node* leftRotate(Node* x, Node *NIL);

/**
 * @brief Corrige as cores a faz as rotações se necessário
 * @param z ponteiro para o nó a ser corrigido
 * @param NIL ponteiro para o NIL
 * e estatísticas sobre o desempenho (número de comparações e tempo de execução).
 */
void fixInsert(Node *z, Node *NIL);

/**
 * @brief Insere uma palavra na árvore associada a um documentId. Se for inédita cria um novo nó,
 * se já existir adiciona o documentId ao nó associado.
 * @param tree Ponteiro para a BST.
 * @param word Palavra a ser inserida. Passar por referência.
 * @param documentId Índice do documento que contém a palavra.
 * @return InsertResult com estatísticas sobre o desempenho.
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
