#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "avl.h"
#include "tree_utils.h"

namespace AVL {

BinaryTree* create() {
    BinaryTree* ptr = new BinaryTree{nullptr, nullptr};
    return ptr; // cria o ponteiro para BinaryTree
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* rightRotate(Node* y) {
    if (!y || !y->left) {
        return y;
    }
    
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x; // novo nó raiz da subárvore
}

Node* leftRotate(Node* x) {
    if (!x || !x->right) {
        return x;
    }

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return y; // novo nó raiz da subárvore
}

Node* insertAVL(Node* node, const std::string& word, int documentId, int& numComparisons) {
    if (node == nullptr) {
        return (new Node{word, {documentId}, nullptr, nullptr, nullptr, 1, 0});
    }

    numComparisons++;
    int comparison = word.compare(node->word);

    if (comparison < 0)
        node->left = insertAVL(node->left, word, documentId, numComparisons);
    else if (comparison > 0)
        node->right = insertAVL(node->right, word, documentId, numComparisons);
    else {
        bool found = false;
        for (int id : node->documentIds) {
            if (id == documentId) {
                found = true;
                break;
            }
        }
        if (!found) {
            node->documentIds.push_back(documentId);
        }
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && node->left != nullptr && word.compare(node->left->word) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && node->right != nullptr && word.compare(node->right->word) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && node->left != nullptr && word.compare(node->left->word) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && node->right != nullptr && word.compare(node->right->word) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int numComparisons = 0;
    
    if(tree == nullptr){
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        return InsertResult{numComparisons, elapsed.count()};
    }

    tree->root = insertAVL(tree->root, word, documentId, numComparisons);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

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

}