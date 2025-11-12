// Nome do Arquivo: src/Contrato.cpp

#include "ContratoAluguel.hpp"
#include "Agencia.hpp"
#include "Veiculo.hpp"
#include "Cliente.hpp"
#include <iostream>

// --- Includes adicionados para cálculo de datas ---
#include <sstream> // Para std::stringstream
#include <iomanip> // Para std::get_time
#include <chrono>  // Para cálculos de tempo
#include <cmath>   // Para std::ceil (arredondar dias para cima)

/**
 * @brief Função auxiliar para converter string de data (ex: "dd/mm/aaaa")
 * para um time_point do chrono.
 */
static std::chrono::system_clock::time_point parseData(const std::string &dataStr)
{
    std::tm tm = {};
    std::stringstream ss(dataStr);
    // Assume o formato DD/MM/YYYY
    ss >> std::get_time(&tm, "%d/%m/%Y");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

/**
 * @brief Função auxiliar para calcular a diferença de dias entre duas datas.
 * A locadora cobra por diária, então qualquer fração de dia conta como 1 dia.
 */
static int calcularDiasAluguel(const std::string &dataInicio, const std::string &dataFim)
{
    if (dataInicio.empty() || dataFim.empty())
    {
        return 0; // Evita erro se as datas estiverem vazias
    }

    auto inicio_tp = parseData(dataInicio);
    auto fim_tp = parseData(dataFim);

    // Calcula a duração em horas
    auto duracao_horas = std::chrono::duration_cast<std::chrono::hours>(fim_tp - inicio_tp);

    // Converte horas para dias, arredondando PARA CIMA (ex: 25h = 2 dias)
    double dias_fracionados = duracao_horas.count() / 24.0;
    int dias_alugados = static_cast<int>(std::ceil(dias_fracionados));

    // Garante o aluguel mínimo de 1 diária
    if (dias_alugados <= 0)
    {
        dias_alugados = 1;
    }

    return dias_alugados;
}

// Construtor CORRIGIDO (para bater com ContratoAluguel.hpp)
ContratoDeAluguel::ContratoDeAluguel(int id, Cliente *cliente, Veiculo *veiculo,
                                     Agencia *agenciaretirada, std::string &dataRetirada,
                                     int diarias_previstas, // Este parâmetro estava faltando
                                     std::string &dataPrevisao) :

                                                                  _id(id),
                                                                  _cliente(cliente),
                                                                  _veiculo(veiculo),
                                                                  _agenciaRetirada(agenciaretirada),
                                                                  _agenciaDevolução(nullptr),
                                                                  _dataRetirada(dataRetirada),
                                                                  _dataPrevisao(dataPrevisao),
                                                                  _dataDevolucao(""),
                                                                  _status(StatusContrato::ATIVO),
                                                                  _valorDoContrato(0.0)

{
    if (_veiculo != nullptr)
    {
        _veiculo->setStatus(StatusVeiculo::ALUGADO);
    }
}

void ContratoDeAluguel::finalizar(const std::string &dataDevolucao, Agencia *agenciaDevolucao)
{
    this->_dataDevolucao = dataDevolucao;
    _agenciaDevolução = agenciaDevolucao;
    _status = StatusContrato::FINALIZADO;

    // Calcula o valor final no momento da finalização
    calcularValorContrato();
}

int ContratoDeAluguel::getId() const
{
    return _id;
}

StatusContrato ContratoDeAluguel::getStatus() const
{
    return _status;
}

Cliente *ContratoDeAluguel::getCliente() const
{
    return _cliente;
}

Veiculo *ContratoDeAluguel::getVeiculo() const
{
    return _veiculo;
}

// Função de cálculo MODIFICADA
void ContratoDeAluguel::calcularValorContrato()
{
    if (_veiculo == nullptr)
        return; // Segurança

    double diaria = _veiculo->getPrecoDiaria();

    // 1. Calcula os dias reais que o cliente ficou com o carro
    int dias_alugados = calcularDiasAluguel(_dataRetirada, _dataDevolucao);

    // 2. Calcula os dias previstos no contrato
    int dias_previstos = calcularDiasAluguel(_dataRetirada, _dataPrevisao);

    double valor_multa = 0.0;

    // 3. Verifica se houve atraso e calcula a multa
    if (dias_alugados > dias_previstos)
    {
        int dias_excedentes = dias_alugados - dias_previstos;

        // Lógica de multa: 10% da diária por dia excedente (exemplo)
        valor_multa = dias_excedentes * (diaria * 0.10);
    }

    // 4. Define o valor total do contrato
    _valorDoContrato = (diaria * dias_alugados) + valor_multa;

    // 5. Libera o veículo
    _veiculo->setStatus(StatusVeiculo::DISPONIVEL);
}

// O '}' extra que existia aqui no arquivo original foi removido.