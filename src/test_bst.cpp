#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include "bst.h"
#include "tree_utils.h"

// Funções Auxiliares de Teste 

// Função para verificar se um ID existe em um vetor de IDs
bool containsId(const std::vector<int>& ids, int id) {
    for (size_t i = 0; i < ids.size(); i++) {
        if (ids[i] == id) {
            return true;
        }
    }
    return false;
}

// Funcao para verificar a estrutura da arvore criada
bool checkTreeStructure(Node* node, const std::string& word, Node* expected_left, Node* expected_right) {
    if (!node) return false; 
    if (node->word != word) return false;
    if (node->left != expected_left) return false;
    if (node->right != expected_right) return false;
    return true;
}

// Função para encontrar um nó na árvore
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

    // Criar árvore vazia
    BinaryTree* tree1 = BST::create();
    assert(tree1 != nullptr && tree1->root == nullptr);
    std::cout << "Teste Criar Arvore Vazia: PASSOU" << std::endl;
    BST::destroy(tree1);

    // Criar outra árvore vazia
    BinaryTree* tree2 = BST::create();
    assert(tree2 != nullptr && tree2->root == nullptr);
    std::cout << "Teste Criar Arvore Vazia Novamente: PASSOU" << std::endl;
    BST::destroy(tree2);

    // Criar árvore e inserir um nó (verificação indireta)
    BinaryTree* tree3 = BST::create();
    BST::insert(tree3, "raiz", 1);
    assert(tree3 != nullptr && tree3->root != nullptr && tree3->root->word == "raiz");
    std::cout << "Teste Criar Arvore com um No: PASSOU" << std::endl;
    BST::destroy(tree3);

    std::cout << std::endl;
}

void test_insert() {
    std::cout << "Testando o insert" << std::endl;
    BinaryTree* tree = BST::create();

    // Inserir na árvore vazia
    BST::insert(tree, "banana", 10);
    assert(tree->root != nullptr && tree->root->word == "banana");
    assert(containsId(tree->root->documentIds, 10));
    assert(tree->root->left == nullptr && tree->root->right == nullptr);
    std::cout << "Teste Inserir na Arvore Vazia: PASSOU" << std::endl;

    // Inserir elemento menor
    BST::insert(tree, "abacate", 20);
    assert(tree->root->left != nullptr && tree->root->left->word == "abacate");
    assert(containsId(tree->root->left->documentIds, 20));
    assert(tree->root->right == nullptr);
    std::cout << "Teste Inserir Elemento Menor: PASSOU" << std::endl;

    // Inserir elemento maior
    BST::insert(tree, "caqui", 30);
    assert(tree->root->right != nullptr && tree->root->right->word == "caqui");
    assert(containsId(tree->root->right->documentIds, 30));
    std::cout << "Teste Inserir Elemento Maior: PASSOU" << std::endl;

    // Inserir elemento intermediário (requer navegação)
    BST::insert(tree, "acerola", 40);
    Node* abacateNode = findNode(tree->root, "abacate");
    assert(abacateNode != nullptr && abacateNode->right != nullptr && abacateNode->right->word == "acerola");
    assert(containsId(abacateNode->right->documentIds, 40));
    std::cout << "Teste Inserir Elemento: PASSOU" << std::endl; 

    // Inserir palavra duplicada (ID diferente)
    BST::insert(tree, "banana", 11);
    assert(tree->root != nullptr && tree->root->word == "banana");
    assert(containsId(tree->root->documentIds, 10)); 
    assert(containsId(tree->root->documentIds, 11));
    assert(tree->root->documentIds.size() == 2);    
    std::cout << "Teste Inserir Palavra Duplicada (ID diferente): PASSOU" << std::endl;

    // Inserir palavra duplicada (ID igual)
    BST::insert(tree, "abacate", 20);
    abacateNode = findNode(tree->root, "abacate"); 
    assert(abacateNode != nullptr);
    assert(containsId(abacateNode->documentIds, 20));
    assert(abacateNode->documentIds.size() == 1);
    std::cout << "Teste Inserir Palavra Duplicada (ID igual): PASSOU" << std::endl;

    // Inserir elemento que vai à direita de um nó direito
    BST::insert(tree, "damasco", 50);
    Node* caquiNode = findNode(tree->root, "caqui");
    assert(caquiNode != nullptr && caquiNode->right != nullptr && caquiNode->right->word == "damasco");
    assert(containsId(caquiNode->right->documentIds, 50));
    std::cout << "Teste Inserir Elemento Grande: PASSOU" << std::endl;

    // Inserir elemento que vai à esquerda de um nó esquerdo
    BST::insert(tree, "a", 60); 
    abacateNode = findNode(tree->root, "abacate"); 
    assert(abacateNode != nullptr && abacateNode->left != nullptr && abacateNode->left->word == "a");
    assert(containsId(abacateNode->left->documentIds, 60));
    std::cout << "Teste Inserir Elemento Pequeno: PASSOU" << std::endl;

    BST::destroy(tree);
    std::cout << std::endl;
}

