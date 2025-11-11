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

    //função parar tirar um carro da lista
    // CORREÇÃO: Removido o '*' extra antes de 'Veiculo*'
    void removerVeiculo(Veiculo* veiculo); 
};

#endif // AGENCIA_H