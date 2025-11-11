// Nome do Arquivo: src/Agencia.cpp

#include "Agencia.hpp"
#include "Veiculo.hpp"
#include <string>
#include <iostream>

Agencia::Agencia(const std::string& nome, const std::string& endereco) 
    : _nome(nome), _endereco(endereco) {
    // Corpo do construtor
} 

Agencia::~Agencia() {
    // MODIFICADO:
    // O SistemaLocadora agora é dono dos ponteiros de Veiculo.
    // A agência não deve mais deletá-los.
    // O loop de 'delete v' foi removido.
}

std::string Agencia::getnome() const {
    return this->_nome;
}

std::string Agencia::getEndereço() const {
    return this->_endereco;
}

const std::vector<Veiculo*>& Agencia::getFrota() const {
    return this->_frotaLocal;
}

void Agencia::adicionarVeiculo(Veiculo* veiculo) {
    this->_frotaLocal.push_back(veiculo);
}

// MODIFICADO: Busca por placa e retorna o ponteiro sem deletar.
Veiculo* Agencia::removerVeiculo(const std::string& placa) {
    for(auto it = this->_frotaLocal.begin(); it != _frotaLocal.end(); ++it) {
        if((*it)->getPlaca() == placa) {
            Veiculo* veiculoRemovido = *it;
            this->_frotaLocal.erase(it);
            return veiculoRemovido; // Retorna o ponteiro para transferência
        }
    }
    return nullptr; // Não encontrado
}