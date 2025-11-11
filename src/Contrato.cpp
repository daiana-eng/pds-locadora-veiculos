#include "Contrato.hpp"
#include "Agencia.hpp"
#include "Veiculo.hpp"
#include "Cliente.hpp"
#include <iostream>

ContratoDeAluguel::Contrato(int id, Cliente* cliente, Veiculo* veiculo,
                   Agencia* agenciaretirada, std::string& dataRetirada,
                   std::string& dataPrevisao) :

_id(id),
_cliente(cliente),
_veiculo(veiculo),
_agenciaRetirada(agenciaRetirada),
_agenciaDevolução(nullptr),
_dataRetirada(dataRetirada),
_dataPrevisao(dataPrevisao),
_dataDevolucao(""),
_status(StatusContrato::ATIVO),
_valorDoContrato(0.0)

{
if (_veiculo != nullptr) { 
        _veiculo->setStatus(StatusVeiculo::ALUGADO); 
    }
}


void ContratoDeAluguel::finalizar(const std::string& dataDevolucao, Agencia* agenciaDevolucao){
    this->_dataDevolucao = dataDevolucao;
    _agenciaDevolução = agenciaDevolucao;
    _status = StatusContrato::FINALIZADO;
    calcularValorContrato();
}

int ContratoDeAluguel::getId() const {
    return _id;
}

StatusContrato ContratoDeAluguel::getStatus() const{
    return _status;
}

Cliente* ContratoDeAluguel::getCliente() const{
    return _cliente;
}

Veiculo* ContratoDeAluguel::getVeiculo() const{
    return _veiculo;
}

void ContratoDeAluguel::calcularValorContrato(){
    double diaria = _veiculo->getPrecoDiaria();


int dias_alugados = 5;

_valorDoContrato = diaria * dias_alugados;

_veiculo->setStatus(StatusVeiculo::DISPONIVEL);

}