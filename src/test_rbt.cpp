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

// Função para encontrar um nó na árvore
Node* findNode(Node* root, Node* NIL, const std::string& word) {
    if (root == NIL) return NIL;
    if (word == root->word) return root;
    if (word < root->word) return findNode(root->left, NIL, word);
    else return findNode(root->right, NIL, word);
}

void printTreeStructureRBT(Node* node, Node* NIL, int level = 0) {
    if (node == NIL) return;
    printTreeStructureRBT(node->right, NIL, level + 1);
    
    for (int i = 0; i < level; i++) std::cout << "    ";
    std::cout << node->word << "(" << (node->isRed ? "R" : "B") << ")\n";
    
    printTreeStructureRBT(node->left, NIL, level + 1);
}

void printTreeRBT(BinaryTree* tree) {
    std::cout << "\nEstrutura da árvore:\n";
    printTreeStructureRBT(tree->root, tree->NIL);
    std::cout << "-------------------\n";
}

// Testes 
void test_create() {
    std::cout << "Testando a create" << std::endl;

    // Criar arvore vazia
    BinaryTree* tree1 =RBT::create();
    assert(tree1 != nullptr && tree1->root == tree1->NIL);
    std::cout << "Teste Criar Arvore Vazia: PASSOU" << std::endl;
    RBT::destroy(tree1);

    // Criar árvore e inserir um no
    BinaryTree* tree2 =RBT::create();
    RBT::insert(tree2, "raiz", 1);
    assert(tree2 != nullptr && tree2->root != tree2->NIL && tree2->root->word == "raiz");
    assert(tree2->root->isRed == false); // Raiz sempre preta
    std::cout << "Teste Criar Arvore com um No: PASSOU" << std::endl;
    RBT::destroy(tree2);

    std::cout << std::endl;
}

void test_insert() {
    std::cout << "Testando o insert" << std::endl;
    BinaryTree* tree =RBT::create();
    Node* NIL = tree->NIL;
  
    // Teste 1: Insercao básica e propriedades RBT
    RBT::insert(tree, "banana", 10);
    assert(tree->root != NIL);
    assert(tree->root->word == "banana");
    assert(tree->root->isRed == false); // Raiz sempre preta

    std::cout << "Teste Inserção básica 1: PASSOU" << std::endl;
   
    // Teste 2: Insercao à esquerda
    RBT::insert(tree, "abacate", 20); 
    // Verificar estrutura:
    //     banana(B)
    // abacate(R)
    assert(tree->root->left != NIL);
    assert(tree->root->left->word == "abacate");
    assert(tree->root->left->isRed == true); // Novo no deve ser vermelho
    assert(tree->root->left->parent == tree->root);

    std::cout << "Teste Inserções à esquerda 2: PASSOU" << std::endl;

    // Teste 3: Inserção que causa ajustes
    RBT::insert(tree, "acerola", 30);
    // Após ajustes, a estrutura deve ser:
    //      acerola(B)      
    // abacate(R) banana(R)
    assert(tree->root->word == "acerola");
    assert(tree->root->isRed == false);
    
    // Filho esquerdo
    assert(tree->root->left != NIL);
    assert(tree->root->left->word == "abacate");
    assert(tree->root->left->isRed == true);
    assert(tree->root->left->parent == tree->root);
    
    // Filho direito
    assert(tree->root->right != NIL);
    assert(tree->root->right->word == "banana");
    assert(tree->root->right->isRed == true);
    assert(tree->root->right->parent == tree->root);
    
    std::cout << "Teste Inserção com Ajustes 3: PASSOU" << std::endl;

    // Teste 4: Inserção à direita 
    RBT::insert(tree, "caqui", 40);
    
    // Estrutura deve ser:
    //        acerola(B)
    // abacate(B) banana(B)
    //                caqui(R)
    assert(tree->root->word == "acerola");
    assert(tree->root->isRed == false);
    
    // Filhos devem ter virado pretos
    assert(tree->root->left->isRed == false);
    assert(tree->root->right->isRed == false);
    
    // Novo nó à direita
    assert(tree->root->right->right != NIL);
    assert(tree->root->right->right->word == "caqui");
    assert(tree->root->right->right->isRed == true);
    assert(tree->root->right->right->parent == tree->root->right);
    
    // Teste 5: Inserção que causa novos ajustes
    RBT::insert(tree, "damasco", 50);
    
    // Estrutura após inserção:
    //          acerola(B)
    // abacate(B)      caqui(B)
    //              banana(R) damasco(R)
    assert(tree->root->word == "acerola");
    assert(tree->root->right->word == "caqui");
    assert(tree->root->right->isRed == false);
    
    // Filho esquerdo de caqui
    assert(tree->root->right->left != NIL);
    assert(tree->root->right->left->word == "banana");
    assert(tree->root->right->left->isRed == true);
    assert(tree->root->right->left->parent == tree->root->right);
    
    // Filho direito de caqui
    assert(tree->root->right->right != NIL);
    assert(tree->root->right->right->word == "damasco");
    assert(tree->root->right->right->isRed == true);
    assert(tree->root->right->right->parent == tree->root->right);
    
    std::cout << "Teste Inserções Múltiplas 5: PASSOU" << std::endl;

    // Teste 6: Inserção de duplicatas 
    Node* damascoNode = findNode(tree->root, NIL, "damasco");
    RBT::insert(tree, "damasco", 60);
    RBT::insert(tree, "damasco", 80);
    
    assert(damascoNode != NIL);
    assert(damascoNode->documentIds.size() == 3);
    assert(containsId(damascoNode->documentIds, 50));
    assert(containsId(damascoNode->documentIds, 60));
    assert(containsId(damascoNode->documentIds, 80));
    
    // Verificar se a estrutura permaneceu correta
    assert(tree->root->word == "acerola");
    assert(tree->root->right->word == "caqui");
    assert(tree->root->right->right->word == "damasco");
    
    std::cout << "Teste Duplicatas 6: PASSOU" << std::endl;

    RBT::destroy(tree);
    std::cout << std::endl;;
}

