#include "SistemaLocadora.hpp"
#include "Agencia.hpp"
#include "Veiculo.hpp"
#include <iostream>

// construtor

SistemaLocadora::SistemaLocadora(){

    std::cout << "Sistema Locadora iniciado!" << std::endl;

}

//destrutor

SistemaLocadora::~SistemaLocadora(){
    for(Agencia* agencia : listaDeAgencias){
        delete agencia;
    }
    listaDeAgencias.clear();
}
// add aagência ao sistema

void SistemaLocadora::AdicionarAgencia(Agencia* agencia){
    if(agencia != nullptr){
        listaDeAgencias.push_back(agencia);
        std::cout << "Agencia" << agencia->getNome() << "adicionando ao sistema!" << std::endl;
    }
}

// obter lista de agência

const std::vector<Agencia*>& SistemaLocadora::getAgencias() const {
    return listaDeAgencias;
}

// transferir veículo ente agência

bool SistemaLocadora::transferirVeiculo(Veiculo* veiculo, Agencia* origem, Agencia* destino){


    if(veiculo == nullptr || origem == nullptr || destino == nullptr){
        std::cout << "Erro: dados invalidos para transferencia!" << std::endl;
        return false;
    }

    // verifica se o veículo está disponível para transferência
    if(veiculo->getStatus()!= StatusVeiculo::DISPONIVEL){
        std::cout << "Erro: Veiculo " << veiculo-> getPlaca()
        << "nao esta disponivel para transferencia!" << std::endl;
        return false;
    }

    //remove de agencia de origem

    origem->removerVeiculo(veiculo);

    // adiciona na agência de destino

    destino->adicionarVeiculo(veiculo);

    std::cout << "Veiculo " << veiculo->getPlaca()
              << " tranferencia de" << origem->getnome()
              << " para " << destino->getnome() << std::endl;


return true;

}

// encontra agência com falta de veículos e retorna a agência com menos veículos

Agencia* SistemaLocadora::AgenciaComFaltaDeVeiculo(){
    if(listaDeAgencias.empty()){
        return nullptr;
    }

    //assume que a primeira é a com menos veículos

    Agencia* AgenciaComMenosVeiculos = listaDeAgencias[0];
    size_t menorQuantidade = AgenciaComMenosVeiculos->getFrota().size();

    // compara com as demais

    for(Agencia* agencia : listaDeAgencias){
        size_t quantidade = agencia->getFrota().size();

        if(quantidade < menorQuantidade){
            menorQuantidade = quantidade;
            AgenciaComMenosVeiculos = agencia;
        }
    }

    return AgenciaComMenosVeiculos;
}

// encontra agência com sobra de veículos

Agencia* SistemaLocadora::AgenciaComSobraDeVeiculo(){
    if(listaDeAgencias.empty()){
        return nullptr;
    }

    Agencia* AgenciaComMaisVeiculos = listaDeAgencias[0];
    size_t maiorQuantidade = AgenciaComMaisVeiculos->getFrota().size();

    for(Agencia* agencia : listaDeAgencias){
        size_t quantidade = agencia->getFrota().size();

        if(quantidade > maiorQuantidade){
            maiorQuantidade = quantidade;
            AgenciaComMaisVeiculos = agencia;
        }
    }

    return AgenciaComMaisVeiculos;
}

// otimizar frotas, trasnfere veículos da agência com mais para a com menos

void SistemaLocadora::otimizarFrotas(){

    std::cout << "\n=== INICIANDO OTIMIZACAO DE FROTAS ===" <<std::endl;

    Agencia* agenciaComSobra = AgenciaComSobraDeVeiculo();
    Agencia* agenciaComFalta = AgenciaComFaltaDeVeiculo();

    if(agenciaComSobra == nullptr || agenciaComFalta == nullptr) {
        std::cout << "Nao ha agencias suficientes para otimização." << std::endl;
        return;
}

    if(agenciaComSobra == agenciaComFalta){
        std::cout << "Todas as agencias estao balanceadas!" << std::endl;
        return;
    }

size_t qtdSobra = agenciaComSobra->getFrota().size();
size_t qtdFalta = agenciaComFalta->getFrota().size();

// calcula quantos veículos transferir
// transfere até equilibbrar 

int diferenca = qtdSobra - qtdFalta;
int quantidadeTransferir = (diferenca > 2) ? diferenca / 2 : 1;

std::cout << "Agencia com sobra: " << agenciaComSobra->getnome() 
              << " (" << qtdSobra << " veiculos)" << std::endl;
std::cout << "Agencia com falta: " << agenciaComFalta->getnome() 
              << " (" << qtdFalta << " veiculos)" << std::endl;
std::cout << "Transferindo " << quantidadeTransferir << " veiculo(s)..." << std::endl;
 

// Realiza as transferências
    int transferidos = 0;
    for (Veiculo* veiculo : agenciaComSobra->getFrota()) {
        if (transferidos >= quantidadeTransferir) {
            break; // Já transferiu o suficiente
        }

        if (veiculo->getStatus() == StatusVeiculo::DISPONIVEL) {
            if (tranferirVeiculo(veiculo, agenciaComSobra, agenciaComFalta)) {
                transferidos++;
            }
        }
    }

    std::cout << "Otimizacao concluida! " << transferidos << " veiculo(s) transferido(s)." << std::endl;
}