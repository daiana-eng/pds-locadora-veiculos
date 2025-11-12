CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude

# Diretórios
BUILD_DIR = build
TEST_DIR = tests
SRC_DIR = src
INCLUDE_DIR = include

# Todos os arquivos fonte
SRCS = $(SRC_DIR)/Agencia.cpp \
       $(SRC_DIR)/Cliente.cpp \
       $(SRC_DIR)/Contrato.cpp \
       $(SRC_DIR)/VeiculoEconomico.cpp \
       $(SRC_DIR)/VeiculoLuxo.cpp \
       $(SRC_DIR)/SistemaLocadora.cpp \
       $(SRC_DIR)/main.cpp

# Objetos intermediários
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executável principal
TARGET = $(BUILD_DIR)/locadora.exe

# Arquivo de teste
TEST_SRC = $(TEST_DIR)/test.cpp
TEST_OBJS = $(BUILD_DIR)/Agencia.o \
            $(BUILD_DIR)/VeiculoEconomico.o \
            $(BUILD_DIR)/VeiculoLuxo.o
TEST_TARGET = $(BUILD_DIR)/run_tests.exe

.PHONY: all run test clean dirs

# Regra padrão: compila o programa principal
all: dirs $(TARGET)

# Compila e executa o programa principal
run: all
	@echo =========================================
	@echo   Executando Sistema de Locadora
	@echo =========================================
	@$(TARGET)

# Compila e executa os testes
test: dirs $(TEST_TARGET)
	@echo --- [ Executando Testes ] ---
	@$(TEST_TARGET)
	@echo -----------------------------

# Cria os diretórios necessários (CORRIGIDO PARA WINDOWS)
dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "data" mkdir "data"

# Regra para linkar o executável principal
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo Build completo: $(TARGET)

# Regra para compilar cada arquivo .cpp em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para linkar o executável de teste
$(TEST_TARGET): $(TEST_SRC) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(TEST_OBJS)

# Limpa os arquivos compilados (CORRIGIDO PARA WINDOWS)
clean:
	@echo Limpando diretório build...
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@echo Limpeza concluída.

# Informações sobre o projeto
info:
	@echo Sistema de Locadora de Veículos - PDS2
	@echo Arquivos fonte: $(SRCS)
	@echo Executável: $(TARGET)
	@echo.
	@echo Comandos disponíveis:
	@echo   mingw32-make          - Compila o projeto
	@echo   mingw32-make run      - Compila e executa o sistema
	@echo   mingw32-make test     - Compila e executa os testes
	@echo   mingw32-make clean    - Remove arquivos compilados