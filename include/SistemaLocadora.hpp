#ifndef SISTEMALOCADORA_HPP
#define SISTEMALOCADORA_HPP

#include <vector> 

class Agencia;
class Veiculo;

class SistemaLocadora {

    private: 

    
     std::vector<Agencia*> listaDeAgencias;

     
     Agencia* AgenciaComFaltaDeVeiculo();
     Agencia* AgenciaComSobraDeVeiculo();


    public:
  
    SistemaLocadora();

   
    virtual ~SistemaLocadora();


    bool tranferirVeiculo(Veiculo* veiculo, Agencia* origem, Agencia* destino);

  
    void otimizarFrotas();


    void AdicionarAgencia(Agencia* agencia);


    const std::vector<Agencia*>& getAgencias() const;

};

#endif