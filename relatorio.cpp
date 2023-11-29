#include <iostream>
#include "relatorio.h"

using namespace std;

Relatorio::Relatorio(const tm &data_eleicao, const map<int, Partido> &partidos) : data_eleicao(data_eleicao) {
    for (const pair<int, Partido> p : partidos) {
        this->numero_total_eleitos = p.second.get_eleitos();
        this->candidatos_vector.push_back(p.second.get_candidato_mais_votado());
        for (const pair<int, Candidato> c : p.second.get_candidatos()) {
            this->candidatos_vector.push_back(c.second);
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
    for (const Candidato &c : this->candidatos_vector) {
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
        if (!this->candidatos_vector[i].is_eleito()) {
            cout << i + 1 << " - " << endl;
            //faltar imprimir os dados do candidato do vector ordenado
        }
    }
}

//Relatorio 5
void Relatorio::eleitos_beneficiados_sistema_porporcional() {
    for (int i = this->numero_total_eleitos; i < this->candidatos_vector.size(); i++) {
        cout << i + 1 << " - " << endl;
        //faltar imprimir os dados do candidato do vector ordenado
    }
}

//Relatorio 8
void Relatorio::eleitos_por_faixa_etaria() {
    int idade, eleitos = this->numero_total_eleitos;
    int cont_menor_30 = 0, cont_30_40 = 0, cont_40_50 = 0, cont_50_60 = 0, cont_maior_60 = 0;

}

//Relatorio 9
void Relatorio::eleitos_por_genero() {
    int cont_masculino = 0, cont_feminino = 0;

    for (const Candidato &c : this->candidatos_vector) {
        if (c.get_cod_genero() == Genero::MASCULINO && c.is_eleito()) cont_masculino++;
        else if (c.get_cod_genero() == Genero::FEMININO && c.is_eleito()) cont_feminino++;
    }
    /*
                System.out.println("Feminino: " + eleitosFemininos + " (" + (eleitosFemininos + eleitosMasculinos == 0 ? "0" : 
                                                    df.format((double) eleitosFemininos / (eleitosFemininos + eleitosMasculinos) * 100)) + "%)");
        System.out.println("Masculino: " + eleitosMasculinos + " (" + (eleitosFemininos + eleitosMasculinos == 0 ? "0" : 
                                                    df.format((double) eleitosMasculinos / (eleitosFemininos + eleitosMasculinos) * 100)) + "%)\n");
    
    */
}

//Relatorio 10
void Relatorio::total_votos_validos() {
    int votos_validos = 0;
    int votos_legenda = 0;
    int votos_nominais = 0;

    for (const Partido &p: this->partidos_vetor) {
        votos_legenda += p.get_qtd_votos_legenda();
        votos_nominais += p.get_votos_nominais();
    }
    votos_validos = votos_legenda + votos_nominais;
    // System.out.println("Total de votos válidos: " + nf.format(votosValidos));
    // System.out.println("Total de votos nominais: " + nf.format(votosNominais) + " (" + (votosValidos == 0 ? "0" : df.format((double) votosNominais / votosValidos * 100)) + "%)");
    // System.out.println("Total de votos de legenda: " + nf.format(votosLegenda) + " (" + (votosValidos == 0 ? "0" : df.format((double) votosLegenda / votosValidos * 100)) + "%)");
}