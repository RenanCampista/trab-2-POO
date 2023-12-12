#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include "entrada.h"

string iso_8859_1_to_utf8(string &str)
{
  // adaptado de: https://stackoverflow.com/a/39884120 :-)
  string str_out;
  for (string::iterator it = str.begin(); it != str.end(); ++it)
  {
    uint8_t ch = *it;
    if (ch < 0x80)
    {
      // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
      str_out.push_back(ch);
    }
    else
    {
      // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
      // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
      str_out.push_back(0b11000000 | (ch >> 6));
      // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
      str_out.push_back(0b10000000 | (ch & 0b00111111));
    }
  }
  return str_out;
}


Entrada::Entrada() {}

void Entrada::read_votacao(string &path, string &arg, map<int, Partido> &partidos){

  ifstream file(path, ios::in);
  if (!file.is_open()) {
      cerr << "Erro ao abrir o arquivo: " << path << endl;
      return;
  }

  string line;
  getline(file, line); // Ignora a primeira linha

  int cod_cargo = 0, num_votavel = 0, qtd_votos = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string field;
        for (int i = 0; i <= QT_VOTOS; ++i) {
            getline(iss, field, ';');
            field.erase(remove(field.begin(), field.end(), '\"'), field.end());
            switch (static_cast<EntradaVotacao>(i)) {
                case CD_CARGO:
                try {
                    cod_cargo = stoi(field);
                } catch (const invalid_argument& e) {
                    cerr << "Erro ao converter o valor de CD_CARGO para inteiro: " << e.what() << endl;
                }
                break;
                case NR_VOTAVEL:
                try {
                    num_votavel = stoi(field);
                } catch (const invalid_argument& e) {
                    cerr << "Erro ao converter o valor de NR_VOTAVEL para inteiro: " << e.what() << endl;
                }
                break;
                case QT_VOTOS:
                try {
                    qtd_votos = stoi(field);
                } catch (const invalid_argument& e) {
                    cerr << "Erro ao converter o valor de QT_VOTOS para inteiro: " << e.what() << endl;
                }
                break;
            }
        }

        if ((arg == "estadual" && cod_cargo == 7) || (arg == "federal" && cod_cargo == 6)) {
            if (num_votavel < 95 || num_votavel > 98) {
                for (auto& p : partidos) {
                    if (p.second.contem_candidato(num_votavel))
                        p.second.adicionar_voto_candidato(num_votavel, qtd_votos);
                    else if (num_votavel == p.second.get_numero_partido())
                        p.second.adicionar_voto_legenda(qtd_votos);
                }
            }
        }
    }

  file.close();
  cout << "Leitura da votação realizada com sucesso." << endl;
}

map<int, Partido> &Entrada::read_candidatos(const string &path, const string &opcao){
try {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << path << endl;
        return partidos;
    }

    string line;
    getline(file, line); // Ignora a primeira linha
    getline(file, line);

    while (!file.eof()) {
        istringstream ss(line);
        vector<string> fields;

        while (ss) {
            string field;
            if (!getline(ss, field, ';')) break;
            fields.push_back(field);
        }

        int cod_cargo = 0, cod_situacao_candidato = 0, num_candidato = 0, num_partido = 0, num_federacao = 0, status_candidatura = 0, cod_genero = 0;
        string nomeUrna, siglaPartido, tipoDestinacaoVotos;
        tm dataNascimento = {};//erro
        try {
            cod_cargo = stoi(fields[CD_CARGO_CANDIDATO].substr(1, fields[CD_CARGO_CANDIDATO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_CARGO_CANDIDATO para inteiro: " << e.what() << endl;
        }

        try {
            cod_situacao_candidato = stoi(fields[CD_SITUACAO_CANDIDATO_TOT].substr(1, fields[CD_SITUACAO_CANDIDATO_TOT].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_SITUACAO_CANDIDATO_TOT para inteiro: " << e.what() << endl;
        }

        try {
            num_candidato = stoi(fields[NR_CANDIDATO].substr(1, fields[NR_CANDIDATO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de NR_CANDIDATO para inteiro: " << e.what() << endl;
        }
        nomeUrna = fields[NM_URNA_CANDIDATO].substr(1, fields[NM_URNA_CANDIDATO].size() - 2);
        nomeUrna = iso_8859_1_to_utf8(nomeUrna);

        try {
            num_partido = stoi(fields[NR_PARTIDO].substr(1, fields[NR_PARTIDO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de NR_PARTIDO para inteiro: " << e.what() << endl;
        }

        siglaPartido = fields[SG_PARTIDO].substr(1, fields[SG_PARTIDO].size() - 2);
        siglaPartido = iso_8859_1_to_utf8(siglaPartido);
     
        try {
            num_federacao = stoi(fields[NR_FEDERACAO].substr(1, fields[NR_FEDERACAO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de NR_FEDERACAO para inteiro: " << e.what() << endl;
        }
       
        if (fields[DT_NASCIMENTO].substr(1, fields[DT_NASCIMENTO].size() - 2) != "") {
            try {
                istringstream dateStream(fields[DT_NASCIMENTO].substr(1, fields[DT_NASCIMENTO].size() - 2));
                dateStream >> get_time(&dataNascimento, "%d/%m/%Y");
            } catch (exception const& e) {
                cerr << "Erro ao converter o valor de DT_NASCIMENTO para data: " << e.what() << endl;
            }
        }
        
        try {
            status_candidatura = stoi(fields[CD_SIT_TOT_TURNO].substr(1, fields[CD_SIT_TOT_TURNO].size() - 2));
            
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_SIT_TOT_TURNO para inteiro: " << e.what() << endl;
        }
        try {
            cod_genero = stoi(fields[CD_GENERO].substr(1, fields[CD_GENERO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_GENERO para inteiro: " << e.what() << endl;
        }   
        tipoDestinacaoVotos = fields[NM_TIPO_DESTINACAO_VOTOS].substr(1, fields[NM_TIPO_DESTINACAO_VOTOS].size() - 2);
        tipoDestinacaoVotos = iso_8859_1_to_utf8(tipoDestinacaoVotos);
        Data data_tratada = Data(dataNascimento.tm_mday,dataNascimento.tm_mon + 1, dataNascimento.tm_year + 1900);
        Candidato candidato(cod_situacao_candidato, num_candidato, nomeUrna, num_partido, siglaPartido, num_federacao, data_tratada, status_candidatura, cod_genero, tipoDestinacaoVotos, 0);
        
        if (partidos.find(num_partido) != partidos.end()) {
            if ((opcao == "estadual" && cod_cargo == 7) || (opcao == "federal" && cod_cargo == 6)) {
                if ((candidato.get_cod_situacao_candidato() == 2 || candidato.get_cod_situacao_candidato() == 16) || tipoDestinacaoVotos == "Válido (legenda)")
                    partidos.at(num_partido).add_candidato(candidato);
            }
        } else {
            Partido partido(num_partido, siglaPartido);
            if ((opcao == "estadual" && cod_cargo == 7) || (opcao == "federal" && cod_cargo == 6)) {
                if ((candidato.get_cod_situacao_candidato() == 2 || candidato.get_cod_situacao_candidato() == 16) || tipoDestinacaoVotos == "Válido (legenda)")
                    partido.add_candidato(candidato);
            }
            partidos.insert({num_partido, partido});
            
        }          
        getline(file, line);
    }
    file.close();
    } catch (exception const& e) {
    cerr << "Erro de E/S: " << e.what() << endl;
    }

  return partidos;
}

