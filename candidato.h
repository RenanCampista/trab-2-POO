#if !defined(_CANDIDATO_H_)
#define _CANDIDATO_H_

#include <string>
#include "data.h"

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
    Data data_nascimento;
    SituacaoCandidato status_candidatura;
    Genero cod_genero;
    string tipo_destinacao_votos;
    int qtd_votos_nominal;
public:
    Candidato(const int &cod_situacao_candidato, const int &numero_candidato, const string &nome_urna, const int &num_partido, 
                                const string &sigla_partido, const int &num_federacao, const Data &data_nascimento, const int &status_candidatura, 
                                                                    const int &cod_genero, const string &tipo_destinacao_votos, const int &qtd_votos_nominal);
    const int &get_cod_situacao_candidato() const;
    const int &get_numero_candidato() const;
    const string &get_nome_urna() const;
    const int &get_num_partido() const;
    const string &get_sigla_partido() const;
    const int &get_num_federacao() const;
    const Data &get_data_nascimento() const;
    const SituacaoCandidato &get_status_candidatura() const;
    const Genero &get_cod_genero() const;
    const string &get_tipo_destinacao_votos() const;
    const int &get_qtd_votos_nominal() const;
    const int &get_idade(const Data &data_atual) const;
    
    bool tem_federacao() const;
    bool votos_legenda() const;
    bool is_eleito() const;
    void adicionar_voto(const int &qtd_votos);

    friend std::ostream& operator<<(std::ostream& os, const Candidato& candidato);
    class VotoNominalComparator {
    public:
        bool operator()(const Candidato& c1, const Candidato& c2) const;
    };

};

#endif // _CANDIDATO_H_
