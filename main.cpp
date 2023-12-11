#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <ctime>
#include "partido.h"
#include "relatorio.h"
#include "entrada.h"

int main(int argc, char* argv[]) {
    Entrada entrada;
    map<int, Partido> partidos;
    Relatorio* relatorio = nullptr;
    string opcao = "";

    try {
        std::string str(argv[3]);
        string opcao = argv[1] + 2;
        std::cerr << "Aqui1\n" << std::endl;
        partidos = entrada.read_candidatos(argv[2], opcao);
        std::cerr << "Aqui2\n" << std::endl;
        entrada.read_votacao(str, opcao, partidos);
        std::cerr << "Aqui3\n" << std::endl;
        std::tm date = {};
        std::istringstream dateStream(argv[4]);
        dateStream >> std::get_time(&date, "%d/%m/%Y");
        std::cerr << "Aqui4\n" << std::endl;
        Data data_tratada = Data(date.tm_mday,date.tm_mon + 1, date.tm_year + 1900);
        std::cerr << "Aqui5\n" << std::endl;
        relatorio = new Relatorio(data_tratada, partidos);
        std::cerr << "Aqui6\n" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Argumentos insuficientes. Certifique-se de fornecer todos os argumentos necessários." << std::endl;
        return 1;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro ao analisar a data. Certifique-se de fornecer a data no formato correto (dd/MM/yyyy)." << std::endl;
        return 1;
    }

    try {
        std::cout << "Número de vagas: " << relatorio->get_numero_total_eleitos() << "\n";

        if (opcao == "federal")
            std::cout << "Deputados federais eleitos:" << std::endl;
        else if (opcao == "estadual")
            std::cout << "Deputados estaduais eleitos:" << std::endl;
        relatorio->candidatos_eleitos();

        std::cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;
        relatorio->candidatos_mais_votados();

        std::cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << std::endl;
        std::cout << "(com sua posição no ranking de mais votados)" << std::endl;
        relatorio->teriam_sido_eleitos();

        std::cout << "\nEleitos, que se beneficiaram do sistema proporcional:" << std::endl;
        std::cout << "(com sua posição no ranking de mais votados)" << std::endl;
        relatorio->eleitos_beneficiados_sistema_proporcional();

        std::cout << "\nVotação dos partidos e número de candidatos eleitos:" << std::endl;
        relatorio->votosTotalizadosPorPartido();

        std::cout << "\nPrimeiro e último colocados de cada partido: " << std::endl;
        relatorio->primeiroUltimoColocadosPartido();

        std::cout << "\nEleitos, por faixa etária (na data da eleição):" << std::endl;
        relatorio->eleitos_por_faixa_etaria();

        std::cout << "\nEleitos, por gênero:" << std::endl;
        relatorio->eleitos_por_genero();

        relatorio->total_votos_validos();
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro ao gerar os relatórios. Certifique-se de fornecer os arquivos corretos." << std::endl;
        delete relatorio;
        return 1;
    }

    delete relatorio;
    return 0;
}