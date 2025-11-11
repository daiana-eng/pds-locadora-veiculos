#ifndef VEICULO_H
#define VEICULO_H

#include <string>

// Enum para o status do veículo, usado no Contrato.cpp
enum class StatusVeiculo {
    DISPONIVEL,
    ALUGADO,
    EM_MANUTENCAO
};

class Veiculo {
protected:
    std::string _placa;
    std::string _marca;
    std::string _modelo;
    int _ano;
    std::string _categoria; // "Economico", "Luxo", etc.
    StatusVeiculo _status;

public:
    // Construtor
    Veiculo(const std::string& placa, const std::string& marca, 
            const std::string& modelo, int ano, const std::string& categoria)
        : _placa(placa), _marca(marca), _modelo(modelo), _ano(ano), 
          _categoria(categoria), _status(StatusVeiculo::DISPONIVEL) {}

    // Destrutor virtual para permitir polimorfismo
    virtual ~Veiculo() {}

    // Getters
    std::string getPlaca() const { return _placa; }
    std::string getMarca() const { return _marca; }
    std::string getModelo() const { return _modelo; }
    int getAno() const { return _ano; }
    std::string getCategoria() const { return _categoria; }
    StatusVeiculo getStatus() const { return _status; }

    // Setter
    void setStatus(StatusVeiculo status) { _status = status; }

    // Método virtual puro (abstrato)
    // Força as classes filhas (Economico, Luxo) a implementarem este método
    virtual double getPrecoDiaria() = 0; 
};

#endif // VEICULO_H