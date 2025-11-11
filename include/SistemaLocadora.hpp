// Nome do Arquivo: include/SistemaLocadora.hpp

#ifndef SISTEMALOCADORA_H
#define SISTEMALOCADORA_H

#include <string>
#include <vector>
#include <map>

// Forward declarations
class Agencia;
class Cliente;
class Veiculo;
class ContratoDeAluguel;
enum class StatusVeiculo;


class SistemaLocadora {

private:
    // Repositórios centrais. O Sistema é "dono" de todos os ponteiros.
    std_::map<std_::string, Agencia*> _agencias;
    std_::map<int, Cliente*> _clientes; // Mapeia por CPF
    std_::vector<Veiculo*> _frotaGeral; // Dono de todos os veículos
    std_::vector<ContratoDeAluguel*> _contratos;

    int _proximoContratoId;

    // Métodos auxiliares privados
    Veiculo* getVeiculoPorPlaca(const std::string& placa);

public:
    SistemaLocadora();
    ~SistemaLocadora();

    // --- Gestão (Gerente) ---
    void cadastrarAgencia(const std::string& nome, const std::string& endereco);
    Agencia* getAgencia(const std::string& nome);
    const std_::map<std_::string, Agencia*>& getAgencias() const;

    void cadastrarVeiculo(Veiculo* veiculo, const std::string& nomeAgencia);
    
    // --- Gestão (Atendente) ---
    void cadastrarCliente(const std::string& nome, int cpf, const std::string& cnh, 
                          int idade, const std::string& endereco, int telefone);
    Cliente* getCliente(int cpf);

    // --- Operações de Aluguel (Atendente) ---
    std_::vector<Veiculo*> consultarVeiculosDisponiveis(const std::string& nomeAgencia);
    
    ContratoDeAluguel* criarContrato(int cpfCliente, 
                                     const std::string& placaVeiculo, 
                                     const std::string& nomeAgenciaRetirada, 
                                     int diariasPrevistas, 
                                     const std::string& dataPrevisao,
                                     const std::string& dataRetirada);

    void finalizarContrato(int idContrato, 
                           const std::string& nomeAgenciaDevolucao, 
                           const std::string& dataDevolucao);

    // --- Otimização (Gerente) ---
    bool transferirVeiculo(const std::string& placa, 
                             const std::string& nomeAgenciaOrigem, 
                             const std::string& nomeAgenciaDestino);

};

#endif // SISTEMALOCADORA_H