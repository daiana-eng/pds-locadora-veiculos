#include <iostream>
#include "Cliente.hpp"
#include "Agencia.hpp"
#include "Veiculo.hpp"
#include <map>
#include <string>




void atualizarDados(std::map<int, Cliente>&cadastroCliente_){
    int idCpf;
    std::cout <<"Digite o numero do Cpf que deseja atualizar." << std::endl;
    std::cin >> idCpf;




    auto it = cadastroCliente_.find(idCpf);




    if(it != cadastroCliente_.end()){




        Cliente& clienteParaAtualizar = it->second;
        int id;
        std::cout << "O que deseja atualizar? 1-Endereco, 2-Idade, 3-Telefone" << std::endl;
        std::cin >> id;




        if(id == 1){
            std::string novoEndereco;
            std::cout << "Digite o novo endereco " << std::endl;
            std::cin.ignore();
            std::getline(std::cin, novoEndereco);
            clienteParaAtualizar.setEndereco(novoEndereco);




        }




        else if(id == 2){
            int novaIdade;
            std::cout << "Digite a nova idade " << std::endl;
            std::cin >> novaIdade;
            clienteParaAtualizar.setIdade(novaIdade);




        }
        else if(id == 3){
            int novoTelefone;
            std::cout << "Digite o novo telefone " << std::endl;
            std::cin >> novoTelefone;
            clienteParaAtualizar.setTelefone(novoTelefone);
        }
        else {
            std::cout << "Erro: Cliente com CPF " << idCpf << " nao encontrado!" << std::endl;
        }
    }
}




void cadastrarNovoCliente(std::map<int, Cliente>& cadastroCliente_){
    std::string temp_nome, temp_cnh, temp_endereco;
    int temp_cpf, temp_idade, temp_telefone;
    std::cout << "Digite o cpf (somente numeros)" << std::endl;
    std::cin >> temp_cpf;




    std::cout << "Digite o nome completo: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, temp_nome);




    std::cout << "Digite o cnh: " << std::endl;
    std::cin >> temp_cnh;




    std::cout << "Digite o endereco: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, temp_endereco);




    std::cout << "Digite a idade: " << std::endl;
    std::cin >> temp_idade;
   
    std::cout << "Digite o numero de telefone(somente numeros): " << std::endl;
    std::cin >> temp_telefone;
   




    Cliente registraCliente(temp_nome, temp_cpf, temp_cnh, temp_idade, temp_endereco, temp_telefone);




    cadastroCliente_.insert({temp_cpf,registraCliente});




    std::cout << "Cliente: " << registraCliente.getNome() << " cadastrado com sucesso!" << std::endl;
   
}




void cadastrarAgencia(std::map<std::string, Agencia>& cadastroAgencia){
    std::string t_nome, t_endereco;




    std::cout << "Qual o nome da Agencia? " << std::endl;
    std::getline(std::cin, t_nome);




    std::cout << "Qual é o endereco da Agencia? " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, t_endereco);




    Agencia registraAgencia(t_nome, t_endereco);
    cadastroAgencia.insert({t_nome,registraAgencia});
}

<<<<<<< HEAD
void cadastrarNovoVeiculo(std::map<std::string, Agencia>& cadastroAgencia){
    std::cout << "Digite o nome da agencia onde o veiculo sera registrado" << std::endl;
    std::string nomeAgencia;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max()) << std::endl;
    std::getline(std::cin, nomeAgencia);

    auto it = cadastroAgencia.find(nomeAgencia);
    if(it == cadastroAgencia.end()){
        return;
    }

    Agencia& agencia = it->second;

    std::cout << "Selecione a categoria: 1.Economico, 2.Luxo" << std::endl;

    int categoria;
    std::cin >> categoria;

    std::string placa, marca, modelo;
    int ano;

    std::cout << "Digite a placa" << std::endl;
    std::getline(std::cin, placa);

    std::cout << "Digite a marca" << std::endl;
    std::getline(std::cin, marca);

    std::cout << "Digite o modelo" << std::endl;
    std::getline(std::cin,modelo);

    std::cout << "Digite o ano" << std::endl;
    std::cin >> ano;

    Veiculo* veiculoRecemCadastro = nullptr;

    switch (categoria)
    {
    case 1:
        veiculoRecemCadastro = new VeiculoEconomico(placa,marca,modelo,ano);
        break;

    case 2: 
        veiculoRecemCadastro = new VeiculoLuxo(placa,marca,modelo,ano);
        break;
    
    default:
        break;
    }

    if(veiculoRecemCadastro != nullptr) {
        agencia.adicionarVeiculo(veiculoRecemCadastro);
    }
}

