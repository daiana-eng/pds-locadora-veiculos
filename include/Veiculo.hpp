#ifndef VEICULO_H
#define VEICULO_H

#include<string>


enum class StatusVeiculo {
    DISPONIVEL,
    ALUGADO,
    EM_MANUTENCAO
};

class Veiculo {
    private:

    std::string _placa;
    std::string _marca;
    std::string _modelo;
    int _ano;
    int _km;
    StatusVeiculo status;
    std::string _categoria;

    public:

    Veiculo(const std::string& placa, const std::string& marca, 
    const std::string& modelo, int ano, const std::string& categoria);
    
    virtual ~Veiculo() = default;


    std::string getPlaca() const;
    std::string getMarca() const;
    std::string getModelo() const;
    int getAno() const;
    std:: string getCategoria() const;
    StatusVeiculo getStatus() const;

    void setStatus(StatusVeiculo novostatus);

    virtual double getPrecoDiaria() const = 0;

};


#endif // VEICULO_H
