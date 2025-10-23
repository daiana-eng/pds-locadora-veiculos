#ifndef VEICULO_H
#define VEICULO_H

#include <string>

class Veiculo {

    private:
    std::string modelo;
    std::string marca;
    std::string cor;
    int ano;
    int km;
    int ID;

    public:
    RegistrarVeiculo();
    VerificaAgencia();
    TransferenciaVeiculo();
    RegistroVeiculoAlugado();
    

};

#endif