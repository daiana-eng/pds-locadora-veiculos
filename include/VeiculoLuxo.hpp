#ifndef VEICULOLUXO_H
#define VEICULOLUXO_H

#include "Veiculo.hpp"
#include <string>
#include <map>

class VeiculoLuxo : public Veiculo{
    public: 

    VeiculoLuxo(const std::string& placa, const std::string& marca, 
    const std::string& modelo, int ano, const std::string& categoria);

    virtual double getPrecoDiaria() const override;

    private:
    static const std::map<std::string, double> _tabelaDePrecos;
};

#endif