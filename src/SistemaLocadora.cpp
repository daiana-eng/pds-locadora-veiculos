// Nome do Arquivo: src/SistemaLocadora.cpp

#include "SistemaLocadora.hpp"
#include "Agencia.hpp"
#include "Cliente.hpp"
#include "Veiculo.hpp"
#include "ContratoAluguel.hpp"

#include <stdexcept> 
#include <iostream>  
#include <list> // Usado para a lógica de otimização

SistemaLocadora::SistemaLocadora() : _proximoContratoId(1) {
    // Construtor
}

SistemaLocadora::~SistemaLocadora() {
    // Limpa a memória, já que o sistema é dono dos ponteiros
    for (auto& par : _agencias) {
        delete par.second;
    }
    for (auto& par : _clientes) {
        delete par.second;
    }
    for (Veiculo* v : _frotaGeral) {
        delete v;
    }
    for (ContratoDeAluguel* c : _contratos) {
        delete c;
    }
}

// --- Gestão (Gerente) ---

void SistemaLocadora::cadastrarAgencia(const std::string& nome, const std::string& endereco) {
    if (_agencias.find(nome) == _agencias.end()) {
        _agencias[nome] = new Agencia(nome, endereco);
        std::cout << "Agencia " << nome << " cadastrada." << std::endl;
    }
}

Agencia* SistemaLocadora::getAgencia(const std::string& nome) {
    auto it = _agencias.find(nome);
    if (it != _agencias.end()) {
        return it->second;
    }
    return nullptr;
}

const std::map<std::string, Agencia*>& SistemaLocadora::getAgencias() const {
    return _agencias;
}

void SistemaLocadora::cadastrarVeiculo(Veiculo* veiculo, const std::string& nomeAgencia) {
    Agencia* agencia = getAgencia(nomeAgencia);
    if (agencia) {
        _frotaGeral.push_back(veiculo); // Adiciona ao repositório central
        agencia->adicionarVeiculo(veiculo); // Associa à agência
    } else {
        delete veiculo; // Se a agência não existe, deleta o veículo para evitar leak
        throw std::runtime_error("Agencia nao encontrada para cadastrar veiculo.");
    }
}

// --- Gestão (Atendente) ---

void SistemaLocadora::cadastrarCliente(const std::string& nome, int cpf, const std::string& cnh, 
                                     int idade, const std::string& endereco, int telefone) {
    if (_clientes.find(cpf) == _clientes.end()) {
        _clientes[cpf] = new Cliente(nome, cpf, cnh, idade, endereco, telefone);
        std::cout << "Cliente " << nome << " cadastrado." << std::endl;
    } else {
        std::cout << "CPF ja cadastrado." << std::endl;
    }
}

Cliente* SistemaLocadora::getCliente(int cpf) {
    auto it = _clientes.find(cpf);
    if (it != _clientes.end()) {
        return it->second;
    }
    return nullptr;
}

// --- Operações de Aluguel (Atendente) ---

std::vector<Veiculo*> SistemaLocadora::consultarVeiculosDisponiveis(const std::string& nomeAgencia) {
    Agencia* agencia = getAgencia(nomeAgencia);
    if (!agencia) {
        throw std::runtime_error("Agencia nao encontrada.");
    }

    std::vector<Veiculo*> disponiveis;
    for (Veiculo* v : agencia->getFrota()) {
        if (v->getStatus() == StatusVeiculo::DISPONIVEL) {
            disponiveis.push_back(v);
        }
    }
    return disponiveis;
}

ContratoDeAluguel* SistemaLocadora::criarContrato(
    int cpfCliente, const std::string& placaVeiculo, 
    const std::string& nomeAgenciaRetirada, int diariasPrevistas, 
    const std::string& dataPrevisao, const std::string& dataRetirada) 
{
    Cliente* cliente = getCliente(cpfCliente);
    if (!cliente) throw std::runtime_error("Cliente nao encontrado.");

    if (cliente->getStatus() != StatusCliente::ATIVO) {
        throw std::runtime_error("Cliente com pendencias.");
    }

    Veiculo* veiculo = getVeiculoPorPlaca(placaVeiculo);
    if (!veiculo) throw std::runtime_error("Veiculo nao encontrado.");

    if (veiculo->getStatus() != StatusVeiculo::DISPONIVEL) {
        throw std::runtime_error("Veiculo indisponivel.");
    }
    
    Agencia* agencia = getAgencia(nomeAgenciaRetirada);
    if (!agencia) throw std::runtime_error("Agencia nao encontrada.");

    // Cópia da data (pois o construtor espera referências não-const)
    std::string dtRetirada = dataRetirada;
    std::string dtPrevisao = dataPrevisao;

    ContratoDeAluguel* contrato = new ContratoDeAluguel(
        _proximoContratoId++, cliente, veiculo, agencia, 
        dtRetirada, diariasPrevistas, dtPrevisao
    );

    _contratos.push_back(contrato);
    cliente->associarContrato(contrato);
    cliente->associarVeiculoAlugado(veiculo);

    return contrato;
}

