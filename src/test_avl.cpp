#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include "avl.h"
#include "tree_utils.h"

// Funções Auxiliares de Teste 

// Funcao para verificar se um ID existe em um vetor de IDs
bool containsId(const std::vector<int>& ids, int id) {
    for (size_t i = 0; i < ids.size(); i++) {
        if (ids[i] == id) {
            return true;
        }
    }
    return false;
}

Node* findNode(Node* node, const std::string& word) {
    if (node == nullptr) {
        return nullptr;
    }
    int comparison = word.compare(node->word);
    if (comparison == 0) {
        return node;
    } else if (comparison < 0) {
        return findNode(node->left, word);
    } else {
        return findNode(node->right, word);
    }
}

// Testes 
void test_create() {
    std::cout << "Testando a create" << std::endl;

    // Criar arvore vazia
    BinaryTree* tree1 = AVL::create();
    assert(tree1 != nullptr && tree1->root == nullptr);
    std::cout << "Teste Criar Arvore Vazia: PASSOU" << std::endl;
    AVL::destroy(tree1);

    // Criar árvore e inserir um no (verificação indireta)
    BinaryTree* tree2 = AVL::create();
    AVL::insert(tree2, "raiz", 1);
    assert(tree2 != nullptr && tree2->root != nullptr && tree2->root->word == "raiz");
    std::cout << "Teste Criar Arvore com um No: PASSOU" << std::endl;
    AVL::destroy(tree2);

    std::cout << std::endl;
}

void test_insert() {
    std::cout << "Testando o insert" << std::endl;
    BinaryTree* tree = AVL::create();

    // Inserção que causa rotação Left-Right (LR)
    AVL::insert(tree, "banana", 10);
    AVL::insert(tree, "abacate", 20);
    InsertResult res = AVL::insert(tree, "acerola", 30); // Deve causar rotação LR

    printTree(tree);

    // Após rotação LR:
    //       acerola
    //      /       \
    // abacate     banana

    assert(tree->root != nullptr && tree->root->word == "acerola");
    assert(tree->root->left != nullptr && tree->root->left->word == "abacate");
    assert(tree->root->right != nullptr && tree->root->right->word == "banana");
    std::cout << "Teste Rotação Left-Right (LR): PASSOU" << std::endl;

    // Teste de inserção normal à direita
    AVL::insert(tree, "caqui", 40);
    assert(tree->root->right->right != nullptr && tree->root->right->right->word == "caqui");
    std::cout << "Teste Inserção Direita Após LR: PASSOU" << std::endl;

    // Inserção que causa rotação Right-Left (RL)
    AVL::insert(tree, "figo", 50);
    AVL::insert(tree, "damasco", 60); // Deve causar rotação RL

    printTree(tree);

    // Verificações pós RL
    assert(tree->root->right->word == "damasco");
    assert(tree->root->right->left != nullptr && tree->root->right->left->word == "caqui");
    assert(tree->root->right->right != nullptr && tree->root->right->right->word == "figo");
    std::cout << "Teste Rotação Right-Left (RL): PASSOU" << std::endl;

    // Inserção adicional
    AVL::insert(tree, "goiaba", 70);
    assert(tree->root->right->right->right != nullptr && tree->root->right->right->right->word == "goiaba");

    // Teste de duplicatas
    AVL::insert(tree, "damasco", 60); // repetido
    AVL::insert(tree, "damasco", 80); // novo

    Node* damasco = findNode(tree->root, "damasco");
    assert(damasco != nullptr);
    assert(damasco->documentIds.size() == 2);
    assert(containsId(damasco->documentIds, 60));
    assert(containsId(damasco->documentIds, 80));
    std::cout << "Teste Duplicatas: PASSOU" << std::endl;

    AVL::destroy(tree);
    std::cout << std::endl;
}

void test_search() {
    std::cout << "Testando o search" << std::endl;
    BinaryTree* tree = AVL::create();
    AVL::insert(tree, "laranja", 1);
    AVL::insert(tree, "maça", 2);
    AVL::insert(tree, "uva", 3);
    AVL::insert(tree, "maça", 4);

    // Busca existente
    SearchResult sres1 = AVL::search(tree, "laranja");
    assert(sres1.found == 1);
    assert(containsId(sres1.documentIds, 1));
    std::cout << "Teste Buscar Palavra Existente: PASSOU" << std::endl;

    // Busca com multiplos IDs
    SearchResult sres2 = AVL::search(tree, "maça");
    assert(sres2.found == 1);
    assert(containsId(sres2.documentIds, 2));
    assert(containsId(sres2.documentIds, 4));
    assert(sres2.documentIds.size() == 2);
    std::cout << "Teste Buscar com Multiplos IDs: PASSOU" << std::endl;

    // Busca inexistente
    SearchResult sres3 = AVL::search(tree, "abacaxi");
    assert(sres3.found == 0);
    assert(sres3.documentIds.empty());
    std::cout << "Teste Buscar Palavra Inexistente: PASSOU" << std::endl;

    // Busca em árvore vazia
    BinaryTree* emptyTree = AVL::create();
    SearchResult sres4 = AVL::search(emptyTree, "qualquer");
    assert(sres4.found == 0);
    assert(sres4.documentIds.empty());
    assert(sres4.numComparisons == 0);
    AVL::destroy(emptyTree);
    std::cout << "Teste Buscar em Arvore Vazia: PASSOU" << std::endl;

    AVL::destroy(tree);
    std::cout << std::endl;
}

void test_destroy() {
    std::cout << "Testando o destroy" << std::endl;

    BinaryTree* tree1 = AVL::create();
    AVL::destroy(tree1);
    std::cout << "Teste Destruir Arvore Vazia: PASSOU" << std::endl;

    BinaryTree* tree2 = AVL::create();
    AVL::insert(tree2, "m", 1);
    AVL::insert(tree2, "f", 2);
    AVL::insert(tree2, "s", 3);
    AVL::insert(tree2, "a", 4);
    AVL::insert(tree2, "h", 5);
    AVL::insert(tree2, "z", 6);
    AVL::destroy(tree2);
    std::cout << "Teste Destruir Arvore Multiplos Nos: PASSOU" << std::endl;

    AVL::destroy(nullptr);
    std::cout << "Teste Destruir nullptr: PASSOU" << std::endl;

    std::cout << std::endl;
}

int main() {
    std::cout << "Iniciando testes para a AVL: \n" << std::endl;

    test_create();
    test_insert();
    test_search();
    test_destroy();

    std::cout << "Todos os testes AVL concluidos com sucesso!" << std::endl;

    return 0;
}