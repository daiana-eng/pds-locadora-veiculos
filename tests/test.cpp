#include <iostream>
#include <cassert> // Usando assert para testes simples
#include "Agencia.hpp"
#include "VeiculoEconomico.hpp"
#include "VeiculoLuxo.hpp"
#include "Veiculo.hpp"

/*
NOTA: Este arquivo de teste NÃO PODE incluir "Cliente.hpp" 
ou "ContratoAluguel.hpp" ainda, pois suas implementações 
(.cpp) estão pendentes.
*/

void testCriacaoAgencia() {
    Agencia agencia("Agencia Central", "Rua A, 123");
    assert(agencia.getnome() == "Agencia Central");
    assert(agencia.getEndereço() == "Rua A, 123");
    assert(agencia.getFrota().size() == 0);
    std::cout << "PASS: testCriacaoAgencia" << std::endl;
}

void testAdicionarVeiculo() {
    Agencia agencia("AgFilial", "Rua B, 456");
    
    // Teste com VeiculoEconomico
    Veiculo* v1 = new VeiculoEconomico("ABC-1111", "Fiat", "Mobi", 2020, "Economico");
    agencia.adicionarVeiculo(v1);
    
    assert(agencia.getFrota().size() == 1);
    assert(agencia.getFrota()[0]->getPlaca() == "ABC-1111");
    
    // Teste com VeiculoLuxo
    Veiculo* v2 = new VeiculoLuxo("LUX-2222", "Ferrari", "Ferrari", 2023);
    agencia.adicionarVeiculo(v2);
    
    assert(agencia.getFrota().size() == 2);
    assert(agencia.getFrota()[1]->getModelo() == "Ferrari");

    std::cout << "PASS: testAdicionarVeiculo" << std::endl;
    
    // O ~Agencia() deletará v1 e v2
}

void testPrecoDiaria() {
    Veiculo* mobi = new VeiculoEconomico("ECO-0001", "Fiat", "Mobi", 2020, "Economico");
    assert(mobi->getPrecoDiaria() == 600.00); // Valor de VeiculoEconomico.cpp

    Veiculo* porsche = new VeiculoLuxo("LUX-0001", "Porsche", "Porsche", 2024);
    assert(porsche->getPrecoDiaria() == 4450.00); // Valor de VeiculoLuxo.cpp

    std::cout << "PASS: testPrecoDiaria" << std::endl;
    
    delete mobi;
    delete porsche;
}


int main() {
    std::cout << "Iniciando testes..." << std::endl;
    
    testCriacaoAgencia();
    testAdicionarVeiculo();
    testPrecoDiaria();
    
    std::cout << "\nTodos os testes iniciais passaram com sucesso!" << std::endl;
    
    return 0;
}