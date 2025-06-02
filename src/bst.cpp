#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "bst.h"
#include "tree_utils.h"


BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree{nullptr, nullptr};
    return ptr; // cria e retorna
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
    auto start = std::chrono::high_resolution_clock::now(); // incia a contagem
    int numComparisons = 0;
    
    if(tree == nullptr){
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

        return InsertResult{numComparisons, elapsed.count()};
    } // se a arvore for null retorna direto
    if(tree->root == nullptr) {
        tree->root = new Node{word, {documentId}, nullptr, nullptr, nullptr, 0, 0};

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

        return InsertResult{numComparisons, elapsed.count()};
    } // se a árvore ainda estiver vazia é criado o root

    Node* current_node = tree->root; // nó atual
    Node* current_node_parent = nullptr; // guarda o pai do nó atual
    int L_or_R = 0; // -1 de left e +1 se right 

    while (current_node != nullptr) {
        int comparison = word.compare(current_node->word);
        numComparisons++;

        if ( comparison == 0 ) {
            current_node->documentIds.push_back(documentId); // salva o Id

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

            return InsertResult{numComparisons, elapsed.count()}; // se a palavra for igual, retorna com a lista atualizada
        }
        if ( comparison < 0 ) {
            current_node_parent = current_node;
            current_node = current_node->left;
            L_or_R = -1; // se a palavra for menor, segue pela esquerda
        }
        if ( comparison > 0 ) {
            current_node_parent = current_node;
            current_node = current_node->right;
            L_or_R = +1; // se a palavra for maior, segue pela direita
        }
    }
    
    current_node = new Node{word, {documentId}, current_node_parent, nullptr, nullptr, 0, 0};

    if (L_or_R == -1) current_node_parent->left = current_node;
    if (L_or_R == +1) current_node_parent->right = current_node; // guarda o nó atual do lado corrto do nó pai

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

    return InsertResult{numComparisons, elapsed.count()};
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