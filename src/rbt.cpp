#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "rbt.h"
#include "tree_utils.h"

namespace RBT {

BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree();
    ptr->NIL = new Node{"", {}, nullptr, nullptr, nullptr, 0};
    ptr->NIL->left = ptr->NIL;
    ptr->NIL->right = ptr->NIL;
    ptr->NIL->parent = ptr->NIL;
    ptr->root = ptr->NIL;
    return ptr; // Cria o ponteiro da árvore e do nó NIL
}

SearchResult search(BinaryTree* tree, const std::string& word){
    auto start = std::chrono::high_resolution_clock::now(); // incia a contagem
    int numComparisons = 0;
    
    if(tree == nullptr){
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

        return SearchResult{0, {}, elapsed.count(), numComparisons};
    } // se a arvore for null retorna direto

    if(tree->root == nullptr) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

        return SearchResult{0, {}, elapsed.count(), numComparisons};
    } // se a árvore ainda estiver vazia retorna direto

    Node* current_node = tree->root; // nó atual

    while (current_node != tree->NIL) {

        int comparison = word.compare(current_node->word);
        numComparisons++;

        if ( comparison == 0 ) {

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

            return SearchResult{1, current_node->documentIds, elapsed.count(), numComparisons}; // se a palavra for igual, retorna com a lista atualizada
        }
        if ( comparison < 0 ) {
            current_node = current_node->left; // se a palavra for menor, sigo pela esquerda
        } else if ( comparison > 0 ) {
            current_node = current_node->right; // se a palavra for maior, sigo pela direita
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

    return SearchResult{0, {}, elapsed.count(), numComparisons};
}

void destroyNode(Node* node, Node* nil_node) {
    if (node != nil_node) {
        destroyNode(node->left, nil_node);
        destroyNode(node->right, nil_node);
        delete node;
    } // Deleta os nós evitando o NIL node
    return;
}

void destroy(BinaryTree* tree) {
    if (tree == nullptr) return;
    destroyNode(tree->root, tree->NIL);
    delete tree->NIL;
    delete tree;
    return; // deleta a árvore completa
}
} // namespace RBT