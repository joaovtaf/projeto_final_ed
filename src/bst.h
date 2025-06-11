#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "tree_utils.h"
#ifndef BST_H
#define BST_H

namespace BST{

// Cria uma nova árvore binária vazia.
// Retorna uma BinaryTree.
BinaryTree* create();

// Insere uma palavra na árvore associada a um documentId. Se for nova cria um novo nó, e já existir adiciona o documentId.
// Retorna um InsertResult que trás estatísticas sobre o desempenho (número de comparações e tempo de execução).
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

// Realiza uma busca em uma árvore.
// Retorna um SearchResult que trás se a palavra foi achada, em quais documentos está, e estatísticas sobre o desempenho (número de comparações e tempo de execução).
SearchResult search(BinaryTree* tree, const std::string& word);

// Função auxiliar da destroy.
void destroyNode(Node* node);

// Libera toda a memória alocada pela árvore binária.
void destroy(BinaryTree* tree);
}

#endif