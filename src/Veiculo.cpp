#include "Veiculo.hpp"
#include <iostream>

Veiculo::Veiculo(const::string& placa, const std::string& marca, 
const std::string& modelo, int ano, const std::string& categoria):
_placa(placa), _marca(placa), _modelo(modelo), _ano(ano), km(0), _categoria(categoria)

{
    status = StatusVeiculo::DISPONIVEL;
}


void Veiculo::setStatus(StatusVeiculo novostatus){
   this->status = novostatus;
}

std::string Veiculo::getPlaca() const {
    return _placa;
}

std::string Veiculo::getMarca() const {
    return _marca;
}

std::string Veiculo::getModelo() const {
    return _modelo;
}

int Veiculo::getAno() const{
    return _ano;
}

std::string Veiculo::getCategoria() const{
    return _categoria;
}

StatusVeiculo Veiculo::getStatus() const {
    return status;
}

