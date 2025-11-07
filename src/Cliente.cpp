#include "Cliente.hpp"
#include "Veiculo.hpp"
#include "ContratoAluguel.hpp"


 Cliente::Cliente(const std::string& nome, int cpf, const std::string& cnh, 
              int idade, const std::string& endereco, int telefone) : nome(nome), cnh(cnh),
                idade(idade), cpf(cpf),endereco(endereco),telefone(telefone),

                status(StatusCliente::PENDENTE),
                veiculoAlugado(nullptr),
                contratoAtual(nullptr)      
{


  }

int Cliente::getIdade() const {
    return idade;
}

int Cliente::getCpf() const{
    return cpf;
}

std::string Cliente::getEndereco() const{
    return endereco;
}

 int Cliente::getTelefone() const{
    return telefone;
 }

void Cliente::setEndereco(const std::string& novoEndereco){
    this->endereco =novoEndereco;
}
void Cliente::setTelefone(int novoTelefone){
    this->telefone = novoTelefone;
}
void Cliente::setIdade(int novaIdade){
    this->idade = novaIdade;

}

void Cliente::associarVeiculoAlugado(Veiculo* veiculo){
    this->veiculoAlugado = veiculo;
}
void Cliente::desassociarVeiculoAlugado(){
    this->veiculoAlugado = nullptr;
}

Veiculo* Cliente::getVeiculoAlugado() const{
    return veiculoAlugado;
}

void Cliente::setStatus(StatusCliente status){
    this->status = status;
}
StatusCliente Cliente::getStatus() const{
    return status;
}

void Cliente::associarContrato(ContratoDeAlugel* contrato){
    this->contratoAtual = contrato;
}
ContratoDeAlugel* Cliente::getContrato() const{
    return contrato;
}


Cliente::~Cliente();