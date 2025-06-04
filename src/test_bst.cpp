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

    // Testa criação de árvore novamente
    BinaryTree* tree2 = BST::create();
    success &= (tree2 != nullptr && tree2->root == nullptr);
    print_test_result("Criar Arvore Vazia Novamente", success);

    BST::destroy(tree);
    BST::destroy(tree2);

    // Testa árvore com apenas um nó
    BinaryTree* tree3 = BST::create();
    BST::insert(tree3, "primeiro", 1);
    success &= (tree3->root != nullptr && tree3->root->word == "primeiro" && tree3->root->documentIds.size() == 1);
    print_test_result("Criar Arvore com um Nó", success);
    
    BST::destroy(tree3);
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

    // Inserir elemento muito grande
    InsertResult res7 = BST::insert(tree, "pneumoultramicroscopicossilicovulcanoconiotico", 6);
    success &= (tree->root->right->right != nullptr && tree->root->right->right->word == "pneumoultramicroscopicossilicovulcanoconiotico" && contains(tree->root->right->right->documentIds, 6));
    print_test_result("Inserir Elemento Grande", success);

    // Inserir elemento muito pequeno
    InsertResult res8 = BST::insert(tree, "a", 7);
    success &= (tree->root->left->left != nullptr && tree->root->left->left->word == "a" && contains(tree->root->left->left->documentIds, 7));
    print_test_result("Inserir Elemento Pequeno", success);

    // Inserir palavras com letras maiúsculas e minúsculas
    InsertResult res9 = BST::insert(tree, "Apple", 8);
    InsertResult res10 = BST::insert(tree, "apple", 9);
    success &= (tree->root->right->right->left != nullptr && tree->root->right->right->left->word == "Apple" && contains(tree->root->right->right->left->documentIds, 8));
    success &= (tree->root->right->right->right != nullptr && tree->root->right->right->right->word == "apple" && contains(tree->root->right->right->right->documentIds, 9));
    print_test_result("Inserir Palavras com Maiúsculas e Minúsculas", success);

    // Inserir palavra semelhante a outra já existente
    InsertResult res11 = BST::insert(tree, "antonia", 10);
    success &= (tree->root->left->right != nullptr && tree->root->left->right->word == "antonia" && contains(tree->root->left->right->documentIds, 10));
    print_test_result("Inserir Palavra Semelhante", success);

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

    // Buscar elemento existente
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

    // Buscar em árvore nula
    SearchResult res6 = BST::search(nullptr, "dilmar");
    success &= (res6.found == 0 && res6.documentIds.empty());
    print_test_result("Buscar em Arvore Nula", success);

    // Buscar um elemento muito grande
    SearchResult res7 = BST::search(tree, "pneumoultramicroscopicossilicovulcanoconiotico");
    success &= (res7.found == 0 && res7.documentIds.empty());
    print_test_result("Buscar Elemento Grande Inexistente", success);

    // Buscar elemento com letras maiúsculas e minúsculas
    SearchResult res8 = BST::search(tree, "Apple");
    success &= (res8.found == 0 && res8.documentIds.empty());
    print_test_result("Buscar Elemento Maiúsculo", success);

    // Buscar palavra semelhante a outra já existente
    SearchResult res9 = BST::search(tree, "antonia");
    success &= (res9.found == 1 && contains(res9.documentIds, 10));
    print_test_result("Buscar Elemento Semelhante", success);

    BST::destroy(tree);
}

// Testa a função destroy
void test_destroy() {
    std::cout << "\nTestando a destroy" << std::endl;
    bool success = true;

    // Destruir árvore não vazia
    BinaryTree* tree1 = BST::create();
    BST::insert(tree1, "bernardo", 1);
    BST::insert(tree1, "roger", 2);
    try {
        BST::destroy(tree1);
        tree1 = nullptr;
        if (tree1 == nullptr) {
            print_test_result("Destruir Arvore Nao Vazia", true);
        } else {
            success = false;
            print_test_result("Destruir Arvore Nao Vazia", false);
        }
    } catch (...) {
        success = false;
        print_test_result("Destruir Arvore Nao Vazia", false);
    }

    // Destruir árvore vazia
    BinaryTree* tree2 = BST::create(); 
    try {
        BST::destroy(tree2);
        tree2 = nullptr;
        if (tree2 == nullptr) {
            print_test_result("Destruir Arvore Vazia", true);
        } else {
            success = false;
            print_test_result("Destruir Arvore Vazia", false);
        }
    } catch (...) {
        success = false;
        print_test_result("Destruir Arvore Vazia", false);
    }

    // Destruir ponteiro nulo
    try {
        BST::destroy(nullptr);
        print_test_result("Destruir Ponteiro Nulo", true);
    } catch (...) {
        success = false;
        print_test_result("Destruir Ponteiro Nulo", false);
    }

    // Recriar árvore e verificar se a criação funciona após destruir
    BinaryTree* tree3 = BST::create(); 
    BST::insert(tree3, "teste", 100);
    if (tree3 != nullptr && tree3->root != nullptr) {
        print_test_result("Recriar Arvore Após Destruir", true);
    } else {
        success = false;
        print_test_result("Recriar Arvore Após Destruir", false);
    }

    BST::destroy(tree3);
}

// Main para rodar os testes
int main() {
    std::cout << "Iniciando testes para a BST: \n" << std::endl;

    test_create();
    test_insert();
    test_search();
    test_destroy();

    std::cout << "\nTestes concluídos." << std::endl;

    return 0;
}
