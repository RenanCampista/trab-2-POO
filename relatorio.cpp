#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "relatorio.h"

using namespace std;

void imprime_candidato(const Candidato& c) {
    // Imprime o candidato ao inves de retornar uma string, caso contrario os numeros nao estariam na formatacao correta
    cout << (c.tem_federacao() ? "*" : "") << c.get_nome_urna() << " (" << c.get_sigla_partido() << ", " << c.get_qtd_votos_nominal() << " votos)" << endl;
}

Relatorio::Relatorio(const Data &data_eleicao, const map<int, Partido> &partidos) : data_eleicao(data_eleicao) {
    this->numero_total_eleitos = 0;
    for (const pair<int, Partido> p : partidos) {
        this->numero_total_eleitos += p.second.get_eleitos();
        this->partidos_vetor.push_back(p.second);
        for (const pair<int, Candidato> c : p.second.get_candidatos()) {
            this->candidatos_vector.push_back(c.second);
        }
    }
    sort(this->partidos_vetor.begin(), this->partidos_vetor.end(), Partido::VotoPartidoComparator());
    sort(this->candidatos_vector.begin(), this->candidatos_vector.end(), Candidato::VotoNominalComparator());


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
            cout << i << " - ";
            imprime_candidato(c);
        }
    }
}

//Relatorio 3
void Relatorio::candidatos_mais_votados() {
    for (int i = 0; i < this->numero_total_eleitos; i++) {
        cout << i + 1 << " - "; 
        imprime_candidato(candidatos_vector[i]);
    }
}

//Relatorio 4
void Relatorio::teriam_sido_eleitos() {
    for (int i = 0; i < this->numero_total_eleitos; i++) {
        if (!this->candidatos_vector[i].is_eleito()) {
            cout << i + 1 << " - "; 
            imprime_candidato(candidatos_vector[i]);
        }
    }
}


//Relatorio 5
void Relatorio::eleitos_beneficiados_sistema_proporcional() {
    for (vector<Candidato>::size_type i = this->numero_total_eleitos; i < this->candidatos_vector.size(); i++) {
        if(this->candidatos_vector[i].is_eleito()) {
            cout << i + 1 << " - " ;
            imprime_candidato(candidatos_vector[i]);
        }
    }
}

// Relatorio 6
void Relatorio::votos_totalizados_por_partido() {
    sort(partidos_vetor.begin(), partidos_vetor.end(), Partido::VotoPartidoComparator());

    int i = 1;
    for (Partido& p : partidos_vetor) {
        cout << i << " - " << p << ", " << p.get_total_votos() << " voto"
                << (p.get_total_votos() > 1 ? "s" : "") << " (" << p.get_votos_nominais()
                << " nomina" << (p.get_votos_nominais() > 1 ? "is" : "l") << " e " << p.get_qtd_votos_legenda()
                << " de legenda), " << p.get_eleitos() << " candidato" << (p.get_eleitos() > 1 ? "s" : "")
                << " eleito" << (p.get_eleitos() > 1 ? "s" : "") << endl;
        i++;
    }
}

// Relatorio 7
void Relatorio::primeiro_ultimo_colocados_partido() {
    // Cria um vetor de referências para partidos que possuem candidatos cadastrados
    vector<reference_wrapper<Partido>> partidos_com_candidatos;
    for (Partido &p : this->partidos_vetor) {
        if (p.ha_candidato_cadastrado()) {
            partidos_com_candidatos.push_back(ref(p));
        }
    }

    // Ordena o vetor de referências
    sort(partidos_com_candidatos.begin(), partidos_com_candidatos.end(), Partido::MaisVotadoPartidoComparator());

    int i = 1;
    for (Partido& p : partidos_com_candidatos) {
        Candidato maisVotado = p.get_candidato_mais_votado();
        Candidato menosVotado = p.get_candidato_menos_votado();
        string votos = menosVotado.get_qtd_votos_nominal() < 2 ? " voto)" : " votos)";
        cout << i << " - " << p.get_sigla_partido() << " - " << to_string(p.get_numero_partido()) << ", " << maisVotado.get_nome_urna()
             << "(" << to_string(maisVotado.get_numero_candidato()) << ", " << maisVotado.get_qtd_votos_nominal()
             << " votos)" << " / " << menosVotado.get_nome_urna() << "(" << to_string(menosVotado.get_numero_candidato())
             << ", " << menosVotado.get_qtd_votos_nominal() << votos << endl;
        i++;
    }
}

//Relatorio 8
void Relatorio::eleitos_por_faixa_etaria() {
    int idade = 0, eleitos = this->numero_total_eleitos;
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

    cout << "Total de votos válidos: " << votos_validos << "\n";
    cout << "Total de votos nominais: " << votos_nominais << " (" << (votos_validos == 0 ? 0 : (double) votos_nominais / votos_validos * 100) << "%)\n";
    cout << "Total de votos de legenda: " << votos_legenda << " (" << (votos_validos == 0 ? 0 : (double) votos_legenda / votos_validos * 100) << "%)\n\n";
}
