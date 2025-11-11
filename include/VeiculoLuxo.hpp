#ifndef VEICULOLUXO_H
#define VEICULOLUXO_H

#include "Veiculo.hpp"
#include <string>
#include <map>

class VeiculoLuxo : public Veiculo {
public:
    // Construtor
    VeiculoLuxo(const std::string& placa, const std::string& marca, 
                const std::string& modelo, int ano);

    // Sobrescrita do método virtual puro
    virtual double getPrecoDiaria() override;

private:
    // Tabela de preços estática específica para VeiculoLuxo
    static const std::map<std::string, double> _tabelaDePrecos;
};

#endif // VEICULOLUXO_H