#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <cctype> // para std::tolower
#include <functional> // para std::function
#include <fstream>
#include <iostream>
#include <chrono>
#include <unordered_set>

// estrutura para armazenar estatistica de processamento
struct ProcessResult {
    int totalWords;
    int uniqueWords;
    double executionTime;
};

// função para processar as palavras
std::string processWord(const std::string& word);

// função para processar os arquivos
ProcessResult processFiles(
    const std::string& directory, 
    int numFiles,
    const std::function<void(const std::string&, int)>& insertCallback
);

#endif 