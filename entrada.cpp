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
  string strOut;
  for (string::iterator it = str.begin(); it != str.end(); ++it)
  {
    uint8_t ch = *it;
    if (ch < 0x80)
    {
      // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
      strOut.push_back(ch);
    }
    else
    {
      // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
      // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
      strOut.push_back(0b11000000 | (ch >> 6));
      // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
      strOut.push_back(0b10000000 | (ch & 0b00111111));
    }
  }
  return strOut;
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

  int codCargo = 0, numVotavel = 0, qtdVotos = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string field;
        for (int i = 0; i <= QT_VOTOS; ++i) {
            getline(iss, field, ';');
            field.erase(remove(field.begin(), field.end(), '\"'), field.end());
            switch (static_cast<EntradaVotacao>(i)) {
                case CD_CARGO:
                try {
                    codCargo = stoi(field);
                    //cout << codCargo << endl;
                } catch (const invalid_argument& e) {
                    cerr << "Erro ao converter o valor de CD_CARGO para inteiro: " << e.what() << endl;
                }
                break;
                case NR_VOTAVEL:
                try {
                    numVotavel = stoi(field);
                } catch (const invalid_argument& e) {
                    cerr << "Erro ao converter o valor de NR_VOTAVEL para inteiro: " << e.what() << endl;
                }
                break;
                case QT_VOTOS:
                try {
                    qtdVotos = stoi(field);
                } catch (const invalid_argument& e) {
                    cerr << "Erro ao converter o valor de QT_VOTOS para inteiro: " << e.what() << endl;
                }
                break;
            }
        }
    //cout << "Lendo votação..." << endl;
        if ((arg == "estadual" && codCargo == 7) || (arg == "federal" && codCargo == 6)) {
            if (numVotavel < 95 || numVotavel > 98) {
                for (auto& p : partidos) {
                    if (p.second.contem_candidato(numVotavel))
                        p.second.adicionar_voto_candidato(numVotavel, qtdVotos);
                    //else if (numVotavel == p.second.get_numero_partido())
                        //p.second.adicionar_voto_legenda(qtdVotos);
                    //p.second.adicionar_voto_candidato(numVotavel, qtdVotos);

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

        int codCargo = 0, codSituacaoCandidato = 0, numCandidato = 0, numPartido = 0, numFederacao = 0, statusCandidatura = 0, codGenero = 0;
        string nomeUrna, siglaPartido, tipoDestinacaoVotos;
        tm dataNascimento = {};//erro
        try {
            codCargo = stoi(fields[CD_CARGO_CANDIDATO].substr(1, fields[CD_CARGO_CANDIDATO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_CARGO_CANDIDATO para inteiro: " << e.what() << endl;
        }

        try {
            codSituacaoCandidato = stoi(fields[CD_SITUACAO_CANDIDATO_TOT].substr(1, fields[CD_SITUACAO_CANDIDATO_TOT].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_SITUACAO_CANDIDATO_TOT para inteiro: " << e.what() << endl;
        }

        try {
            numCandidato = stoi(fields[NR_CANDIDATO].substr(1, fields[NR_CANDIDATO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de NR_CANDIDATO para inteiro: " << e.what() << endl;
        }
        nomeUrna = fields[NM_URNA_CANDIDATO].substr(1, fields[NM_URNA_CANDIDATO].size() - 2);
        nomeUrna = iso_8859_1_to_utf8(nomeUrna);

        try {
            numPartido = stoi(fields[NR_PARTIDO].substr(1, fields[NR_PARTIDO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de NR_PARTIDO para inteiro: " << e.what() << endl;
        }//erro

        siglaPartido = fields[SG_PARTIDO].substr(1, fields[SG_PARTIDO].size() - 2);
        siglaPartido = iso_8859_1_to_utf8(siglaPartido);
        //erro
        try {
            numFederacao = stoi(fields[NR_FEDERACAO].substr(1, fields[NR_FEDERACAO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de NR_FEDERACAO para inteiro: " << e.what() << endl;
        }
        //erro
        if (fields[DT_NASCIMENTO].substr(1, fields[DT_NASCIMENTO].size() - 2) != "") {
            try {
                istringstream dateStream(fields[DT_NASCIMENTO].substr(1, fields[DT_NASCIMENTO].size() - 2));
                dateStream >> get_time(&dataNascimento, "%d/%m/%Y");
            } catch (exception const& e) {
                cerr << "Erro ao converter o valor de DT_NASCIMENTO para data: " << e.what() << endl;
            }
        }
        //erro
        try {
            statusCandidatura = stoi(fields[CD_SIT_TOT_TURNO].substr(1, fields[CD_SIT_TOT_TURNO].size() - 2));
            // if (statusCandidatura == 2 || statusCandidatura == 6)
            //     cout << "Candidato eleito" << endl;
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_SIT_TOT_TURNO para inteiro: " << e.what() << endl;
        }
        try {
            codGenero = stoi(fields[CD_GENERO].substr(1, fields[CD_GENERO].size() - 2));
        } catch (invalid_argument const& e) {
            cerr << "Erro ao converter o valor de CD_GENERO para inteiro: " << e.what() << endl;
        }   
        tipoDestinacaoVotos = fields[NM_TIPO_DESTINACAO_VOTOS].substr(1, fields[NM_TIPO_DESTINACAO_VOTOS].size() - 2);
        tipoDestinacaoVotos = iso_8859_1_to_utf8(tipoDestinacaoVotos);
        Data data_tratada = Data(dataNascimento.tm_mday,dataNascimento.tm_mon + 1, dataNascimento.tm_year + 1900);
        Candidato candidato(codSituacaoCandidato, numCandidato, nomeUrna, numPartido, siglaPartido, numFederacao, data_tratada, statusCandidatura, codGenero, tipoDestinacaoVotos, 0);
        
        if (partidos.find(numPartido) != partidos.end()) {
            if ((opcao == "estadual" && codCargo == 7) || (opcao == "federal" && codCargo == 6)) {
                if ((candidato.get_cod_situacao_candidato() == 2 || candidato.get_cod_situacao_candidato() == 16) || tipoDestinacaoVotos == "Válido (legenda)")
                    partidos.at(numPartido).add_candidato(candidato);
            }
        } else {
            Partido partido(numPartido, siglaPartido);
            if ((opcao == "estadual" && codCargo == 7) || (opcao == "federal" && codCargo == 6)) {
                if ((candidato.get_cod_situacao_candidato() == 2 || candidato.get_cod_situacao_candidato() == 16) || tipoDestinacaoVotos == "Válido (legenda)")
                    partido.add_candidato(candidato);
            }
            partidos.insert({numPartido, partido});
            
        }          
        getline(file, line);
    }
    file.close();
    } catch (exception const& e) {
    cerr << "Erro de E/S: " << e.what() << endl;
    }

  return partidos;
}

