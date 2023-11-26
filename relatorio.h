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
    const int &get_numero_total_eleitos() const;
};




#endif // _RELATORIO_H_
