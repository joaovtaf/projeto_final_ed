#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "rbt.h"
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
    BinaryTree* tree1 =RBT::create();
    assert(tree1 != nullptr && tree1->root == nullptr);
    std::cout << "Teste Criar Arvore Vazia: PASSOU" << std::endl;
   RBT::destroy(tree1);

    // Criar árvore e inserir um no (verificação indireta)
    BinaryTree* tree2 =RBT::create();
   RBT::insert(tree2, "raiz", 1);
    assert(tree2 != nullptr && tree2->root != nullptr && tree2->root->word == "raiz");
    std::cout << "Teste Criar Arvore com um No: PASSOU" << std::endl;
   RBT::destroy(tree2);

    std::cout << std::endl;
}

void test_insert() {
    std::cout << "Testando o insert" << std::endl;
    BinaryTree* tree =RBT::create();

    // Inserção que causa rotação Left-Right (LR)
   RBT::insert(tree, "banana", 10);
   RBT::insert(tree, "abacate", 20);
   RBT::insert(tree, "acerola", 30); // Deve causar rotação LR

    // Após rotação LR
    assert(tree->root != nullptr && tree->root->word == "acerola");
    assert(tree->root->left != nullptr && tree->root->left->word == "abacate");
    assert(tree->root->right != nullptr && tree->root->right->word == "banana");
    std::cout << "Teste Rotação Left-Right (LR): PASSOU" << std::endl;

    // Teste de inserçao normal à direita.
   RBT::insert(tree, "caqui", 40);

    assert(tree->root->right->right != nullptr && tree->root->right->right->word == "caqui");
    std::cout << "Teste Inserção Direita Após LR: PASSOU" << std::endl;
    printTree(tree);
    // Inserção que causa rotação Right-Left (RL).
   RBT::insert(tree, "figo", 50);
    printTree(tree);
   RBT::insert(tree, "damasco", 60); // Deve causar rotação RL
    printTree(tree);
    
    // Verificacoes pós RL
    assert(tree->root->right->right == nullptr && tree->root->right->left->word == "damasco");
    assert(tree->root->word == "caqui");
    std::cout << "Teste Rotação Right-Left (RL): PASSOU" << std::endl;

    // Inserção adicional
   RBT::insert(tree, "goiaba", 70);
    assert(tree->root->right->right->right == nullptr && tree->root->right->right->word == "goiaba");

    // Teste de duplicatas
   RBT::insert(tree, "damasco", 60); // repetido
   RBT::insert(tree, "damasco", 80); // novo

    Node* damasco = findNode(tree->root, "damasco");
    assert(damasco != nullptr);
    assert(damasco->documentIds.size() == 2);
    assert(containsId(damasco->documentIds, 60));
    assert(containsId(damasco->documentIds, 80));
    std::cout << "Teste Duplicatas: PASSOU" << std::endl;

   RBT::destroy(tree);
    std::cout << std::endl;
}

void test_search() {
    std::cout << "Testando o search" << std::endl;
    BinaryTree* tree =RBT::create();
   RBT::insert(tree, "laranja", 1);
   RBT::insert(tree, "maça", 2);
   RBT::insert(tree, "uva", 3);
   RBT::insert(tree, "maça", 4);

    // Busca existente
    SearchResult sres1 =RBT::search(tree, "laranja");
    assert(sres1.found == 1);
    assert(containsId(sres1.documentIds, 1));
    std::cout << "Teste Buscar Palavra Existente: PASSOU" << std::endl;

    // Busca com multiplos IDs
    SearchResult sres2 =RBT::search(tree, "maça");
    assert(sres2.found == 1);
    assert(containsId(sres2.documentIds, 2));
    assert(containsId(sres2.documentIds, 4));
    assert(sres2.documentIds.size() == 2);
    std::cout << "Teste Buscar com Multiplos IDs: PASSOU" << std::endl;

    // Busca inexistente
    SearchResult sres3 =RBT::search(tree, "abacaxi");
    assert(sres3.found == 0);
    assert(sres3.documentIds.empty());
    std::cout << "Teste Buscar Palavra Inexistente: PASSOU" << std::endl;

    // Busca em árvore vazia
    BinaryTree* emptyTree =RBT::create();
    SearchResult sres4 =RBT::search(emptyTree, "qualquer");
    assert(sres4.found == 0);
    assert(sres4.documentIds.empty());
    assert(sres4.numComparisons == 0);
   RBT::destroy(emptyTree);
    std::cout << "Teste Buscar em Arvore Vazia: PASSOU" << std::endl;

   RBT::destroy(tree);
    std::cout << std::endl;
}

void test_destroy() {
    std::cout << "Testando o destroy" << std::endl;

    BinaryTree* tree1 =RBT::create();
   RBT::destroy(tree1);
    std::cout << "Teste Destruir Arvore Vazia: PASSOU" << std::endl;

    BinaryTree* tree2 =RBT::create();
   RBT::insert(tree2, "m", 1);
   RBT::insert(tree2, "f", 2);
   RBT::insert(tree2, "s", 3);
   RBT::insert(tree2, "a", 4);
   RBT::insert(tree2, "h", 5);
   RBT::insert(tree2, "z", 6);
   RBT::destroy(tree2);
    std::cout << "Teste Destruir Arvore Multiplos Nos: PASSOU" << std::endl;

   RBT::destroy(nullptr);
    std::cout << "Teste Destruir nullptr: PASSOU" << std::endl;

    std::cout << std::endl;
}

int main() {
    std::cout << "Iniciando testes para a RBT: \n" << std::endl;

    test_create();
    test_insert();
    test_search();
    test_destroy();

    std::cout << "Todos os testes RBT concluidos com sucesso!" << std::endl;

    return 0;
}