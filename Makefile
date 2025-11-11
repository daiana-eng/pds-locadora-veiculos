
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Iinclude

# Diretórios
BUILD_DIR = build
TEST_DIR = tests
SRC_DIR = src

# Fontes que podemos compilar no momento
# NOTA: src/Contrato.cpp foi omitido pois depende de Cliente.hpp/cpp
SRCS = $(SRC_DIR)/Agencia.cpp \
       $(SRC_DIR)/VeiculoEconomico.cpp \
       $(SRC_DIR)/output/VeiculoLuxo.cpp

# Arquivo de teste
TEST_SRC = $(TEST_DIR)/test.cpp

# Executável de teste
TEST_TARGET = $(BUILD_DIR)/run_tests

.PHONY: all test clean

# 'make' ou 'make all' por padrão rodarão os testes
all: test

# Compila e executa os testes
test: $(TEST_TARGET)
	@echo "--- [ Executando Testes Iniciais ] ---"
	./$(TEST_TARGET)
	@echo "--------------------------------------"

# Regra para linkar o executável de teste
$(TEST_TARGET): $(TEST_SRC) $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(SRCS)

# Limpa os arquivos compilados
clean:
	@echo "Limpando diretório build..."
	rm -rf $(BUILD_DIR)