/**
 * @file Veiculo.hpp
 * @brief Define a classe base abstrata Veiculo
 * @author Daiana, Davi, Jamile
 * @date 2025
 */

#ifndef VEICULO_H
#define VEICULO_H

#include <string>

/**
 * @enum StatusVeiculo
 * @brief Enumeração para os possíveis status de um veículo
 */
enum class StatusVeiculo
{
    DISPONIVEL,   ///< Veículo disponível para aluguel
    ALUGADO,      ///< Veículo atualmente alugado
    EM_MANUTENCAO ///< Veículo em manutenção
};

/**
 * @class Veiculo
 * @brief Classe base abstrata que representa um veículo genérico
 *
 * Esta classe implementa o conceito de abstração da POO, definindo
 * a interface comum para todos os tipos de veículos (Econômico, Luxo, etc.).
 * Utiliza um método virtual puro para forçar as classes derivadas a
 * implementarem o cálculo do preço da diária.
 */
class Veiculo
{
protected:
    std::string _placa;     ///< Placa do veículo (identificador único)
    std::string _marca;     ///< Marca do veículo (ex: Fiat, BMW)
    std::string _modelo;    ///< Modelo do veículo (ex: Mobi, Ferrari)
    int _ano;               ///< Ano de fabricação
    std::string _categoria; ///< Categoria: "Economico", "Luxo", etc.
    StatusVeiculo _status;  ///< Status atual do veículo

public:
    /**
     * @brief Construtor da classe Veiculo
     * @param placa Placa do veículo no formato XXX-0000
     * @param marca Marca do veículo
     * @param modelo Modelo do veículo
     * @param ano Ano de fabricação
     * @param categoria Categoria do veículo
     */
    Veiculo(const std::string &placa, const std::string &marca,
            const std::string &modelo, int ano, const std::string &categoria)
        : _placa(placa), _marca(marca), _modelo(modelo), _ano(ano),
          _categoria(categoria), _status(StatusVeiculo::DISPONIVEL) {}

    /**
     * @brief Destrutor virtual para permitir polimorfismo
     *
     * Importante: destrutor virtual permite que objetos de classes
     * derivadas sejam corretamente destruídos quando apontados por
     * um ponteiro do tipo base.
     */
    virtual ~Veiculo() {}

    // --- Getters ---

    /** @brief Retorna a placa do veículo */
    std::string getPlaca() const { return _placa; }

    /** @brief Retorna a marca do veículo */
    std::string getMarca() const { return _marca; }

    /** @brief Retorna o modelo do veículo */
    std::string getModelo() const { return _modelo; }

    /** @brief Retorna o ano de fabricação */
    int getAno() const { return _ano; }

    /** @brief Retorna a categoria do veículo */
    std::string getCategoria() const { return _categoria; }

    /** @brief Retorna o status atual do veículo */
    StatusVeiculo getStatus() const { return _status; }

    // --- Setter ---

    /**
     * @brief Define um novo status para o veículo
     * @param status Novo status (DISPONIVEL, ALUGADO, EM_MANUTENCAO)
     */
    void setStatus(StatusVeiculo status) { _status = status; }

    /**
     * @brief Método virtual puro para obter o preço da diária
     * @return Preço da diária em reais (R$)
     *
     * Este método virtual puro torna a classe Veiculo abstrata.
     * Cada classe derivada (VeiculoEconomico, VeiculoLuxo) deve
     * implementar sua própria lógica de precificação.
     */
    virtual double getPrecoDiaria() = 0;
};

#endif // VEICULO_H