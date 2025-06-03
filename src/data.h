#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <cctype> // para std::tolower
#include <functional> // para std::function

/**
 * @struct ProcessResult
 * @brief Armazena resultados do processamento de arquivos
 * @var totalWords - Total de palavras processadas (incluindo repeticoes)
 * @var executionTime - Tempo total de processamento em segundos
 */
struct ProcessResult {
    int totalWords;
    double executionTime;
};

/**
 * @brief Processa uma palavra removendo caracteres nao alfanumericos e convertendo para minúsculas
 * @param word Palavra a ser processada
 * @return std::string Palavra processada
 */
std::string processWord(const std::string& word);

/**
 * @brief Processa múltiplos arquivos de texto em um diretorio
 * @param directory Caminho do diretório contendo os arquivos
 * @param numFiles Numero de arquivos a processar
 * @param insertCallback Funçao de callback para inserção de palavras
 * @param tree Arvore a ser construida apos o processamento
 * @return ProcessResult Resultados do processamento
 */
ProcessResult processFiles(
    const std::string& directory, 
    int numFiles,
    const std::function<InsertResult(void* ,const std::string&, int)>& insertCallback,
    void* tree
);

#endif 