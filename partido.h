#if !defined(_PARTIDO_H_)
#define _PARTIDO_H_

#include <string>
#include <map>
#include "candidato.h"
#include "data.h"


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
    
    int get_eleitos() const;
    int get_votos_nominais() const;
    int get_total_votos() const;
    const Candidato &get_candidato_mais_votado() const;
    const Candidato &get_candidato_menos_votado() const;
    void add_candidato(const Candidato &candidato);
    
    bool contem_candidato(const int &numero_candidato) const;
    bool ha_candidato_cadastrado() const;
    void adicionar_voto_candidato(const int &numero_votavel, const int &qtd_votos);
    void adicionar_voto_legenda(const int &qtd_votos);
    const map<int, Candidato> &get_candidatos() const;
    friend std::ostream& operator<<(std::ostream& os, const Partido& partido) {
        os << partido.sigla_partido << " - " << partido.numero_partido;
        return os;
    }
    class VotoPartidoComparator {
        public:
            bool operator()(const Partido& p1, const Partido& p2) const {
                int totalVotosP1 = p1.get_total_votos();
                int totalVotosP2 = p2.get_total_votos();
                if (totalVotosP1 > totalVotosP2){
                    return true;
                }else if (totalVotosP1 == totalVotosP2){ 
                    return p1.get_numero_partido() < p2.get_numero_partido() ? true : false;
                }else{ 
                    return false;
                }
            }
    };

    class MaisVotadoPartidoComparator {
        public:
            bool operator()(const Partido& p1, const Partido& p2) const {
                const Candidato c1 = p1.get_candidato_mais_votado();
                const Candidato c2 = p2.get_candidato_mais_votado();
                std::cerr << c1.get_nome_urna() << std::endl;
                std::cerr << c2.get_nome_urna() << std::endl;

                if (&c1 == nullptr && &c2 == nullptr) {
                    return false; // No comparison possible, consider them equal
                } else if (&c1 == nullptr) {
                    return false; // c2 is greater as c1 is considered minimal
                } else if (&c2 == nullptr) {
                    return true; // c1 is greater as c2 is considered minimal
                }

                int votosP1 = c1.get_qtd_votos_nominal();
                int votosP2 = c2.get_qtd_votos_nominal();

                if (votosP1 > votosP2) {
                    return true;
                } else if (votosP1 == votosP2) {
                    return p1.get_numero_partido() < p2.get_numero_partido();
                } else {
                    return false;
                }  
            }
    };
};

#endif // _PARTIDO_H_
