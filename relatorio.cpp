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

//Relatorio 2
void Relatorio::candidatos_eleitos() {
    int i = 0;
    for (const Candidato &c : this->candidatos) {
        if (c.is_eleito()) {
            i++;
            cout << i << " - " << endl;
            //faltar imprimir os dados do candidato
        }
    }
}

//Relatorio 3
void Relatorio::candidatos_mais_votados() {
    for (int i = 0; i < this->numero_total_eleitos; i++) {
        cout << i + 1 << " - " << endl;
        //faltar imprimir os dados do candidato do vector ordenado
    }
}

//Relatorio 4
void Relatorio::teriam_sido_eleitos() {
    for (int i = 0; i < this->numero_total_eleitos; i++) {
        if (!this->candidatos[i].is_eleito()) {
            cout << i + 1 << " - " << endl;
            //faltar imprimir os dados do candidato do vector ordenado
        }
    }
}

//Relatorio 5
void Relatorio::eleitos_beneficiados_sistema_porporcional() {
    for (int i = this->numero_total_eleitos; i < this->candidatos.size(); i++) {
        cout << i + 1 << " - " << endl;
        //faltar imprimir os dados do candidato do vector ordenado
    }
}

//Relatorio 8
void Relatorio::eleitos_por_faixa_etaria() {
    int idade, eleitos = this->numero_total_eleitos;
    int cont_menor_30 = 0, cont_30_40 = 0, cont_40_50 = 0, cont_50_60 = 0, cont_maior_60 = 0;

}