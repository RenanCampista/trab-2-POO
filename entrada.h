#if !defined(_ENTRADA_H_)
#define _ENTRADA_H_

#include <map>
#include <string>
#include "partido.h"
#include "candidato.h"
#include "data.h"

using namespace std;

enum EntradaCandidato {
    CD_CARGO_CANDIDATO = 13,
    CD_SITUACAO_CANDIDATO_TOT = 68,
    NR_CANDIDATO = 16,
    NM_URNA_CANDIDATO = 18,
    NR_PARTIDO = 27,
    SG_PARTIDO = 28,
    NR_FEDERACAO = 30,
    DT_NASCIMENTO = 42,
    CD_SIT_TOT_TURNO = 56,
    CD_GENERO = 45,
    NM_TIPO_DESTINACAO_VOTOS = 67
};

enum EntradaVotacao {
    CD_CARGO = 17,
    NR_VOTAVEL = 19,
    QT_VOTOS = 21
};

class Entrada {
private:
    map<int, Partido> partidos;
public:
    Entrada();
    void read_votacao(string &path, string &arg, map<int, Partido> &partidos);
    map<int, Partido> &read_candidatos(const string &path, const string &opcao);
};


#endif // _ENTRADA_H_


