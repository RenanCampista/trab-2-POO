#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <string>
#include "partido.h"
#include "relatorio.h"
#include "entrada.h"

using namespace std;

int main(int argc, char* argv[]) {
    Entrada entrada;
    map<int, Partido> partidos;
    Relatorio* relatorio = nullptr;
    string opcao = "";

    try {
        string opcao = argv[1] + 2;
        string dir_candidatos = argv[2];
        string dir_votacao(argv[3]);
        string data_string = argv[4];

        partidos = entrada.read_candidatos(dir_candidatos, opcao);
        entrada.read_votacao(dir_votacao, opcao, partidos);

        istringstream iss(data_string);
        int dia, mes, ano;
        char barra1, barra2;
        iss >> dia >> barra1 >> mes >> barra2 >> ano;
        Data data_eleicao = Data(dia, mes, ano);

        relatorio = new Relatorio(data_eleicao, partidos);
    } catch (const out_of_range& e) {
        cerr << "Argumentos insuficientes. Certifique-se de fornecer todos os argumentos necessários." << endl;
        return 1;
    } catch (const invalid_argument& e) {
        cerr << "Erro ao analisar a data. Certifique-se de fornecer a data no formato correto (dd/MM/yyyy)." << endl;
        return 1;
    }

    try {
        cout << "Número de vagas: " << relatorio->get_numero_total_eleitos() << "\n";

        if (opcao == "federal")
            cout << "Deputados federais eleitos:" << endl;
        else if (opcao == "estadual")
            cout << "Deputados estaduais eleitos:" << endl;
        relatorio->candidatos_eleitos();

        cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
        relatorio->candidatos_mais_votados();

        cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
        cout << "(com sua posição no ranking de mais votados)" << endl;
        relatorio->teriam_sido_eleitos();

        cout << "\nEleitos, que se beneficiaram do sistema proporcional:" << endl;
        cout << "(com sua posição no ranking de mais votados)" << endl;
        relatorio->eleitos_beneficiados_sistema_proporcional();

        cout << "\nVotação dos partidos e número de candidatos eleitos:" << endl;
        relatorio->votosTotalizadosPorPartido();

        cout << "\nPrimeiro e último colocados de cada partido: " << endl;
       // relatorio->primeiroUltimoColocadosPartido();

        cout << "\nEleitos, por faixa etária (na data da eleição):" << endl;
        relatorio->eleitos_por_faixa_etaria();

        cout << "\nEleitos, por gênero:" << endl;
        relatorio->eleitos_por_genero();

        relatorio->total_votos_validos();
    } catch (const runtime_error& e) {
        cerr << "Erro ao gerar os relatórios. Certifique-se de fornecer os arquivos corretos." << endl;
        delete relatorio;
        return 1;
    }

    return 0;
}