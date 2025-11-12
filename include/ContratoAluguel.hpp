#ifndef CONTRATOALUGUEL_H
#define CONTRATOALUGUEL_H

#include <string>
#include <iostream>

enum class StatusContrato
{
    ATIVO,
    FINALIZADO
};

class Cliente;
class Veiculo;
class Agencia;

class ContratoDeAluguel
{
private:
    int _id;
    Cliente *_cliente;
    Veiculo *_veiculo;
    // maybe_unused: Agencia *_agenciaRetirada;
    Agencia *_agenciaDevolucao;

    std::string _dataRetirada;
    std::string _dataPrevisao;
    std::string _dataDevolucao;

    StatusContrato _status;

    double _valorDoContrato;

public:
    ContratoDeAluguel(int id, Cliente *cliente, Veiculo *veiculo,
                      Agencia *agenciaRetirada, std::string &dataRetirada,
                      int _diarias_previstas, std::string &dataPrevisao);

    void finalizar(const std::string &_dataDevolucao, Agencia *agenciaDevolucao);

    int getId() const;
    StatusContrato getStatus() const;
    Cliente *getCliente() const;
    Veiculo *getVeiculo() const;

private:
    void calcularValorContrato();
};

#endif // CONTRATO_H
