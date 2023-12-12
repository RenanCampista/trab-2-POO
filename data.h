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
    void set_data(const int &dia, const int &mes, const int &ano);
    int get_idade(const Data &data_atual) const;
    friend std::ostream& operator<<(std::ostream& os, const Data& data);

    class DataComparator{
        public:
            int operator()(const Data& d1, const Data& d2) const {
                if(d1.get_ano() > d2.get_ano())
                    return 1;
                else if(d1.get_ano() < d2.get_ano())
                    return -1;
                else if(d1.get_mes() > d2.get_mes())
                    return 1;
                else if(d1.get_mes() < d2.get_mes())
                    return -1;
                else if(d1.get_dia() > d2.get_dia())
                    return 1;
                else if(d1.get_dia() < d2.get_dia())
                    return -1;
                else
                    return 0;
            }
    };
};

#endif // _DATA_H_
