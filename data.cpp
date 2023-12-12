#include <iostream>
#include "data.h"

Data::Data(const int &dia, const int &mes, const int &ano) : dia(dia), mes(mes), ano(ano) {}

const int &Data::get_dia() const {
    return dia;
}

const int &Data::get_mes() const {
    return mes;
}

const int &Data::get_ano() const {
    return ano;
}

void Data::set_dia(const int &dia) {
    this->dia = dia;
}

void Data::set_mes(const int &mes) {
    this->mes = mes;
}

void Data::set_ano(const int &ano) {
    this->ano = ano;
}

int Data::get_idade(const Data &data_atual) const {
    int idade = data_atual.ano - this->ano;
    if ((data_atual.mes < this->mes) || (data_atual.mes == this->mes && data_atual.dia < this->dia)) {
        idade--;
    }
    return idade;
}

std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << data.dia << "/" << data.mes << "/" << data.ano;
    return os;
}
