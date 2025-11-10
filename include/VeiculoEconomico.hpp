#ifndef VEICULOECONOMICO_H
#define VEICULOECONOMICO_H

#include "Veiculo.hpp"
#include <string>
#include <map>

class VeiculoEconomico : public Veiculo{
    public: 

    VeiculoEconomico(const std::string& placa, const std::string& marca, 
    const std::string& modelo, int ano, const std::string& categoria);

    virtual double getPrecoDiaria() const override;

    private:
    static const std::map<std::string, double> _tabelaDePrecos;
};

#endif










#endif