void SistemaLocadora::finalizarContrato(int idContrato, 
    const std::string& nomeAgenciaDevolucao, const std::string& dataDevolucao) 
{
    ContratoDeAluguel* contrato = nullptr;
    for (ContratoDeAluguel* c : _contratos) {
        if (c->getId() == idContrato) {
            contrato = c;
            break;
        }
    }

    if (!contrato) throw std::runtime_error("Contrato nao encontrado.");
    if (contrato->getStatus() == StatusContrato::FINALIZADO) {
        throw std::runtime_error("Contrato ja finalizado.");
    }

    Agencia* agencia = getAgencia(nomeAgenciaDevolucao);
    if (!agencia) throw std::runtime_error("Agencia de devolucao nao encontrada.");

    Cliente* cliente = contrato->getCliente();
    
    contrato->finalizar(dataDevolucao, agencia);

    cliente->desassociarVeiculoAlugado();
    cliente->associarContrato(nullptr);
}

// --- Otimização (Gerente) ---

bool SistemaLocadora::transferirVeiculo(const std::string& placa, 
    const std::string& nomeAgenciaOrigem, const std::string& nomeAgenciaDestino) 
{
    Agencia* origem = getAgencia(nomeAgenciaOrigem);
    Agencia* destino = getAgencia(nomeAgenciaDestino);

    if (!origem || !destino) {
        std::cerr << "Erro: Agencia de origem ou destino nao encontrada." << std::endl;
        return false;
    }

    Veiculo* veiculo = origem->removerVeiculo(placa);

    if (veiculo) {
        destino->adicionarVeiculo(veiculo); 
        std::cout << "Veiculo " << placa << " transferido de " 
                  << nomeAgenciaOrigem << " para " << nomeAgenciaDestino << std::endl;
        return true;
    }

    std::cerr << "Erro: Veiculo " << placa << " nao encontrado na agencia " 
              << nomeAgenciaOrigem << "." << std::endl;
    return false;
}

// LÓGICA DE OTIMIZAÇÃO (NOVA)
void SistemaLocadora::executarOtimizacaoFrota(int limiteMin, int limiteMax) {
    std::cout << "\n--- Iniciando Otimizacao de Frota ---" << std::endl;
    std::cout << "Limites: Min=" << limiteMin << ", Max=" << limiteMax << std::endl;

    std::list<Agencia*> agenciasComSobra;
    std::list<Agencia*> agenciasComFalta;

    // 1. Identificar agências com sobra ou falta
    for (auto const& [nome, agencia] : _agencias) {
        int disponiveis = 0;
        for (Veiculo* v : agencia->getFrota()) {
            if (v->getStatus() == StatusVeiculo::DISPONIVEL) {
                disponiveis++;
            }
        }

        if (disponiveis > limiteMax) {
            agenciasComSobra.push_back(agencia);
        } else if (disponiveis < limiteMin) {
            agenciasComFalta.push_back(agencia);
        }
    }

    // 2. Executar transferências
    while (!agenciasComSobra.empty() && !agenciasComFalta.empty()) {
        Agencia* origem = agenciasComSobra.front();
        Agencia* destino = agenciasComFalta.front();

        // Conta quantos disponíveis a origem e destino têm AGORA
        int disponiveisOrigem = consultarVeiculosDisponiveis(origem->getnome()).size();
        int disponiveisDestino = consultarVeiculosDisponiveis(destino->getnome()).size();

        int veiculosParaEnviar = disponiveisOrigem - limiteMax;
        int veiculosParaReceber = limiteMin - disponiveisDestino;

        int transferir = std::min(veiculosParaEnviar, veiculosParaReceber);
        if (transferir <= 0) break; // Segurança

        std::cout << "\nAgencia " << origem->getnome() << " (sobra) -> " 
                  << destino->getnome() << " (falta)" << std::endl;
        std::cout << "Transferindo " << transferir << " veiculo(s)..." << std::endl;

        // Encontra e transfere os veículos
        std::vector<Veiculo*> frotaOrigem = consultarVeiculosDisponiveis(origem->getnome());
        int transferidos = 0;
        for (Veiculo* v : frotaOrigem) {
            if (transferidos >= transferir) break;
            
            if (transferirVeiculo(v->getPlaca(), origem->getnome(), destino->getnome())) {
                transferidos++;
            }
        }

        // Re-avalia as duas agências
        if (consultarVeiculosDisponiveis(origem->getnome()).size() <= limiteMax) {
            agenciasComSobra.pop_front();
        }
        if (consultarVeiculosDisponiveis(destino->getnome()).size() >= limiteMin) {
            agenciasComFalta.pop_front();
        }
    }

    std::cout << "--- Otimizacao Concluida ---" << std::endl;
}


// --- Métodos auxiliares privados ---

Veiculo* SistemaLocadora::getVeiculoPorPlaca(const std::string& placa) {
    for (Veiculo* v : _frotaGeral) {
        if (v->getPlaca() == placa) {
            return v;
        }
    }
    return nullptr;
}