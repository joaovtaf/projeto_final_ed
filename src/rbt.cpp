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

Node* rightRotate(Node* y, Node* NIL) {
    if (y == NIL || y->left == NIL) {
        return y;
    }
    
    Node* x = y->left;
    Node* T2 = x->right;

    x->parent = y->parent;
    y->parent = x; 

    if (T2 != NIL) {
        T2->parent = y; // Atualiza o pai de T2 se existir
    }

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x; // novo nó raiz da subárvore
}

Node* leftRotate(Node* x, Node* NIL) {
    if (x == NIL || x->right == NIL) {
        return x;
    }

    Node* y = x->right;
    Node* T2 = y->left;

    y->parent = x->parent; 
    x->parent = y; 

    if (T2 != NIL) {
        T2->parent = x;     // Atualiza o pai de T2 se existir
    }

    y->left = x;
    x->right = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return y; // novo nó raiz da subárvore
}

void fixInsert(Node *z, Node *NIL) {
    while (z->parent->isRed == 1) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->isRed == 1) {
                // Caso 1: Tio vermelho
                z->parent->isRed = 0;
                y->isRed = 0;
                z->parent->parent->isRed = 1;
                z = z->parent->parent;
            } else {
                // Caso 2: Tio preto
                if (z == z->parent->right) {
                    // Left-right case
                    z = z->parent;
                    leftRotate(z, NIL);
                }
                // Left-left case
                z->parent->isRed = 0;
                z->parent->parent->isRed = 1;
                rightRotate(z->parent->parent, NIL);
            }
        } else {
            // Mirror cases
            Node *y = z->parent->parent->left;
            if (y->isRed == 1) {
                // Case 1
                z->parent->isRed = 0;
                y->isRed = 0;
                z->parent->parent->isRed = 1;
                z = z->parent->parent;
            } else {
                // Case 2
                if (z == z->parent->left) {
                    // Right-left case
                    z = z->parent;
                    rightRotate(z, NIL);
                }
                // Right-right case
                z->parent->isRed = 0;
                z->parent->parent->isRed = 1;
                leftRotate(z->parent->parent, NIL);
            }
        }
    }
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int numComparisons = 0;

    if(tree == nullptr){
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        return InsertResult{numComparisons, elapsed.count()};
    } // se o ponteiro tree for nulo retorna direto
    if(tree->root == nullptr) {
        tree->root = new Node{word, {documentId}, tree->NIL, nullptr, nullptr, 0, 0};
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start; // salva o tempo de execução

        return InsertResult{numComparisons, elapsed.count()};
    } // se a árvore ainda estiver vazia é criado o root
    
    Node* current_node = tree->root; // nó atual
    Node* current_node_parent = nullptr; // guarda o pai do nó atual
    int L_or_R = 0; // -1 de left e +1 se right 

    while (current_node != tree->NIL) {
        int comparison = word.compare(current_node->word);
        numComparisons++;

        if ( comparison == 0 ) {
            bool found = false;
            for (int id : current_node->documentIds) {
                if (id == documentId) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                current_node->documentIds.push_back(documentId); // salva o Id
            }

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

    current_node = new Node{word, {documentId}, current_node_parent, nullptr, nullptr, 0, 1};  // inserido como vermelho a principio
    if (L_or_R == -1) current_node_parent->left = current_node;
    if (L_or_R == +1) current_node_parent->right = current_node; // guarda o nó atual do lado correto do nó pai
    fixInsert(current_node, tree->NIL);
    tree->root->isRed = 0;

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