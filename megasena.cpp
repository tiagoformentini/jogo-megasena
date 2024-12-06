#include <iostream> //Para entrada e saída (std::cin, std::cout)
#include <fstream> //Para manipular arquivos (std::ifstream)
#include <vector> //Para usar vetores dinâmicos (std::vector)
#include <string> //Para manipular strings (std::string)
#include <sstream> //Para manipular strings como streams (std::stringstream)
#include <map> //É um contêiner associativo que armazena pares chave-valor ordenados (std::map)
#include <algorithm> //Ordena elementos de uma coleção em ordem crescente ou de acordo com um critério customizado(std::sort)
#include <random> //Para gerar números aleatórios
#include <locale.h> //Para imprimir as palavras com acentuação

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Permite imprimir acentos e caracteres especiais na tela

    // Caminho do arquivo que o programa vai procurar
    std::string caminho_arquivo = "C:\\Users\\nome-do-usuario\\pasta-do-arquivo\\numeros.txt";
    std::ifstream arquivo(caminho_arquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << caminho_arquivo << std::endl;
        return 1;
    }

    // Ler números do arquivo e contar as frequência de cada número
    std::map<int, int> frequencia;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        int numero;
        while (ss >> numero) {
            frequencia[numero]++;
            if (ss.peek() == ',' || ss.peek() == ' ') {
                ss.ignore();
            }
        }
    }
    arquivo.close();

    if (frequencia.size() < 60) {
        std::cerr << "Erro: É necessário pelo menos 60 números únicos no arquivo para gerar os jogos." << std::endl;
        return 1;
    }

    // Ordenar os números por frequência (decrescente)
    std::vector<std::pair<int, int>> numeros_frequentes(frequencia.begin(), frequencia.end());
    std::sort(numeros_frequentes.begin(), numeros_frequentes.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second; // Ordena pela frequência em ordem decrescente
              });

    // Selecionar os 60 números mais frequentes
    std::vector<int> numeros_selecionados;
    for (size_t i = 0; i < 60 && i < numeros_frequentes.size(); ++i) {
        numeros_selecionados.push_back(numeros_frequentes[i].first);
    }

    // Embaralhar os números selecionados
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numeros_selecionados.begin(), numeros_selecionados.end(), g);

    // Gerar 10 jogos com 6 números cada
    std::vector<std::vector<int>> jogos;
    for (int i = 0; i < 10; ++i) {
        std::vector<int> jogo;
        for (int j = 0; j < 6; ++j) {
            jogo.push_back(numeros_selecionados.back());
            numeros_selecionados.pop_back();
        }
        std::sort(jogo.begin(), jogo.end()); // Ordenar os números do jogo
        jogos.push_back(jogo);
    }

    // Exibir os jogos
    std::cout << "10 jogos gerados com os números mais frequentes:\n";
    for (size_t i = 0; i < jogos.size(); ++i) {
        std::cout << "Jogo " << i + 1 << ": ";
        for (int num : jogos[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
