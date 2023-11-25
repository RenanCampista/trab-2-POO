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
    Partido(const int &numero_partido, const string &sigla_partido);
    const int &get_numero_partido() const;
    const string &get_sigla_partido() const;
    const int &get_qtd_votos_legenda() const;

};




#endif // _PARTIDO_H_
