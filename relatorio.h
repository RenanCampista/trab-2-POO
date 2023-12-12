#if !defined(_RELATORIO_H_)
#define _RELATORIO_H_

#include <vector>
#include "candidato.h"
#include "partido.h"
#include "data.h"

class Relatorio {
private:
    Data data_eleicao;
    vector<Candidato> candidatos_vector;
    vector<Partido> partidos_vetor;
    int numero_total_eleitos;
public:
    Relatorio(const Data &data_eleicao, const map<int, Partido> &partidos);
    
    //Relatorio 1
    const int &get_numero_total_eleitos() const;

    //Relatorio 2
    void candidatos_eleitos();

    //Relatorio 3
    void candidatos_mais_votados();

    //Relatorio 4
    void teriam_sido_eleitos();

    //Relatorio 5
    void eleitos_beneficiados_sistema_proporcional();

    // Relatorio 6
    void votosTotalizadosPorPartido();

    // Relatorio 7
    void primeiroUltimoColocadosPartido();

    //Relatorio 8
    void eleitos_por_faixa_etaria();

    //Relatorio 9
    void eleitos_por_genero();

    //Relatorio 10
    void total_votos_validos();
};

#endif // _RELATORIO_H_

