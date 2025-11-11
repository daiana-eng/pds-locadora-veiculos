#include "VeiculoLuxo.hpp"
#include "Veiculo.hpp"
#include <string>


const std::map<std::string, double> VeiculoLuxo::_tabelaDePrecos = {
    {"Ferrari",      4500.00}, 
    {"BMW",          3500.00},
    {"Porsche",      4450.00},
    {"Ranger Rover", 3200.00},
    {"Mercedes-Benz",3000.00}
};

VeiculoLuxo::VeiculoLuxo(const std::string& placa, const std::string& marca, 
    const std::string& modelo, int ano) : Veiculo(placa, marca, modelo, ano, "Luxo"){

    }

double VeiculoLuxo::getPrecoDiaria() const override{
    std::string meuModelo = this->getModelo();
    auto it = _tabelaDePrecos.find(meuModelo);

    if(it != _tabelaDePrecos.end()){
        return it -> second;
    }
    
}

