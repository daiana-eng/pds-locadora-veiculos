#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <limits> //limpeza
#include "SistemaLocadora.hpp"
#include "Agencia.hpp"
#include "Cliente.hpp"
#include "Veiculo.hpp"
#include "VeiculoEconomico.hpp"
#include "VeiculoLuxo.hpp"
#include "ContratoAluguel.hpp"


// --- Funções Auxiliares da Interface ---

void limparBufferCin() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Carrega dados iniciais para facilitar o teste
void carregarDadosIniciais(SistemaLocadora& sistema) {
    std::cout << "Carregando dados iniciais..." << std::endl;
    
    // 1. Agências
    sistema.cadastrarAgencia("Central BH", "Av. Afonso Pena, 1000");
    sistema.cadastrarAgencia("Filial Savassi", "Rua Tomé de Souza, 500");
    sistema.cadastrarAgencia("Filial Pampulha", "Av. Antonio Carlos, 6627");

    // 2. Veículos
    // (Placa, Marca, Modelo, Ano, Categoria/Luxo)
    
    // 5 na Central
    sistema.cadastrarVeiculo(new VeiculoEconomico("ABC-1111", "Fiat", "Mobi", 2020, "Economico"), "Central BH");
    sistema.cadastrarVeiculo(new VeiculoEconomico("ABC-2222", "Fiat", "Uno", 2021, "Economico"), "Central BH");
    sistema.cadastrarVeiculo(new VeiculoEconomico("ABC-3333", "Renault", "Kwid", 2022, "Economico"), "Central BH");
    sistema.cadastrarVeiculo(new VeiculoLuxo("LUX-1000", "BMW", "BMW", 2023), "Central BH");
    sistema.cadastrarVeiculo(new VeiculoLuxo("LUX-2000", "Mercedes-Benz", "Mercedes-Benz", 2024), "Central BH");

    // 1 na Savassi (para teste de otimização)
    sistema.cadastrarVeiculo(new VeiculoEconomico("SAV-1111", "Hyundai", "HB20", 2022, "Economico"), "Filial Savassi");

    // 3. Clientes
    // (Nome, CPF, CNH, Idade, Endereco, Telefone)
    sistema.cadastrarCliente("Davi Aredes", 123456, "111111", 30, "Rua A, 1", 99991111);
    sistema.cadastrarCliente("Daiana Rodrigues", 654321, "222222", 25, "Rua B, 2", 99992222);

    std::cout << "Carga inicial concluida!\n" << std::endl;
}

void exibirMenuAtendente(SistemaLocadora& sistema);
void exibirMenuGerente(SistemaLocadora& sistema);

// --- Funções do Menu Gerente ---

void gerente_cadastrar_agencia(SistemaLocadora& sistema) {
    std::string nome, endereco;
    std::cout << "\n== Cadastrar Nova Agencia ==\n";
    std::cout << "Nome da Agencia: ";
    limparBufferCin();
    std::getline(std::cin, nome);
    std::cout << "Endereco: ";
    std::getline(std::cin, endereco);
    
    sistema.cadastrarAgencia(nome, endereco);
}

void gerente_cadastrar_veiculo(SistemaLocadora& sistema) {
    std::string placa, marca, modelo, categoria, nomeAgencia;
    int ano, tipo;

    std::cout << "\n== Cadastrar Novo Veiculo ==\n";
    std::cout << "Agencia (Nome exato): ";
    limparBufferCin();
    std::getline(std::cin, nomeAgencia);
    
    if (sistema.getAgencia(nomeAgencia) == nullptr) {
        std::cout << "ERRO: Agencia '" << nomeAgencia << "' nao existe!" << std::endl;
        return;
    }

    std::cout << "Placa (XXX-0000): ";
    std::getline(std::cin, placa);
    std::cout << "Marca: ";
    std::getline(std::cin, marca);
    std::cout << "Modelo (Ex: Mobi, Uno, Ferrari): ";
    std::getline(std::cin, modelo);
    std::cout << "Ano: ";
    std::cin >> ano;
    std::cout << "Tipo (1: Economico, 2: Luxo): ";
    std::cin >> tipo;

    Veiculo* novoVeiculo = nullptr;
    if (tipo == 1) {
        categoria = "Economico";
        novoVeiculo = new VeiculoEconomico(placa, marca, modelo, ano, categoria);
    } else if (tipo == 2) {
        categoria = "Luxo";
        novoVeiculo = new VeiculoLuxo(placa, marca, modelo, ano);
    } else {
        std::cout << "Tipo invalido." << std::endl;
        return;
    }

    sistema.cadastrarVeiculo(novoVeiculo, nomeAgencia);
    std::cout << "Veiculo " << placa << " cadastrado em " << nomeAgencia << std::endl;
}

