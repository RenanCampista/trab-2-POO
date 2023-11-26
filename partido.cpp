#include <iostream>
#include "partido.h"

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

const int &Partido::get_eleitos() const {
    int eleitos = 0;
    for (const pair<int, Candidato> c : candidatos) {
        if (c.second.is_eleito()) eleitos++;
    }
    return eleitos;
}

const int &Partido::get_votos_nominais() const {
    int votos = 0;
    for (const pair<int, Candidato> c : candidatos) {
        if (c.second.votos_legenda())
            votos += c.second.get_qtd_votos_nominal();
    }
    return votos;
}

const int &Partido::get_total_votos() const {
    return qtd_votos_legenda + get_votos_nominais();
}

// const Candidato &Partido::get_candidato_mais_votado() const {
//     const Candidato *mais_votado = nullptr;
//     for (const pair<int, Candidato> c : candidatos) {
//         if (mais_votado == nullptr || c.second.get_qtd_votos_nominal() > mais_votado->get_qtd_votos_nominal())
//             mais_votado = &c.second;
//         else if (c.second.get_qtd_votos_nominal() == mais_votado->get_qtd_votos_nominal() && mais_votado->get_data_nascimento() > c.second.get_data_nascimento())
//             mais_votado = &c.second;
//     }
//     return *mais_votado;
// }

// const Candidato &Partido::get_candidato_menos_votado() const {
//     const Candidato *menos_votado = nullptr;
//     for (const pair<int, Candidato> c : candidatos) {
//         if ((menos_votado == nullptr || c.second.get_qtd_votos_nominal() < menos_votado->get_qtd_votos_nominal()) && (c.second.get_cod_situacao_candidato() == 2 || c.second.get_cod_situacao_candidato() == 16))
//             menos_votado = &c.second;
//         else if(c.second.get_qtd_votos_nominal() == menos_votado->get_qtd_votos_nominal() && menos_votado->get_data_nascimento() < c.second.get_data_nascimento() && (c.second.get_cod_situacao_candidato() == 2 || c.second.get_cod_situacao_candidato() == 16))
//             menos_votado = &c.second;
//     }
//     return *menos_votado;
// }

void Partido::add_candidato(const Candidato &candidato) {
    candidatos.insert(pair<int, Candidato>(candidato.get_numero_candidato(), candidato));
}