=======
>>>>>>> 255af916a223fcce8a023c0adbb55c1f1f86f2ab

void cadastrarNovoVeiculo(std::map<std::string, Agencia>& cadastroAgencia){
    std::cout << "Digite o nome da agencia onde o veiculo sera registrado" << std::endl;
    std::string nomeAgencia;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max()) << std::endl;
    std::getline(std::cin, nomeAgencia);


    auto it = cadastroAgencia.find(nomeAgencia);
    if(it == cadastroAgencia.end()){
        return;
    }


    Agencia& agencia = it->second;


    std::cout << "Selecione a categoria: 1.Economico, 2.Luxo" << std::endl;


    int categoria;
    std::cin >> categoria;


    std::string placa, marca, modelo;
    int ano;


    std::cout << "Digite a placa" << std::endl;
    std::getline(std::cin, placa);


    std::cout << "Digite a marca" << std::endl;
    std::getline(std::cin, marca);


    std::cout << "Digite o modelo" << std::endl;
    std::getline(std::cin,modelo);


    std::cout << "Digite o ano" << std::endl;
    std::cin >> ano;


    Veiculo* veiculoRecemCadastro = nullptr;


    switch (categoria)
    {
    case 1:
        veiculoRecemCadastro = new VeiculoEconomico(placa,marca,modelo,ano);
        break;


    case 2:
        veiculoRecemCadastro = new VeiculoLuxo(placa,marca,modelo,ano);
        break;
   
    default:
        break;
    }


    if(veiculoRecemCadastro != nullptr) {
        agencia.adicionarVeiculo(veiculoRecemCadastro);
    }
}




int main(){
   
    std::map<int, Cliente> cadastroCliente_;
    std::map<std::string, Agencia> cadastroAgencia;
     bool continua = true;
    while(continua){
        std::cout << "1.Cadastrar novo Cliente" << std::endl;
        std::cout << "2.Cadastrar nova Agencia" << std::endl;
        std::cout << "3.Atualizar Dados do Cliente" << std::endl;
        std::cout << "4.Sair" << std::endl;
       
        int escolha;
        std::cin >> escolha;
        switch (escolha)
        {
        case 1:
            cadastrarNovoCliente(cadastroCliente_);
            break;
       
        case 2:
            cadastrarAgencia(cadastroAgencia);
            break;

        case 3:
            atualizarDados(cadastroCliente_);
            break;
<<<<<<< HEAD


        case 4:
            cadastrarNovoVeiculo(cadastroAgencia);
            break;

       
        case 5:
=======
<<<<<<< HEAD

        case 4:
            cadastrarNovoVeiculo(cadastroAgencia);
            break;
       
        case 5:
=======
       
        case 4:
>>>>>>> 255af916a223fcce8a023c0adbb55c1f1f86f2ab
>>>>>>> 4646533a5c45bc4dc483bd2d476408bbcd84ae95
            continua = false;
             break;
        default:
            break;
        }
       


    }
   
    return 0;
<<<<<<< HEAD
} 

=======
}
<<<<<<< HEAD
=======
>>>>>>> 4646533a5c45bc4dc483bd2d476408bbcd84ae95

>>>>>>> 255af916a223fcce8a023c0adbb55c1f1f86f2ab
