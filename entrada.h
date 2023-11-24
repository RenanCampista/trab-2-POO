#if !defined(_ENTRADA_H_)
#define _ENTRADA_H_

#include <map>
#include "partido.h"

using namespace std;

enum EntradaCandidato {
    CD_CARGO = 13,
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
};





#endif // _ENTRADA_H_
