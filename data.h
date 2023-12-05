#if !defined(_DATA_H_)
#define _DATA_H_

using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;
public:
    Data(const int &dia, const int &mes, const int &ano);
    const int &get_dia() const;
    const int &get_mes() const;
    const int &get_ano() const;
    const int &get_idade(const Data &data_atual) const;
    friend std::ostream& operator<<(std::ostream& os, const Data& data);
};




#endif // _DATA_H_
