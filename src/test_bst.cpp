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