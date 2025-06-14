#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "rbt.h"
#include "tree_utils.h"

namespace RBT {

BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree{nullptr, nullptr};
    return ptr; // cria e retorna
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

    while (current_node != nullptr) {
        int comparison = word.compare(current_node->word);
        numComparisons++;

        if ( comparison == 0 ) {

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

            return SearchResult{1, current_node->documentIds, elapsed.count(), numComparisons}; // se a palavra for igual, retorna com a lista atualizada
        }
        if ( comparison < 0 ) {
            current_node = current_node->left; // se a palavra for menor, sigo pela esquerda
        }
        if ( comparison > 0 ) {
            current_node = current_node->right; // se a palavra for maior, sigo pela direita
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

    return SearchResult{0, {}, elapsed.count(), numComparisons};
}

void destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
    return; // recursivamente deleta todos os nós
}

void destroy(BinaryTree* tree) {

    if (tree == nullptr) return; // se a arvore for null retorna direto

    destroyNode(tree->root); // recursivamente deleta os nós
    
    delete tree; 
    return; // deleta a tree e root, e retorna
}
} // namespace RBT