void gerente_listar_agencias_e_frotas(SistemaLocadora& sistema) {
    std::cout << "\n== Frotas de Todas Agencias ==\n";
    auto agencias = sistema.getAgencias();
    if (agencias.empty()) {
        std::cout << "Nenhuma agencia cadastrada." << std::endl;
        return;
    }

    for (auto const& [nome, agencia] : agencias) {
        std::cout << "\n--- Agencia: " << agencia->getnome() << " (" << agencia->getEndereço() << ") ---" << std::endl;
        const auto& frota = agencia->getFrota();
        if (frota.empty()) {
            std::cout << "  (Frota vazia)" << std::endl;
            continue;
        }
        for (Veiculo* v : frota) {
            std::cout << "  - [" << v->getPlaca() << "] " << v->getModelo()
                      << " (Status: " 
                      << (v->getStatus() == StatusVeiculo::DISPONIVEL ? "Disponivel" : "Alugado") 
                      << ")" << std::endl;
        }
    }
}

void gerente_transferir_veiculo(SistemaLocadora& sistema) {
    std::string placa, agOrigem, agDestino;
    std::cout << "\n== Transferencia Manual ==\n";
    std::cout << "Placa do Veiculo: ";
    limparBufferCin();
    std::getline(std::cin, placa);
    std::cout << "Nome da Agencia de Origem: ";
    std::getline(std::cin, agOrigem);
    std::cout << "Nome da Agencia de Destino: ";
    std::getline(std::cin, agDestino);

    try {
        if (sistema.transferirVeiculo(placa, agOrigem, agDestino)) {
            std::cout << "Transferencia concluida." << std::endl;
        } else {
            std::cout << "Falha na transferencia." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void gerente_otimizar_frota(SistemaLocadora& sistema) {
    int min, max;
    std::cout << "\n== Otimizacao Automatica ==\n";
    std::cout << "Manter no minimo quantos veiculos disponiveis? ";
    std::cin >> min;
    std::cout << "Manter no maximo quantos veiculos disponiveis? ";
    std::cin >> max;
    
    if (min >= max) {
        std::cout << "ERRO: Minimo deve ser menor que o maximo." << std::endl;
        return;
    }
    
    sistema.executarOtimizacaoFrota(min, max);
}


// --- Funções do Menu Atendente ---

void atendente_cadastrar_cliente(SistemaLocadora& sistema) {
    std::string nome, cnh, endereco;
    int cpf, idade, telefone;

    std::cout << "\n== Cadastrar Novo Cliente ==\n";
    std::cout << "Nome: ";
    limparBufferCin();
    std::getline(std::cin, nome);
    std::cout << "CPF (apenas numeros): ";
    std::cin >> cpf;
    std::cout << "CNH: ";
    limparBufferCin();
    std::getline(std::cin, cnh);
    std::cout << "Idade: ";
    std::cin >> idade;
    std::cout << "Telefone (apenas numeros): ";
    std::cin >> telefone;
    std::cout << "Endereco: ";
    limparBufferCin();
    std::getline(std::cin, endereco);

    sistema.cadastrarCliente(nome, cpf, cnh, idade, endereco, telefone);
}

void atendente_consultar_disponiveis(SistemaLocadora& sistema) {
    std::string nomeAgencia;
    std::cout << "\n== Consultar Veiculos Disponiveis ==\n";
    std::cout << "Nome da Agencia: ";
    limparBufferCin();
    std::getline(std::cin, nomeAgencia);

    try {
        auto disponiveis = sistema.consultarVeiculosDisponiveis(nomeAgencia);
        if (disponiveis.empty()) {
            std::cout << "Nenhum veiculo disponivel nesta agencia." << std::endl;
            return;
        }
        for (Veiculo* v : disponiveis) {
            std::cout << "  - [" << v->getPlaca() << "] " << v->getMarca() << " " 
                      << v->getModelo() << " (Diaria: R$" << v->getPrecoDiaria() << ")" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void atendente_criar_contrato(SistemaLocadora& sistema) {
    int cpf, diarias;
    std::string placa, agencia, dtRetirada, dtPrevisao;

    std::cout << "\n== Criar Novo Contrato ==\n";
    std::cout << "CPF do Cliente: ";
    std::cin >> cpf;
    std::cout << "Placa do Veiculo: ";
    limparBufferCin();
    std::getline(std::cin, placa);
    std::cout << "Agencia de Retirada: ";
    std::getline(std::cin, agencia);
    std::cout << "Data de Retirada (DD/MM/AAAA): ";
    std::getline(std::cin, dtRetirada);
    std::cout << "Diarias Previstas: ";
    std::cin >> diarias;
    std::cout << "Data Prev. Devolucao (DD/MM/AAAA): ";
    limparBufferCin();
    std::getline(std::cin, dtPrevisao);

    try {
        ContratoDeAluguel* c = sistema.criarContrato(cpf, placa, agencia, diarias, dtPrevisao, dtRetirada);
        std::cout << "Contrato ID " << c->getId() << " criado com sucesso!" << std::endl;
        std::cout << "Cliente: " << c->getCliente()->getNome() << std::endl;
        std::cout << "Veiculo: " << c->getVeiculo()->getModelo() << " [" << c->getVeiculo()->getPlaca() << "]" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}

void atendente_finalizar_contrato(SistemaLocadora& sistema) {
    int idContrato;
    std::string agencia, dtDevolucao;
    
    std::cout << "\n== Finalizar Contrato ==\n";
    std::cout << "ID do Contrato: ";
    std::cin >> idContrato;
    std::cout << "Agencia de Devolucao: ";
    limparBufferCin();
    std::getline(std::cin, agencia);
    std::cout << "Data de Devolucao (DD/MM/AAAA): ";
    std::getline(std::cin, dtDevolucao);

    try {
        sistema.finalizarContrato(idContrato, agencia, dtDevolucao);
        std::cout << "Contrato ID " << idContrato << " finalizado." << std::endl;
        // Aqui faltaria exibir o valor final, mas o Contrato não tem um getValor()
    } catch (const std::exception& e) {
        std::cout << "ERRO: " << e.what() << std::endl;
    }
}


// --- Menus Principais ---

void exibirMenuAtendente(SistemaLocadora& sistema) {
    int opcao = 0;
    while (opcao != 9) {
        std::cout << "\n--- Menu do Atendente ---" << std::endl;
        std::cout << "1. Cadastrar Cliente" << std::endl;
        std::cout << "2. Consultar Veiculos Disponiveis" << std::endl;
        std::cout << "3. Criar Contrato de Aluguel" << std::endl;
        std::cout << "4. Finalizar Contrato (Devolucao)" << std::endl;
        std::cout << "9. Voltar" << std::endl;
        std::cout << "Opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: atendente_cadastrar_cliente(sistema); break;
            case 2: atendente_consultar_disponiveis(sistema); break;
            case 3: atendente_criar_contrato(sistema); break;
            case 4: atendente_finalizar_contrato(sistema); break;
            case 9: std::cout << "Voltando..." << std::endl; break;
            default: std::cout << "Opcao invalida." << std::endl; break;
        }
    }
}

void exibirMenuGerente(SistemaLocadora& sistema) {
    int opcao = 0;
    while (opcao != 9) {
        std::cout << "\n--- Menu do Gerente de Frotas ---" << std::endl;
        std::cout << "1. Cadastrar Agencia" << std::endl;
        std::cout << "2. Cadastrar Veiculo" << std::endl;
        std::cout << "3. Listar Agencias e Frotas" << std::endl;
        std::cout << "4. Transferir Veiculo (Manual)" << std::endl;
        std::cout << "5. Executar Otimizacao Automatica" << std::endl;
        std::cout << "9. Voltar" << std::endl;
        std::cout << "Opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: gerente_cadastrar_agencia(sistema); break;
            case 2: gerente_cadastrar_veiculo(sistema); break;
            case 3: gerente_listar_agencias_e_frotas(sistema); break;
            case 4: gerente_transferir_veiculo(sistema); break;
            case 5: gerente_otimizar_frota(sistema); break;
            case 9: std::cout << "Voltando..." << std::endl; break;
            default: std::cout << "Opcao invalida." << std::endl; break;
        }
    }
}

// --- Ponto de Entrada ---

int main() {
    SistemaLocadora sistema;
    carregarDadosIniciais(sistema);

    int opcao = 0;
    while (opcao != 3) {
        std::cout << "\n=========================================" << std::endl;
        std::cout << "  Sistema de Gestao - Locadora de Veiculos" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "Selecione seu perfil:" << std::endl;
        std::cout << "1. Atendente (Operacoes de Aluguel)" << std::endl;
        std::cout << "2. Gerente (Gestao de Frota)" << std::endl;
        std::cout << "3. Sair" << std::endl;
        std::cout << "Opcao: ";
        
        std::cin >> opcao;

        if (std::cin.fail()) {
            std::cout << "Entrada invalida." << std::endl;
            std::cin.clear();
            limparBufferCin();
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1:
                exibirMenuAtendente(sistema);
                break;
            case 2:
                exibirMenuGerente(sistema);
                break;
            case 3:
                std::cout << "Encerrando sistema..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    }

    return 0;
}