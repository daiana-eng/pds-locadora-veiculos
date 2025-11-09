#include <iostream>
#include <vector>
#include "SistemaLocadora.hpp"
#include "Veiculo.hpp"
#include "Agencia.hpp"

SistemaLocadora::SistemaLocadora(){

}

bool tranferirVeiculo(Veiculo* veiculo, Agencia* origem, Agencia* destino);

  
void otimizarFrotas();


void AdicionarAgencia(Agencia* agencia);


const std::vector<Agencia*>& SistemaLocadora::getAgencias() const{
    return this->listaDeAgencias;
}



virtual SistemaLocadora::~SistemaLocadora(){

    for(Agencia* ag : this->listaDeAgencias){
        delete ag;
    }
}