#include "Agencia.hpp"
#include "Cliente.hpp"
#include "Veiculo.hpp"
#include <vector>
#include <algorithm>


 Agencia(const std::string& nome, const std::string& endereco): _nome(nome),_endereco(endereco){

 }

    std::string Agencia::getnome() const{
        return this->nome;
    }
    std::string Agencia::getEndereco() const{
        return this->endereco;
    }

    const std::vector<Veiculo*>& Agencia::getFrota() const{
        return this->_frotaLocal;

    }

    //função para add um carro na lista

    void adicionarVeiculo(Veiculo* veiculo){
        this->_frotaLocal.push_back(veiculo);
    }

    //função parar tirar um carro da lista

    void removerVeiculo(*Veiculo* veiculo){
        for(auto it = this->_frotaLocal.begin(); it != this->_frotaLocal.end(); ++it){
            if(*it = veiculo){
                this->_frotaLocal.erase(it);
                break;
            }
        }

    }