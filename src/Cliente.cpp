// Nome do Arquivo: src/Cliente.cpp

#include "Cliente.hpp"
#include "Veiculo.hpp"
#include "ContratoAluguel.hpp"
#include <string>

// Construtor
Cliente::Cliente(const std::string& nome, int cpf, const std::string& cnh, 
                 int idade, const std::string& endereco, int telefone) 
    : nome(nome), 
      cnh(cnh), 
      idade(idade), 
      cpf(cpf), 
      endereco(endereco), 
      telefone(telefone),
      status(StatusCliente::ATIVO), // Define um status inicial padrão
      veiculoAlugado(nullptr),
      contratoAtual(nullptr)
{
    // O corpo do construtor pode ficar vazio
}

// Destrutor
Cliente::~Cliente() {
    // A classe Cliente não é "dona" (não aloca dinamicamente) 
    // do Veiculo ou Contrato, então o destrutor não precisa deletá-los.
}

// --- Getters ---

std::string Cliente::getNome() const {
    return nome;
}

std::string Cliente::getCnh() const {
    return cnh;
}

int Cliente::getIdade() const {
    return idade;
}

int Cliente::getCpf() const {
    return cpf;
}

std::string Cliente::getEndereco() const {
    return endereco;
}

int Cliente::getTelefone() const {
    return telefone;
}

StatusCliente Cliente::getStatus() const {
    return status;
}

Veiculo* Cliente::getVeiculoAlugado() const {
    return veiculoAlugado;
}

ContratoDeAluguel* Cliente::getContrato() const {
    return contratoAtual;
}

// --- Setters ---

void Cliente::setEndereco(const std::string& novoEndereco) {
    this->endereco = novoEndereco;
}

void Cliente::setTelefone(int novoTelefone) {
    this->telefone = novoTelefone;
}

void Cliente::setIdade(int novaIdade) {
    this->idade = novaIdade;
}

void Cliente::setStatus(StatusCliente novoStatus) {
    this->status = novoStatus;
}

// --- Métodos de Associação ---

void Cliente::associarVeiculoAlugado(Veiculo* veiculo) {
    this->veiculoAlugado = veiculo;
}

void Cliente::desassociarVeiculoAlugado() {
    this->veiculoAlugado = nullptr;
}

void Cliente::associarContrato(ContratoDeAluguel* contrato) {
    this->contratoAtual = contrato;
}