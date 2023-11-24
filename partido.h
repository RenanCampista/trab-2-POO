#if !defined(_PARTIDO_H_)
#define _PARTIDO_H_

#include <string>
#include <map>
#include "candidato.h"

using namespace std;

class Partido {
private:
    int numero_partido;
    string sigla_partido;
    int qtd_votos_legenda;
    map<int, Candidato> candidatos;
public:

};




#endif // _PARTIDO_H_
