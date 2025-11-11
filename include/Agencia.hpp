// Nome do Arquivo: include/Agencia.hpp

#ifndef AGENCIA_H
#define AGENCIA_H

#include <string>
#include <vector>

class Veiculo; // Forward declaration

class Agencia {

private:
    std::string _nome;
    std::string _endereco;
    std::vector<Veiculo*> _frotaLocal;

public:
    Agencia(const std::string& nome, const std::string& endereco);
    ~Agencia();

    std::string getnome() const;
    std::string getEndereço() const;

    const std::vector<Veiculo*>& getFrota() const;

    //função para add um carro na lista
    void adicionarVeiculo(Veiculo* veiculo);

    /**
     * @brief Remove um veículo da frota local (pela placa) e retorna o ponteiro.
     * Não deleta o veículo.
     * @param placa A placa do veículo a ser removido.
     * @return O ponteiro para o Veiculo removido, ou nullptr se não encontrado.
     */
    Veiculo* removerVeiculo(const std::string& placa); 
};

#endif // AGENCIA_H