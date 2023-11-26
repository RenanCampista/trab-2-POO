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
    
    const int &get_eleitos() const;
    const int &get_votos_nominais() const;
    const int &get_total_votos() const;
    const Candidato &get_candidato_mais_votado() const;
    const Candidato &get_candidato_menos_votado() const;
    void add_candidato(const Candidato &candidato);
    
};




#endif // _PARTIDO_H_
