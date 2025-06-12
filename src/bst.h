#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"
#ifndef BST_H
#define BST_H

namespace BST{
/**
 * @brief Calcula o fator de balanceamento de um node.
 * @param node Ponteiro para o node.
 * @return Altura do nó da esquerda menos a altura do nó da direita.
 */
BinaryTree* create();

/**
 * @brief Função auxiliar da insert.
 * @param node Ponteiro para o node atual.
 * @param word Palavra a ser inserida. Passar por referência.
 * @param documentId Índice do documento que contém a palavra.
 * @param numComparisons Número de comparações, variável a ser atualizada. Passar por referência.
 * @return Ponteiro para o nó percorrido.
 */
Node* insertBST(Node* node, const std::string& word, int documentId, int& numComparisons);

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
 * @brief Realiza a busca de uma palavra na BST.
 * @param tree Ponteiro para a BST.
 * @param word Palavra a ser inserida. Passar por referência.
 * @return SearchResult que diz se a palvra foi achada, em quais documentos e estatísticas
 * sobre o processo.
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief Função auxiliar da destroy.
 * @param node Ponteiro para o node a ser destruído.
 */
void destroyNode(Node* node);

/**
 * @brief Libera toda a memória alocada pela BST.
 * @param tree Ponteiro para a BST a ser destruída.
 */
void destroy(BinaryTree* tree);
}

#endif