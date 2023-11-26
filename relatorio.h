#if !defined(_RELATORIO_H_)
#define _RELATORIO_H_

#include <ctime>
#include <vector>
#include "candidato.h"
#include "partido.h"

class Relatorio {
private:
    tm data_eleicao;
    vector<Candidato> candidatos;
    vector<Partido> partidos;
    int numero_total_eleitos;
public:
    Relatorio(const tm &data_eleicao, const map<int, Partido> &partidos);
    
    //Relatorio 1
    const int &get_numero_total_eleitos() const;

    //Relatorio 2
    void candidatos_eleitos();

    //Relatorio 3
    void candidatos_mais_votados();

    //Relatorio 4
    void teriam_sido_eleitos();

    //Relatorio 5
    void eleitos_beneficiados_sistema_porporcional();

    //Relatorio 8
    void eleitos_por_faixa_etaria();
};




#endif // _RELATORIO_H_
