#ifndef AGENCIA_H
#define AGENCIA_H

#include<string>
#include<vector>

class Veiculo;

class Agencia{

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

    void removerVeiculo(*Veiculo* veiculo);


};

#endif // AGENCIA_H