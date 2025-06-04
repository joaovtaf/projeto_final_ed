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
