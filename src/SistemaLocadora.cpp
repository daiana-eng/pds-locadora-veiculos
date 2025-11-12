// Nome do Arquivo: src/SistemaLocadora.cpp

#include "SistemaLocadora.hpp"
#include "Agencia.hpp"
#include "Cliente.hpp"
#include "Veiculo.hpp"
#include "VeiculoEconomico.hpp"
#include "VeiculoLuxo.hpp"
#include "ContratoAluguel.hpp"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

SistemaLocadora::SistemaLocadora() : _proximoContratoId(1)
{
    carregarDados();
}

SistemaLocadora::~SistemaLocadora()
{
    salvarDados();

    // Limpa a memória, já que o sistema é dono dos ponteiros
    for (auto &par : _agencias)
    {
        delete par.second;
    }
    for (auto &par : _clientes)
    {
        delete par.second;
    }
    for (Veiculo *v : _frotaGeral)
    {
        delete v;
    }
    for (ContratoDeAluguel *c : _contratos)
    {
        delete c;
    }
}

// --- Persistência ---

void SistemaLocadora::salvarDados()
{
    try
    {
        salvarAgencias();
        salvarClientes();
        salvarVeiculos();
        std::cout << "Dados salvos com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao salvar dados: " << e.what() << std::endl;
    }
}

void SistemaLocadora::carregarDados()
{
    try
    {
        carregarAgencias();
        carregarClientes();
        carregarVeiculos();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Aviso ao carregar dados: " << e.what() << std::endl;
    }
}

void SistemaLocadora::salvarAgencias()
{
    std::ofstream arquivo("data/agencia.csv");
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Nao foi possivel abrir data/agencia.csv para escrita");
    }

    arquivo << "nome,endereco\n";
    for (const auto &par : _agencias)
    {
        arquivo << par.second->getnome() << ","
                << par.second->getEndereço() << "\n";
    }
    arquivo.close();
}

void SistemaLocadora::salvarClientes()
{
    std::ofstream arquivo("data/clientes.csv");
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Nao foi possivel abrir data/clientes.csv para escrita");
    }

    arquivo << "nome,cpf,cnh,idade,endereco,telefone\n";
    for (const auto &par : _clientes)
    {
        Cliente *c = par.second;
        arquivo << c->getNome() << ","
                << c->getCpf() << ","
                << c->getCnh() << ","
                << c->getIdade() << ","
                << c->getEndereco() << ","
                << c->getTelefone() << "\n";
    }
    arquivo.close();
}

void SistemaLocadora::salvarVeiculos()
{
    std::ofstream arquivo("data/veiculo.csv");
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Nao foi possivel abrir data/veiculo.csv para escrita");
    }

    arquivo << "placa,marca,modelo,ano,categoria,agencia\n";
    for (const auto &parAgencia : _agencias)
    {
        Agencia *agencia = parAgencia.second;
        for (Veiculo *v : agencia->getFrota())
        {
            arquivo << v->getPlaca() << ","
                    << v->getMarca() << ","
                    << v->getModelo() << ","
                    << v->getAno() << ","
                    << v->getCategoria() << ","
                    << agencia->getnome() << "\n";
        }
    }
    arquivo.close();
}

void SistemaLocadora::carregarAgencias()
{
    std::ifstream arquivo("data/agencia.csv");
    if (!arquivo.is_open())
    {
        return; // Arquivo não existe ainda, não é erro
    }

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha))
    {
        if (linha.empty())
            continue;

        std::stringstream ss(linha);
        std::string nome, endereco;

        std::getline(ss, nome, ',');
        std::getline(ss, endereco, ',');

        cadastrarAgencia(nome, endereco);
    }
    arquivo.close();
}

void SistemaLocadora::carregarClientes()
{
    std::ifstream arquivo("data/clientes.csv");
    if (!arquivo.is_open())
    {
        return;
    }

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha))
    {
        if (linha.empty())
            continue;

        std::stringstream ss(linha);
        std::string nome, cnh, endereco;
        int cpf, idade, telefone;

        std::getline(ss, nome, ',');
        ss >> cpf;
        ss.ignore();
        std::getline(ss, cnh, ',');
        ss >> idade;
        ss.ignore();
        std::getline(ss, endereco, ',');
        ss >> telefone;

        cadastrarCliente(nome, cpf, cnh, idade, endereco, telefone);
    }
    arquivo.close();
}

