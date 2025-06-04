#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include "bst.h"
#include "tree_utils.h"

// Função auxiliar para verificar se um vetor contém um elemento
bool contains(const std::vector<int>& vec, int value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

// Função auxiliar para imprimir resultados de teste
void print_test_result(const std::string& test_name, bool success) {
    std::cout << "Teste '" << test_name << "': " << (success ? "PASSOU" : "FALHOU") << std::endl;
}

// Testa a criação de uma árvore vazia
void test_create() {
    std::cout << "\nTestando a create" << std::endl;
    BinaryTree* tree = BST::create();
    bool success = (tree != nullptr && tree->root == nullptr);
    print_test_result("Criar Arvore Vazia", success);
    BST::destroy(tree);
}

// Testa a inserção em uma árvore vazia e inserções subsequentes
void test_insert() {
    std::cout << "\nTestando o insert" << std::endl;
    BinaryTree* tree = BST::create();
    bool success = true;

    // Inserir na árvore vazia
    InsertResult res1 = BST::insert(tree, "joao", 1);
    success &= (tree->root != nullptr && tree->root->word == "joao" && contains(tree->root->documentIds, 1));
    print_test_result("Inserir na Arvore Vazia", success);

    // Inserir elemento menor (esquerda)
    InsertResult res2 = BST::insert(tree, "antonio", 2);
    success &= (tree->root->left != nullptr && tree->root->left->word == "antonio" && contains(tree->root->left->documentIds, 2));
    print_test_result("Inserir Elemento Menor", success);

    // Inserir elemento maior (direita)
    InsertResult res3 = BST::insert(tree, "roger", 3);
    success &= (tree->root->right != nullptr && tree->root->right->word == "roger" && contains(tree->root->right->documentIds, 3));
    print_test_result("Inserir Elemento Maior", success);

    // Inserir outro elemento entre os já criados
    InsertResult res4 = BST::insert(tree, "dilmar", 4);
    success &= (tree->root->right->left != nullptr && tree->root->right->left->word == "dilmar" && contains(tree->root->right->left->documentIds, 4));
    print_test_result("Inserir Elemento", success);

    // Inserir palavra duplicada com ID diferente
    InsertResult res5 = BST::insert(tree, "joao", 5); 
    success &= (contains(tree->root->documentIds, 1) && contains(tree->root->documentIds, 5) && tree->root->documentIds.size() == 2);
    print_test_result("Inserir Palavra Duplicada (ID diferente)", success);

    // Inserir palavra duplicada com ID igual
    InsertResult res6 = BST::insert(tree, "dilmar", 4);
    success &= (contains(tree->root->left->documentIds, 2) && tree->root->left->documentIds.size() == 1);
    print_test_result("Inserir Palavra Duplicada (ID igual)", success);

    BST::destroy(tree);
}

// Testa a busca por elementos
void test_search() {
    std::cout << "\nTestando a search" << std::endl;
    BinaryTree* tree = BST::create();
    BST::insert(tree, "dilmar", 1);
    BST::insert(tree, "antonio", 2);
    BST::insert(tree, "roger", 3);
    BST::insert(tree, "dilmar", 5);
    bool success = true;

    // Buscar elemento existente (raiz)
    SearchResult res1 = BST::search(tree, "dilmar");
    success &= (res1.found == 1 && contains(res1.documentIds, 1) && contains(res1.documentIds, 5) && res1.documentIds.size() == 2);
    print_test_result("Buscar Elemento Existente (Raiz)", success);

    // Buscar elemento existente em uma folha da esquerda
    SearchResult res2 = BST::search(tree, "antonio");
    success &= (res2.found == 1 && contains(res2.documentIds, 2) && res2.documentIds.size() == 1);
    print_test_result("Buscar Elemento Existente (Folha Esquerda)", success);

    // Buscar elemento existente em uma folha da direita
    SearchResult res3 = BST::search(tree, "roger"); 
    success &= (res3.found == 1 && contains(res3.documentIds, 3) && res3.documentIds.size() == 1);
    print_test_result("Buscar Elemento Existente (Folha Direita)", success);

    // Buscar elemento inexistente
    SearchResult res4 = BST::search(tree, "joao");
    success &= (res4.found == 0 && res4.documentIds.empty());
    print_test_result("Buscar Elemento Inexistente", success);

    // Buscar em árvore vazia
    BST::destroy(tree);
    tree = BST::create();
    SearchResult res5 = BST::search(tree, "dilmar");
    success &= (res5.found == 0 && res5.documentIds.empty());
    print_test_result("Buscar em Arvore Vazia", success);

    // Buscar em árvore nula (teste de segurança)
    SearchResult res6 = BST::search(nullptr, "dilmar");
    success &= (res6.found == 0 && res6.documentIds.empty());
    print_test_result("Buscar em Arvore Nula", success);

    BST::destroy(tree);
}