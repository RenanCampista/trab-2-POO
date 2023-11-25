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

