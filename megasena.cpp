#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "pt_BR.UTF-8"); //IMPRIMI OS ACENTOS E CARCTERS ESPECIAIS NA TELA
	
	//Substituua 0 caminho do arquivo de texto com os numeros que mais sairam em todos os jogos da megasena
    std::string caminho_arquivo = "C:\\Users\\nome-do-usuario\\caminho_do_arquivo\\numeros.txt";
    std::ifstream arquivo(caminho_arquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << caminho_arquivo << std::endl;
        return 1;
    }

    // Ler números do arquivo
    std::vector<int> numeros;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        int numero;
        while (ss >> numero) {
            numeros.push_back(numero);
            if (ss.peek() == ',' || ss.peek() == ' ') {
                ss.ignore();
            }
        }
    }
    arquivo.close();

    if (numeros.size() < 60) {
        std::cerr << "Erro: É necessário pelo menos 60 números para gerar os jogos." << std::endl;
        return 1;
    }

    // Embaralhar os números
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numeros.begin(), numeros.end(), g);

    // Verificar se há duplicatas nos jogos e gerar 10 jogos
    std::vector<std::vector<int>> jogos;
    for (int i = 0; i < 10; ++i) {
        std::vector<int> jogo;

        // Preencher cada jogo com 6 números únicos
        while (jogo.size() < 6 && !numeros.empty()) {
            int numero = numeros.back(); // Obter o número do final da lista
            numeros.pop_back();          // Remover o número da lista original

            // Garantir que o número não foi adicionado ao jogo atual
            if (std::find(jogo.begin(), jogo.end(), numero) == jogo.end()) {
                jogo.push_back(numero);
            }
        }

        std::sort(jogo.begin(), jogo.end()); // Ordenar os números do jogo
        jogos.push_back(jogo);
    }

    // Exibir os jogos
    std::cout << "10 jogos gerados com números aleatórios:\n";
    for (size_t i = 0; i < jogos.size(); ++i) {
        std::cout << "Jogo " << i + 1 << ": ";
        for (int num : jogos[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
