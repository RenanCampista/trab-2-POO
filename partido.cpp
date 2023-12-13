#include <iostream>
#include "partido.h"
#include "data.h"

Partido::Partido(const int &numero_partido, const string &sigla_partido) : numero_partido(numero_partido), sigla_partido(sigla_partido) {
    qtd_votos_legenda = 0;
}

const int &Partido::get_numero_partido() const {
    return numero_partido;
}

const string &Partido::get_sigla_partido() const {
    return sigla_partido;
}

const int &Partido::get_qtd_votos_legenda() const {
    return qtd_votos_legenda;
}

int Partido::get_eleitos() const {
    int eleitos = 0;
    for (const pair<int, Candidato> c : candidatos) {
        if (c.second.is_eleito()) 
            eleitos++;
    }
    return eleitos;
}

int Partido::get_votos_nominais() const {
    int votos = 0;
    for (const pair<int, Candidato> c : candidatos) {
        if (c.second.votos_legenda())
            votos += c.second.get_qtd_votos_nominal();
    }
    return votos;
}

int Partido::get_total_votos() const {
    return qtd_votos_legenda + get_votos_nominais();
}

const Candidato &Partido::get_candidato_mais_votado() const {
    int maior = 0;
    int mais_votado = -1;

    for (const auto& candidato : candidatos) {
        const Candidato& c = candidato.second;

        if ((mais_votado == -1|| c.get_qtd_votos_nominal() > maior) && (c.get_cod_situacao_candidato() == 2 || c.get_cod_situacao_candidato() == 16)) {
            maior = c.get_qtd_votos_nominal();
            mais_votado = candidato.first;  // Usamos candidato.first para obter a chave do mapa
        } else if (c.get_qtd_votos_nominal() == maior && Data::DataComparator()(c.get_data_nascimento(), candidatos.at(mais_votado).get_data_nascimento()) > 0 && (c.get_cod_situacao_candidato() == 2 || c.get_cod_situacao_candidato() == 16)) {
            maior = c.get_qtd_votos_nominal();
            mais_votado = candidato.first;
        }
    }
    return candidatos.at(mais_votado);
}

const Candidato &Partido::get_candidato_menos_votado() const {
    int menor = 0;
    int menos_votado = -1;

    for(const auto& candidato : candidatos) {
        const Candidato& c = candidato.second;

        if ((menos_votado == -1 || c.get_qtd_votos_nominal() < menor) && (c.get_cod_situacao_candidato() == 2 || c.get_cod_situacao_candidato() == 16)) {
            menor = c.get_qtd_votos_nominal();
            menos_votado = candidato.first;
        } else if (c.get_qtd_votos_nominal() == menor && Data::DataComparator()(c.get_data_nascimento(), candidatos.at(menos_votado).get_data_nascimento()) > 0 && (c.get_cod_situacao_candidato() == 2 || c.get_cod_situacao_candidato() == 16)) {
            menor = c.get_qtd_votos_nominal();
            menos_votado = candidato.first;
        }
    }

    return candidatos.at(menos_votado);
}

void Partido::add_candidato(const Candidato &candidato) {
    candidatos.insert(pair<int, Candidato>(candidato.get_numero_candidato(), candidato));
}

bool Partido::contem_candidato(const int &numero_candidato) const {
    return candidatos.find(numero_candidato) != candidatos.end();
}

bool Partido::ha_candidato_cadastrado() const {
    return !candidatos.empty();
}

void Partido::adicionar_voto_candidato(const int &numero_votavel, const int &qtd_votos) {
    if(candidatos.at(numero_votavel).get_tipo_destinacao_votos() == "Válido (legenda)")
        this->qtd_votos_legenda += qtd_votos;
    else
        candidatos.at(numero_votavel).adicionar_voto(qtd_votos);
    
}   

void Partido::adicionar_voto_legenda(const int &qtd_votos){
    this->qtd_votos_legenda += qtd_votos;
}

const map<int, Candidato> &Partido::get_candidatos() const {
    return this->candidatos;
}
