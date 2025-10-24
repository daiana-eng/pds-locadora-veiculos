#ifndef CONTRATOALUGUEL_H
#define CONTRATOALUGUEL_H

#include<string>
#include<iostream>

enum class StatusContrato{
 ATIVO,
 FINALIZADO
};

class Cliente;
class Veiculo;
class Agencia;


class Contrato{
    private:

    int _id;
    Cliente* _cliente;
    Veiculo* _veiculo;
    Agencia* _agenciaRetirada;
    Agencia* _agenciaDevolução;

    std::string _dataRetirada;
    std::string _dataPrevisao;
    std::string _dataDevolucao;

    StatusContrato _status;

    double _valorDoContrato;

    public:

    Contrato(int id, Cliente* cliente, Veiculo* veiculo,
    Agencia* agenciaRetirada, std::string& dataRetirada,
     std::string& dataPrevisao);

     void finalizar(const std::string& _dataDevolucao, Agencia* agenciaDevolucao);
    
     int getId() const;
     StatusContrato getStatus() const;
     Cliente* getCliente() const;
     Veiculo* getVeiculo() const;

     private:

     void calcularValorContrato();

};


#endif // CONTRATO_H
