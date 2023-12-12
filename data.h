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
    int get_idade(const Data &data_atual) const;
    friend std::ostream& operator<<(std::ostream& os, const Data& data);

    class DataComparator{
        public:
            bool operator()(const Data& d1, const Data& d2) const {
                if(d1.ano != d2.ano){
                    return d1.ano < d2.ano;
                }else if(d1.mes != d2.mes){
                    return d1.mes < d2.mes;
                }else{
                    return d1.dia < d2.dia; 
                }
            }
    };
};




#endif // _DATA_H_
