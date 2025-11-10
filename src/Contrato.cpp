#include "Contrato.hpp"
#include "Agencia.hpp"
#include "Veiculo.hpp"
#include "Cliente.hpp"
#include <iostream>

Contrato::Contrato(int id, Cliente* cliente, Veiculo* veiculo,
                   Agencia* agenciaretirada, std::string& dataRetirada,
                   std::string& dataPrevisao) :

_id(id),
_cliente(cliente),
_veiculo(veiculo),
_agenciaRetirada(agenciaRetirada),
_agenciaDevolução(nullprt),
_dataRetirada(dataRetirada),
_dataPrevisao(dataPrevisao),
_dataDevolucao(""),
_status(StatusContrato::ATIVO),
_valorDoContrato(0.0)

{
    if(_veiculo != nullprt){
  _veiculo->setStatus(StatusVeiculo::ALUGADO)
    }
}

void Contrato::finalizar(const std::string& _dataDevolucao, Agencia* agenciaDevolucao){
    this->_dataDevolucao = dataDevolucao;
    _agenciaDevolução = agenciaDevolucao;
    _status = StatusContrato::FINALIZADO;
    calcularValorContrato();
}

int Contrato::getId() const {
    return _id;
}

StatusContrato Contrato::getStatus() const{
    return _status;
}

Cliente* Contrato::getCliente() const{
    return _cliente;
}

Veiculo* Contrato::getVeiculo() const{
    return _veiculo;
}

void Contrato::calcularValorContrato(){
    double diaria = _veiculo->getPrecoDiaria()


int dias_alugados;

_valorDoContrato = diaria * dias_alugados;

-veiculo->setStatus(StatusVeiculo::DISPONIVEL)

}