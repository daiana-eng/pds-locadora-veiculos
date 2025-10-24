#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Veiculo;
class ContratoDeAlugel;


class Cliente {

    public:
      enum class StatusCliente {
        ATIVO, 
        PENDENTE,
        COM_CONTRATO_VENCIDO,
        INATIVO
      };

    public:
      Cliente(const std::string& nome, int cpf, const std::string& cnh, 
              int idade, const std::string& endereco, int telefone);

      ~Cliente();
      
      std::string getNome() const;
      std::string getCnh() const;
      int getIdade() const;
      int getCpf() const;
      std::string getEndereco() const;
      int getTelefone() const;


      void setEndereco(const std::string& novoEndereco);
      void setTelefone(int novoTelefone);
      void setIdade(int novaIdade);

      void associarVeiculoAlugado(Veiculo* veiculo);
      void desassociarVeiculoAlugado();
      Veiculo* getVeiculoAlugado() const;

      void setStatus(StatusCliente status);
      StatusCliente getStatus() const;

      void associarContrato(ContratoDeAlugel* contrato);
      ContratoDeAlugel* getContrato() const;

      private:
      std::string nome;
      std::string cnh;
      int idade;
      int cpf;
      std::string endereco;
      int telefone;

      StatusCliente status;

      Veiculo* veiculoAlugado;

      ContratoDeAlugel* contratoAtual;




};

#endif