void SistemaLocadora::carregarVeiculos()
{
    std::ifstream arquivo("data/veiculo.csv");
    if (!arquivo.is_open())
    {
        return;
    }

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha))
    {
        if (linha.empty())
            continue;

        std::stringstream ss(linha);
        std::string placa, marca, modelo, categoria, nomeAgencia;
        int ano;

        std::getline(ss, placa, ',');
        std::getline(ss, marca, ',');
        std::getline(ss, modelo, ',');
        ss >> ano;
        ss.ignore();
        std::getline(ss, categoria, ',');
        std::getline(ss, nomeAgencia, ',');

        Veiculo *veiculo = nullptr;
        if (categoria == "Economico")
        {
            veiculo = new VeiculoEconomico(placa, marca, modelo, ano, categoria);
        }
        else if (categoria == "Luxo")
        {
            veiculo = new VeiculoLuxo(placa, marca, modelo, ano);
        }

        if (veiculo)
        {
            cadastrarVeiculo(veiculo, nomeAgencia);
        }
    }
    arquivo.close();
}

// --- Gestão (Gerente) ---

void SistemaLocadora::cadastrarAgencia(const std::string &nome, const std::string &endereco)
{
    if (_agencias.find(nome) == _agencias.end())
    {
        _agencias[nome] = new Agencia(nome, endereco);
    }
}

Agencia *SistemaLocadora::getAgencia(const std::string &nome)
{
    auto it = _agencias.find(nome);
    if (it != _agencias.end())
    {
        return it->second;
    }
    return nullptr;
}

const std::map<std::string, Agencia *> &SistemaLocadora::getAgencias() const
{
    return _agencias;
}

void SistemaLocadora::cadastrarVeiculo(Veiculo *veiculo, const std::string &nomeAgencia)
{
    Agencia *agencia = getAgencia(nomeAgencia);
    if (agencia)
    {
        _frotaGeral.push_back(veiculo);
        agencia->adicionarVeiculo(veiculo);
    }
    else
    {
        delete veiculo;
        throw std::runtime_error("Agencia nao encontrada para cadastrar veiculo.");
    }
}

// --- Gestão (Atendente) ---

void SistemaLocadora::cadastrarCliente(const std::string &nome, int cpf, const std::string &cnh,
                                       int idade, const std::string &endereco, int telefone)
{
    if (_clientes.find(cpf) == _clientes.end())
    {
        _clientes[cpf] = new Cliente(nome, cpf, cnh, idade, endereco, telefone);
    }
}

Cliente *SistemaLocadora::getCliente(int cpf)
{
    auto it = _clientes.find(cpf);
    if (it != _clientes.end())
    {
        return it->second;
    }
    return nullptr;
}

// --- Operações de Aluguel (Atendente) ---

std::vector<Veiculo *> SistemaLocadora::consultarVeiculosDisponiveis(const std::string &nomeAgencia)
{
    Agencia *agencia = getAgencia(nomeAgencia);
    if (!agencia)
    {
        throw std::runtime_error("Agencia nao encontrada.");
    }

    std::vector<Veiculo *> disponiveis;
    for (Veiculo *v : agencia->getFrota())
    {
        if (v->getStatus() == StatusVeiculo::DISPONIVEL)
        {
            disponiveis.push_back(v);
        }
    }
    return disponiveis;
}

ContratoDeAluguel *SistemaLocadora::criarContrato(
    int cpfCliente, const std::string &placaVeiculo,
    const std::string &nomeAgenciaRetirada, int diariasPrevistas,
    const std::string &dataPrevisao, const std::string &dataRetirada)
{
    Cliente *cliente = getCliente(cpfCliente);
    if (!cliente)
        throw std::runtime_error("Cliente nao encontrado.");

    if (cliente->getStatus() != StatusCliente::ATIVO)
    {
        throw std::runtime_error("Cliente com pendencias.");
    }

    Veiculo *veiculo = getVeiculoPorPlaca(placaVeiculo);
    if (!veiculo)
        throw std::runtime_error("Veiculo nao encontrado.");

    if (veiculo->getStatus() != StatusVeiculo::DISPONIVEL)
    {
        throw std::runtime_error("Veiculo indisponivel.");
    }

    Agencia *agencia = getAgencia(nomeAgenciaRetirada);
    if (!agencia)
        throw std::runtime_error("Agencia nao encontrada.");

    std::string dtRetirada = dataRetirada;
    std::string dtPrevisao = dataPrevisao;

    ContratoDeAluguel *contrato = new ContratoDeAluguel(
        _proximoContratoId++, cliente, veiculo, agencia,
        dtRetirada, diariasPrevistas, dtPrevisao);

    _contratos.push_back(contrato);
    cliente->associarContrato(contrato);
    cliente->associarVeiculoAlugado(veiculo);

    return contrato;
}

