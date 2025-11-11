#include "Agencia.hpp"
#include "Veiculo.hpp" // Necessário incluir
#include <string>
#include <iostream>

// CORREÇÃO: Sintaxe do construtor corrigida
Agencia::Agencia(const std::string& nome, const std::string& endereco) 
    : _nome(nome), _endereco(endereco) {
    // Corpo do construtor (vazio, neste caso)
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

//função para add um carro na lista
void Agencia::adicionarVeiculo(Veiculo* veiculo) {
    this->_frotaLocal.push_back(veiculo);
}

//função parar tirar um carro da lista
void Agencia::removerVeiculo(Veiculo* veiculo) {
    for(auto it = this->_frotaLocal.begin(); it != _frotaLocal.end(); ++it) {
        if(*it == veiculo) {
            this->_frotaLocal.erase(it);
            // delete veiculo; // Cuidado: A agência não deve deletar o veículo
            // A responsabilidade de deletar pode ser de outra classe (ex: Locadora)
            break;
        }
    }
}

Agencia::~Agencia() {
    // Se a Agência for "dona" dos veículos, ela deve deletá-los.
    // Se não for, esta implementação está errada e deve ser revista.
    // Por enquanto, vou manter como estava no seu código original:
    for(Veiculo* v : this->_frotaLocal) {
        delete v;
    }
}

// CORREÇÃO: Removido o #endif AGENCIA_H extra