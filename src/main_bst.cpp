#include "bst.h"
#include "tree_utils.h"
#include "data.h"
#include <iostream>
#include <string>

//wrapper para a função insert da BST
InsertResult insertWrapper(void* tree, const std::string& word, int documentId) {
    return BST::insert(static_cast<BinaryTree*>(tree), word, documentId);
}

void executeSearch(BinaryTree* tree) {
    std::string word;
    std::cout << "\n--- MODO BUSCA ---" << std::endl;
    std::cout << "Digite palavras para buscar (digite 'quit' para sair):" << std::endl;
    
    while (true) {
        std::cout << "\nBuscar palavra: ";
        std::cin >> word;
        
        if (word == "quit") {
            break;
        }
        
        //processar a palavra da mesma forma que durante a indexação
        std::string processedWord = processWord(word);
        
        if (processedWord.empty()) {
            std::cout << "Palavra inválida (apenas caracteres alfanuméricos são aceitos)." << std::endl;
            continue;
        }
        
        SearchResult result = BST::search(tree, processedWord);
        
        if (result.found) {
            std::cout << "Palavra '" << processedWord << "' encontrada!" << std::endl;
            std::cout << "Documentos: ";
            for (size_t i = 0; i < result.documentIds.size(); i++) {
                std::cout << result.documentIds[i];
                if (i < result.documentIds.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
            std::cout << "Tempo de busca: " << result.executionTime << " segundos" << std::endl;
            std::cout << "Comparações realizadas: " << result.numComparisons << std::endl;
        } else {
            std::cout << "Palavra '" << processedWord << "' não encontrada." << std::endl;
            std::cout << "Tempo de busca: " << result.executionTime << " segundos" << std::endl;
            std::cout << "Comparações realizadas: " << result.numComparisons << std::endl;
        }
    }
}

void executeStats(BinaryTree* tree, ProcessResult processResult) {
    std::cout << "\n--- MODO ESTATÍSTICAS ---" << std::endl;
    std::cout << "Número de palavras processadas: " << processResult.totalWords << std::endl;
    std::cout << "Tempo total de indexação: " << processResult.executionTime << " segundos" << std::endl;
    std::cout << "Altura da árvore: " << height(tree->root) << std::endl;
}

int main(int argc, char* argv[]) {
    //verificar argumentos
    if (argc != 4) {
        std::cout << "Uso: ./bst <comando> <n_docs> <diretorio>" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    
    std::string command = argv[1];
    int numDocs = std::stoi(argv[2]);
    std::string directory = argv[3];
    
    //validar comando
    if (command != "search" && command != "stats") {
        std::cout << "Erro: Comando inválido '" << command << "'" << std::endl;
        std::cout << "Uso: ./bst <comando> <n_docs> <diretorio>" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    
    //validar número de documentos
    if (numDocs <= 0) {
        std::cout << "Erro: Número de documentos deve ser positivo" << std::endl;
        return 1;
    }
    
    std::cout << "Comando Executado: " << command << std::endl;
    std::cout << "Número de Documentos: " << numDocs << std::endl;
    std::cout << "Diretório: " << directory << std::endl;
    
    //criar árvore BST
    BinaryTree* tree = BST::create();
    
    //processar arquivos e construir índice
    std::function<InsertResult(void*, const std::string&, int)> insertCallback = insertWrapper;
    ProcessResult processResult = processFiles(directory, numDocs, insertCallback, tree);
    
    //executar comando solicitado
    if (command == "search") {
        executeSearch(tree);
    } else if (command == "stats") {
        executeStats(tree, processResult);
    }
    
    //limpar memória
    BST::destroy(tree);
    
    return 0;
}