void test_search() {
    std::cout << "Testando o search" << std::endl;
    BinaryTree* tree = BST::create();
    BST::insert(tree, "laranja", 1);
    BST::insert(tree, "maça", 2);
    BST::insert(tree, "uva", 3);
    BST::insert(tree, "maça", 4); 

    // Buscar palavra existente
    SearchResult sres1 = BST::search(tree, "laranja");
    assert(sres1.found == 1);
    assert(containsId(sres1.documentIds, 1));
    assert(sres1.documentIds.size() == 1);
    // assert(sres1.numComparisons == 1);
    std::cout << "Teste Buscar Palavra Existente (Raiz): PASSOU" << std::endl;

    // Buscar palavra existente (folha esquerda)
    SearchResult sres2 = BST::search(tree, "maça");
    assert(sres2.found == 1);
    assert(containsId(sres2.documentIds, 2));
    assert(containsId(sres2.documentIds, 4));
    assert(sres2.documentIds.size() == 2);
    std::cout << "Teste Buscar Palavra Existente (Esquerda): PASSOU" << std::endl;

    // Buscar palavra existente (folha direita)
    SearchResult sres3 = BST::search(tree, "uva");
    assert(sres3.found == 1);
    assert(containsId(sres3.documentIds, 3));
    assert(sres3.documentIds.size() == 1);
    std::cout << "Teste Buscar Palavra Existente (Direita): PASSOU" << std::endl;

    // Buscar palavra inexistente (menor que todas)
    SearchResult sres4 = BST::search(tree, "abacaxi");
    assert(sres4.found == 0);
    assert(sres4.documentIds.empty());
    std::cout << "Teste Buscar Palavra Inexistente (Menor): PASSOU" << std::endl;

    // Buscar palavra inexistente (maior que todas)
    SearchResult sres5 = BST::search(tree, "zucchini");
    assert(sres5.found == 0);
    assert(sres5.documentIds.empty());
    std::cout << "Teste Buscar Palavra Inexistente (Maior): PASSOU" << std::endl;

    // Buscar palavra inexistente
    SearchResult sres6 = BST::search(tree, "pera");
    assert(sres6.found == 0);
    assert(sres6.documentIds.empty());
    std::cout << "Teste Buscar Palavra Inexistente: PASSOU" << std::endl;

    // Buscar em árvore vazia
    BinaryTree* emptyTree = BST::create();
    SearchResult sres7 = BST::search(emptyTree, "qualquer");
    assert(sres7.found == 0);
    assert(sres7.documentIds.empty());
    assert(sres7.numComparisons == 0);
    std::cout << "Teste Buscar em Arvore Vazia: PASSOU" << std::endl;
    BST::destroy(emptyTree);

    BST::destroy(tree);
    std::cout << std::endl;
}

void test_destroy() {
    std::cout << "Testando o destroy" << std::endl;

    // Destruir árvore vazia
    BinaryTree* tree1 = BST::create();
    BST::destroy(tree1);
    std::cout << "Teste Destruir Arvore Vazia: PASSOU" << std::endl;

    // Destruir árvore com um nó
    BinaryTree* tree2 = BST::create();
    BST::insert(tree2, "unico", 1);
    BST::destroy(tree2);
    std::cout << "Teste Destruir Arvore com Um No: PASSOU" << std::endl;

    // Destruir árvore com múltiplos nós
    BinaryTree* tree3 = BST::create();
    BST::insert(tree3, "m", 1);
    BST::insert(tree3, "f", 2);
    BST::insert(tree3, "s", 3);
    BST::insert(tree3, "a", 4);
    BST::insert(tree3, "h", 5);
    BST::insert(tree3, "z", 6);
    BST::destroy(tree3);
    std::cout << "Teste Destruir Arvore Multiplos Nos: PASSOU" << std::endl;

    // Destruir nullptr
    BST::destroy(nullptr);
    std::cout << "Teste Destruir Arvore Nula (nullptr): PASSOU" << std::endl;

    std::cout << std::endl;
}

int main() {
    std::cout << "Iniciando testes para a BST: \n" << std::endl;

    test_create();
    test_insert();
    test_search();
    test_destroy();

    std::cout << "Todos os conjuntos de testes concluidos" << std::endl;

    return 0;
}
