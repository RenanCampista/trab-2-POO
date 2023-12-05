#include <iostream>
#include <iomanip>
#include "relatorio.h"

using namespace std;

Relatorio::Relatorio(const Data &data_eleicao, const map<int, Partido> &partidos) : data_eleicao(data_eleicao) {
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

    for (const Candidato &c : this->candidatos_vector) {
        idade = c.get_idade(this->data_eleicao);
        if (c.is_eleito()) {
            if (idade < 30) cont_menor_30++;
            else if (idade < 40) cont_30_40++;
            else if (idade < 50) cont_40_50++;
            else if (idade < 60) cont_50_60++;
            else cont_maior_60++;
        }
    }

    // System.out.println("      Idade < 30: " + contMenor30 + " (" + (eleitos == 0 ? "0" : df.format((double) contMenor30 / eleitos * 100)) + "%)");
    // System.out.println("30 <= Idade < 40: " + cont30a39 + " (" + (eleitos == 0 ? "0" : df.format((double) cont30a39 / eleitos * 100)) + "%)");
    // System.out.println("40 <= Idade < 50: " + cont40a49 + " (" + (eleitos == 0 ? "0" : df.format((double) cont40a49 / eleitos * 100)) + "%)");
    // System.out.println("50 <= Idade < 60: " + cont50a59 + " (" + (eleitos == 0 ? "0" : df.format((double) cont50a59 / eleitos * 100)) + "%)");
    // System.out.println("60 <= Idade\t: " + cont60 + " (" + (eleitos == 0 ? "0" : df.format((double) cont60 / eleitos * 100)) + "%)");

    cout << fixed << setprecision(2);

    cout << "      Idade < 30: " << cont_menor_30 << " (" << (eleitos == 0 ? 0 : (double) cont_menor_30 / eleitos * 100) << "%)\n";
    cout << "30 <= Idade < 40: " << cont_30_40 << " (" << (eleitos == 0 ? 0 : (double) cont_30_40 / eleitos * 100) << "%)\n";
    cout << "40 <= Idade < 50: " << cont_40_50 << " (" << (eleitos == 0 ? 0 : (double) cont_40_50 / eleitos * 100) << "%)\n";
    cout << "50 <= Idade < 60: " <<  cont_50_60 << " (" << (eleitos == 0 ? 0 : (double)  cont_50_60 / eleitos * 100) << "%)\n";
    cout << "60 <= Idade\t: " << cont_maior_60 << " (" << (eleitos == 0 ? 0 : (double) cont_maior_60 / eleitos * 100) << "%)\n";

}

//Relatorio 9
void Relatorio::eleitos_por_genero() {
    int cont_masculino = 0, cont_feminino = 0;

    for (const Candidato &c : this->candidatos_vector) {
        if (c.get_cod_genero() == Genero::MASCULINO && c.is_eleito()) cont_masculino++;
        else if (c.get_cod_genero() == Genero::FEMININO && c.is_eleito()) cont_feminino++;
    }
    
    //         System.out.println("Feminino: " + cont_feminino + " (" + (cont_feminino + cont_masculino == 0 ? "0" : 
    //                                             df.format((double) cont_feminino / (cont_feminino + cont_masculino) * 100)) + "%)");
    // System.out.println("Masculino: " + cont_masculino + " (" + (cont_feminino + cont_masculino == 0 ? "0" : 
    //                                             df.format((double)cont_masculino / (cont_feminino + cont_masculino) * 100)) + "%)\n");


    cout << fixed << setprecision(2);

    cout << "Feminino: " << cont_feminino << " (" << (cont_feminino + cont_masculino == 0 ? 0 : (double) cont_feminino / (cont_feminino + cont_masculino) * 100) << "%)\n";
    cout << "Masculino: " << cont_masculino << " (" << (cont_feminino + cont_masculino == 0 ? 0 : (double) cont_masculino / (cont_feminino + cont_masculino) * 100) << "%)\n";
    
    
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
    // System.out.println("Total de votos válidos: " + nf.format(votos_validos));
    // System.out.println("Total de votos nominais: " + nf.format(votos_nominais) + " (" + (votos_validos == 0 ? "0" : df.format((double) votos_nominais / votos_validos * 100)) + "%)");
    // System.out.println("Total de votos de legenda: " + nf.format(votos_legenda) + " (" + (votos_validos == 0 ? "0" : df.format((double) votos_legenda / votos_validos * 100)) + "%)");

    cout << fixed << setprecision(2);

    cout << "Total de votos válidos: " << votos_validos << "\n";
    cout << "Total de votos nominais: " << votos_nominais << " (" << (votos_validos == 0 ? 0 : (double) votos_nominais / votos_validos * 100) << "%)\n";
    cout << "Total de votos de legenda: " << votos_legenda << " (" << (votos_validos == 0 ? 0 : (double) votos_legenda / votos_validos * 100) << "%)\n";

}