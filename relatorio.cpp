#include <iostream>
#include "relatorio.h"

using namespace std;

Relatorio::Relatorio(const tm &data_eleicao, const map<int, Partido> &partidos) : data_eleicao(data_eleicao) {
    for (const pair<int, Partido> p : partidos) {
        this->numero_total_eleitos = p.second.get_eleitos();
        this->candidatos.push_back(p.second.get_candidato_mais_votado());
        for (const pair<int, Candidato> c : p.second.get_candidatos()) {
            this->candidatos.push_back(c.second);
        }
    }
    //Collections.sort(candidatosList, new VotoNominalComparator());
}

//Relatorio 1
const int &Relatorio::get_numero_total_eleitos() const {
    return numero_total_eleitos;
}