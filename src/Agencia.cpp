#include "Agencia.hpp"
#include <string>
#include "Veiculo.hpp"
#include <iostream>


    Agencia(const std::string& nome, const std::string& endereco) : _nome(nome), _endereco(endereco){

    } 

    std::string Agencia::getnome() const{
        return this->_nome;
    }
    std::string Agencia::getEndereço() const{
        return this->_endereco;
    }

    const std::vector<Veiculo*>& Agencia::getFrota() const{
        return this->_frotaLocal;
    }

    //função para add um carro na lista

    void Agencia::adicionarVeiculo(Veiculo* veiculo){
        this->_frotaLocal.push_back(veiculo);
    }

    //função parar tirar um carro da lista

    void Agencia::removerVeiculo(Veiculo* veiculo){
        for(auto it = this->_frotaLocal.begin(); it != _frotaLocal.end(); ++it){
            if(*it == veiculo){
                this->_frotaLocal.erase(it);

                delete veiculo;
                break;
            }
        }
        
    }


    Agencia::~Agencia(){
        for(Veiculo* v : this->_frotaLocal){
            delete v;
        }
    }


#endif // AGENCIA_H