void test_search() {
    std::cout << "Testando o search" << std::endl;
    BinaryTree* tree = RBT::create();

    RBT::insert(tree, "laranja", 1);
    RBT::insert(tree, "maça", 2);
    RBT::insert(tree, "uva", 3);
    RBT::insert(tree, "maça", 4);

    // Busca existente
    SearchResult sres1 = RBT::search(tree, "laranja");
    assert(sres1.found == 1);
    assert(containsId(sres1.documentIds, 1));
    std::cout << "Teste Buscar Palavra Existente: PASSOU" << std::endl;

    // Busca com múltiplos IDs
    SearchResult sres2 = RBT::search(tree, "maça");
    assert(sres2.found == 1);
    assert(sres2.documentIds.size() == 2);
    assert(containsId(sres2.documentIds, 2));
    assert(containsId(sres2.documentIds, 4));
    std::cout << "Teste Buscar com Múltiplos IDs: PASSOU" << std::endl;

    // Busca inexistente
    SearchResult sres3 = RBT::search(tree, "abacaxi");
    assert(sres3.found == 0);
    assert(sres3.documentIds.empty());
    std::cout << "Teste Buscar Palavra Inexistente: PASSOU" << std::endl;

    // Busca em árvore vazia
    BinaryTree* emptyTree = RBT::create();
    SearchResult sres4 = RBT::search(emptyTree, "qualquer");
    assert(sres4.found == 0);
    assert(sres4.documentIds.empty());
    RBT::destroy(emptyTree);
    std::cout << "Teste Buscar em Árvore Vazia: PASSOU" << std::endl;

    RBT::destroy(tree);
    std::cout << std::endl;
}

void test_destroy() {
    std::cout << "Testando o destroy" << std::endl;

    BinaryTree* tree1 = RBT::create();
    RBT::destroy(tree1);
    std::cout << "Teste Destruir Árvore Vazia: PASSOU" << std::endl;

    BinaryTree* tree2 = RBT::create();
    RBT::insert(tree2, "m", 1);
    RBT::insert(tree2, "f", 2);
    RBT::insert(tree2, "s", 3);
    RBT::insert(tree2, "a", 4);
    RBT::insert(tree2, "h", 5);
    RBT::insert(tree2, "z", 6);
    RBT::destroy(tree2);
    std::cout << "Teste Destruir Árvore Múltiplos Nós: PASSOU" << std::endl;

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