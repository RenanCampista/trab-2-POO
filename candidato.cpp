#include <iostream>
#include "candidato.h"

Candidato::Candidato(const int &cod_situacao_candidato, const int &numero_candidato, const string &nome_urna, const int &num_partido, 
                            const string &sigla_partido, const int &num_federacao, const tm &data_nascimento, const int &status_candidatura, 
                                                             const int &cod_genero, const string &tipo_destinacao_votos, const int &qtd_votos_nominal) : 
                                                             cod_situacao_candidato(cod_situacao_candidato), numero_candidato(numero_candidato), nome_urna(nome_urna), num_partido(num_partido), 
                                                            sigla_partido(sigla_partido), num_federacao(num_federacao), data_nascimento(data_nascimento), /*status_candidatura(status_candidatura),*/ 
                                                             /*cod_genero(cod_genero),*/ tipo_destinacao_votos(tipo_destinacao_votos), qtd_votos_nominal(qtd_votos_nominal) {   
    if (status_candidatura == 2 || status_candidatura == 3)
        this->status_candidatura = ELEITO;
    else 
        this->status_candidatura = NAO_ELEITO;
    
    if (cod_genero == 2) 
        this->cod_genero = MASCULINO;
    else if (cod_genero == 4) 
        this->cod_genero = FEMININO; 
}

const int &Candidato::get_cod_situacao_candidato() const {
    return cod_situacao_candidato;
}

const int &Candidato::get_numero_candidato() const {
    return numero_candidato;
}

const string &Candidato::get_nome_urna() const {
    return nome_urna;
}

const int &Candidato::get_num_partido() const {
    return num_partido;
}

const string &Candidato::get_sigla_partido() const {
    return sigla_partido;
}

const int &Candidato::get_num_federacao() const {
    return num_federacao;
}

const tm &Candidato::get_data_nascimento() const {
    return data_nascimento;
}

const SituacaoCandidato &Candidato::get_status_candidatura() const {
    return status_candidatura;
}

const Genero &Candidato::get_cod_genero() const {
    return cod_genero;
}

const string &Candidato::get_tipo_destinacao_votos() const {
    return tipo_destinacao_votos;
}

const int &Candidato::get_qtd_votos_nominal() const {
    return qtd_votos_nominal;
}