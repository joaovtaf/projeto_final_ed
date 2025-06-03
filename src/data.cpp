#include "data.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <unordered_set>

// processamento das palavras
std::string processWord(const std::string& word) {
    std::string processed;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            processed += std::tolower(c);
        }
    }
    return processed;
}

// processamento dos arquivos
ProcessResult processFiles(
    const std::string& directory, 
    int numFiles,
    const std::function<void(const std::string&, int)>& insertCallback
) {
    auto start = std::chrono::high_resolution_clock::now();
    int totalWords = 0;
    int uniqueWords = 0;
    std::unordered_set<std::string> uniqueSet;

    for (int docId = 0; docId < numFiles; docId++) { // buscando os arquivos
        std::string filePath = directory + "/" + std::to_string(docId) + ".txt";
        std::ifstream file(filePath);
        
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir arquivo: " << filePath << std::endl;
            continue;
        }

        std::string line;
        if (std::getline(file, line)) { // palavras apenas na primeira linha
            std::istringstream iss(line);
            std::string word;
            
            while (iss >> word) {
                std::string processed = processWord(word);
                if (!processed.empty()) {
                    insertCallback(processed, docId);
                    totalWords++;
                    
                    // contagem de palavras únicas
                    if (uniqueSet.find(processed) == uniqueSet.end()) {
                        uniqueSet.insert(processed);
                        uniqueWords++;
                    }
                }
            }
        }
        file.close();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    return ProcessResult{totalWords, uniqueWords, elapsed.count()};
}