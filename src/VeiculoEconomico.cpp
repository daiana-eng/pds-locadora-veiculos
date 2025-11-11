#include "VeiculoEconomico.hpp"
#include "Veiculo.hpp"
#include <iostream>
#include <string>

const std::map<std::string, double> VeiculoEconomico::_tabelaDePrecos = {
    {"Mobi", 600.00}, 
    {"Kwid", 550.00},
    {"Uno",  450.00},
    {"HB20", 700.00},
    {"Onix", 650.00}
};

VeiculoEconomico::VeiculoEconomico(const std::string& placa, const std::string& marca, 
    const std::string& modelo, int ano) : Veiculo(placa, marca, modelo, ano, "Economico"){

    }

double VeiculoEconomico::getPrecoDiaria() const override{
    std::string meuModelo = this->getModelo();
    auto it = _tabelaDePrecos.find(meuModelo);

    if(it != _tabelaDePrecos.end()){
        return it -> second;
    }
    
}
 