void SistemaLocadora::finalizarContrato(int idContrato,
                                        const std::string &nomeAgenciaDevolucao, const std::string &dataDevolucao)
{
    ContratoDeAluguel *contrato = nullptr;
    for (ContratoDeAluguel *c : _contratos)
    {
        if (c->getId() == idContrato)
        {
            contrato = c;
            break;
        }
    }

    if (!contrato)
        throw std::runtime_error("Contrato nao encontrado.");
    if (contrato->getStatus() == StatusContrato::FINALIZADO)
    {
        throw std::runtime_error("Contrato ja finalizado.");
    }

    Agencia *agencia = getAgencia(nomeAgenciaDevolucao);
    if (!agencia)
        throw std::runtime_error("Agencia de devolucao nao encontrada.");

    Cliente *cliente = contrato->getCliente();

    contrato->finalizar(dataDevolucao, agencia);

    cliente->desassociarVeiculoAlugado();
    cliente->associarContrato(nullptr);
}

// --- Otimização (Gerente) ---

bool SistemaLocadora::transferirVeiculo(const std::string &placa,
                                        const std::string &nomeAgenciaOrigem, const std::string &nomeAgenciaDestino)
{
    Agencia *origem = getAgencia(nomeAgenciaOrigem);
    Agencia *destino = getAgencia(nomeAgenciaDestino);

    if (!origem || !destino)
    {
        std::cerr << "Erro: Agencia de origem ou destino nao encontrada." << std::endl;
        return false;
    }

    Veiculo *veiculo = origem->removerVeiculo(placa);

    if (veiculo)
    {
        destino->adicionarVeiculo(veiculo);
        std::cout << "Veiculo " << placa << " transferido de "
                  << nomeAgenciaOrigem << " para " << nomeAgenciaDestino << std::endl;
        return true;
    }

    std::cerr << "Erro: Veiculo " << placa << " nao encontrado na agencia "
              << nomeAgenciaOrigem << "." << std::endl;
    return false;
}

void SistemaLocadora::executarOtimizacaoFrota(int limiteMin, int limiteMax)
{
    std::cout << "\n--- Iniciando Otimizacao de Frota ---" << std::endl;
    std::cout << "Limites: Min=" << limiteMin << ", Max=" << limiteMax << std::endl;

    std::list<Agencia *> agenciasComSobra;
    std::list<Agencia *> agenciasComFalta;

    for (auto const &[nome, agencia] : _agencias)
    {
        int disponiveis = 0;
        for (Veiculo *v : agencia->getFrota())
        {
            if (v->getStatus() == StatusVeiculo::DISPONIVEL)
            {
                disponiveis++;
            }
        }

        if (disponiveis > limiteMax)
        {
            agenciasComSobra.push_back(agencia);
        }
        else if (disponiveis < limiteMin)
        {
            agenciasComFalta.push_back(agencia);
        }
    }

    while (!agenciasComSobra.empty() && !agenciasComFalta.empty())
    {
        Agencia *origem = agenciasComSobra.front();
        Agencia *destino = agenciasComFalta.front();

        int disponiveisOrigem = consultarVeiculosDisponiveis(origem->getnome()).size();
        int disponiveisDestino = consultarVeiculosDisponiveis(destino->getnome()).size();

        int veiculosParaEnviar = disponiveisOrigem - limiteMax;
        int veiculosParaReceber = limiteMin - disponiveisDestino;

        int transferir = std::min(veiculosParaEnviar, veiculosParaReceber);
        if (transferir <= 0)
            break;

        std::cout << "\nAgencia " << origem->getnome() << " (sobra) -> "
                  << destino->getnome() << " (falta)" << std::endl;
        std::cout << "Transferindo " << transferir << " veiculo(s)..." << std::endl;

        std::vector<Veiculo *> frotaOrigem = consultarVeiculosDisponiveis(origem->getnome());
        int transferidos = 0;
        for (Veiculo *v : frotaOrigem)
        {
            if (transferidos >= transferir)
                break;

            if (transferirVeiculo(v->getPlaca(), origem->getnome(), destino->getnome()))
            {
                transferidos++;
            }
        }

        if (consultarVeiculosDisponiveis(origem->getnome()).size() <= static_cast<size_t>(limiteMax))
        {
            agenciasComSobra.pop_front();
        }
        if (consultarVeiculosDisponiveis(destino->getnome()).size() >= static_cast<size_t>(limiteMin))
        {
            agenciasComFalta.pop_front();
        }
    }

    std::cout << "--- Otimizacao Concluida ---" << std::endl;
}

Veiculo *SistemaLocadora::getVeiculoPorPlaca(const std::string &placa)
{
    for (Veiculo *v : _frotaGeral)
    {
        if (v->getPlaca() == placa)
        {
            return v;
        }
    }
    return nullptr;
}