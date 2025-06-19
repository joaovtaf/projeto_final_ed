#include "bst.h"
#include "tree_utils.h"
#include "data.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <limits>

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

std::string generateRandomWord(int length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string word;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    for (int i = 0; i < length; ++i) {
        word += chars[dist(gen)];
    }

    return word;
}

struct BenchmarkResult {
    int numDocuments;
    int totalWords;
    double indexingTime;
    double avgInsertionTime;
    int treeHeight;
    double totalSearchTime;
    double avgSearchTime;
    double maxSearchTime;
    double minSearchTime;
    int totalComparisons;
    double avgComparisons;
    int maxComparisons;
    int minComparisons;
};

BenchmarkResult executeSingleBenchmark(const std::string& directory, int numDocs) {
    BenchmarkResult result;
    result.numDocuments = numDocs;
    
    //criar árvore BST
    BinaryTree* tree = BST::create();
    
    //processar arquivos e construir índice
    std::function<InsertResult(void*, const std::string&, int)> insertCallback = insertWrapper;
    ProcessResult processResult = processFiles(directory, numDocs, insertCallback, tree);
    
    //coletar métricas de indexação
    result.totalWords = processResult.totalWords;
    result.indexingTime = processResult.executionTime;
    result.avgInsertionTime = (processResult.totalWords > 0) ? processResult.executionTime / processResult.totalWords : 0.0;
    result.treeHeight = (tree->root != nullptr) ? tree->root->height : 0;
    
    //executar benchmark de busca com 1000 palavras aleatórias
    double totalBuscaTime = 0.0;
    double tempoMaximoBusca = 0.0;
    double tempoMinimoBusca = std::numeric_limits<double>::infinity();
    int numBuscas = 1000;
    int totalComparisons = 0;
    int maiorCaminho = 0;
    int menorCaminho = std::numeric_limits<int>::max();
    
    for (int i = 0; i < numBuscas; ++i) {
        std::string randomWord = generateRandomWord(8);
        std::string processedWord = processWord(randomWord);
        
        if (processedWord.empty()) {
            continue;
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        SearchResult searchResult = BST::search(tree, processedWord);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> duration = end - start;
        double buscaDuration = duration.count();
        
        totalBuscaTime += buscaDuration;
        
        if (buscaDuration > tempoMaximoBusca) {
            tempoMaximoBusca = buscaDuration;
        }
        
        if (buscaDuration < tempoMinimoBusca) {
            tempoMinimoBusca = buscaDuration;
        }
        
        totalComparisons += searchResult.numComparisons;
        
        if (searchResult.numComparisons > maiorCaminho) {
            maiorCaminho = searchResult.numComparisons;
        }
        if (searchResult.numComparisons < menorCaminho) {
            menorCaminho = searchResult.numComparisons;
        }
    }
    
    //coletar métricas de busca
    result.totalSearchTime = totalBuscaTime;
    result.avgSearchTime = totalBuscaTime / numBuscas;
    result.maxSearchTime = tempoMaximoBusca;
    result.minSearchTime = (tempoMinimoBusca == std::numeric_limits<double>::infinity()) ? 0.0 : tempoMinimoBusca;
    result.totalComparisons = totalComparisons;
    result.avgComparisons = static_cast<double>(totalComparisons) / numBuscas;
    result.maxComparisons = maiorCaminho;
    result.minComparisons = (menorCaminho == std::numeric_limits<int>::max()) ? 0 : menorCaminho;
    
    // Limpar memória
    BST::destroy(tree);
    
    return result;
}

void executeBenchmark(const std::string& directory) {
    std::cout << "\n--- MODO BENCHMARK COMPLETO ---" << std::endl;
    std::cout << "Executando benchmark para 1 a 10000 documentos..." << std::endl;
    
    //eriar arquivo CSV
    std::ofstream csvFile("benchmark_results.csv");
    if (!csvFile.is_open()) {
        std::cout << "Erro: Não foi possível criar o arquivo CSV." << std::endl;
        return;
    }
    
    //escrever cabeçalho do CSV
    csvFile << "NumDocuments,TotalWords,IndexingTime,AvgInsertionTime,TreeHeight,"
            << "TotalSearchTime,AvgSearchTime,MaxSearchTime,MinSearchTime,"
            << "TotalComparisons,AvgComparisons,MaxComparisons,MinComparisons\n";
    
    std::vector<BenchmarkResult> results;
    
    // Definir intervalos para teste
    std::vector<int> testValues;

    for (int i = 1; i <= 10000; i += 500) {
        testValues.push_back(i);
    }
    
    int totalTests = testValues.size();
    int currentTest = 0;
    
    for (int numDocs : testValues) {
        currentTest++;
        std::cout << "Progresso: " << currentTest << "/" << totalTests 
                  << " - Testando com " << numDocs << " documentos..." << std::endl;
        
        try {
            BenchmarkResult result = executeSingleBenchmark(directory, numDocs);
            results.push_back(result);
            
            //escrever resultado no CSV
            csvFile << result.numDocuments << ","
                    << result.totalWords << ","
                    << result.indexingTime << ","
                    << result.avgInsertionTime << ","
                    << result.treeHeight << ","
                    << result.totalSearchTime << ","
                    << result.avgSearchTime << ","
                    << result.maxSearchTime << ","
                    << result.minSearchTime << ","
                    << result.totalComparisons << ","
                    << result.avgComparisons << ","
                    << result.maxComparisons << ","
                    << result.minComparisons << "\n";
            
            csvFile.flush();
            
        } catch (const std::exception& e) {
            std::cout << "Erro ao processar " << numDocs << " documentos: " << e.what() << std::endl;
        }
    }
    
    csvFile.close();
    
    std::cout << "\nBenchmark completo!" << std::endl;
    std::cout << "Resultados salvos em: benchmark_results.csv" << std::endl;
    std::cout << "Total de testes realizados: " << results.size() << std::endl;
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
    if (command != "search" && command != "stats" && command != "benchmark") {
        std::cout << "Erro: Comando inválido '" << command << "'" << std::endl;
        std::cout << "Uso: ./bst <comando> <n_docs> <diretorio>" << std::endl;
        std::cout << "Comandos disponíveis: search, stats, benchmark, benchmark_range" << std::endl;
        return 1;
    }
    
    //para benchmark, não precisamos validar numDocs pois será ignorado
    if (command == "benchmark") {
        std::cout << "Comando Executado: " << command << std::endl;
        std::cout << "Diretório: " << directory << std::endl;
        executeBenchmark(directory);
        return 0;
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
