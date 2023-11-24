#if !defined(_CANDIDATO_H_)
#define _CANDIDATO_H_

#include <string>

using namespace std;

enum Genero {MASCULINO, FEMININO};
enum SituacaoCandidato {ELEITO, NAO_ELEITO};

class Candidato {
private:
    int cod_situacao_candidato;
    int numero_candidato;
    string nome_urna;
    int num_partido;
    string sigla_partido;
    int num_federacao;
   // Date data_nascimento;
    SituacaoCandidato status_candidatura;
    Genero cod_genero;
    string tipo_destinacao_votos;
    int qtd_votos_nominal;
public:
    
    

};





#endif // _CANDIDATO_H_
