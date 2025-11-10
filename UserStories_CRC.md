TRABALHO PDS - USER STORIES E CRC


Integrantes: Amanda Senario, Daiana David Rodrigues, Jamile Thalita Silva Fonseca, Davi Aredes


User Stories (Histórias de Usuário)

Atendente (Responsável pelas operações cotidianas da agência)


GESTÃO DE CLIENTES

- Como atendente, eu quero cadastrar os dados de um novo cliente (dados pessoais e dados do veículo) para que ele possa realizar o seu primeiro aluguel.

- Como atendente, eu quero verificar o histórico de clientes no meu banco de dados e averiguar o status de um cliente, como a existência de um contrato vencido ou de um cadastro existente, de forma a agilizar o processo.

- Como atendente, quero atualizar os dados de um cliente para garantir informações precisas.


OPERAÇÃO DE ALUGUEL

-  Como atendente, quero poder registrar no sistema um contrato de aluguel, no qual estão associados um cliente, um veículo, a data e hora de retirada e a data e hora previstas de devolução, para que o sistema reserve o carro e calcule o valor inicial do contrato.

- Como atendente, quero consultar os veículos disponíveis para aluguel na agência, para que eu possa oferecer as opções corretas ao cliente.

- Como atendente, quero registrar a devolução de um veículo, para que o contrato seja finalizado, o sistema calcule prazos que venceram (multas) e o veículo volte ao status “disponível”.

- Como atendente, quero poder filtrar os carros disponíveis para que eu possa atender melhor às necessidades do cliente.

Gerente de Frotas (Responsável pela gestão dos veículos, agências e pela otimização da logística)

GESTÃO DE CLIENTES

Como gerente, quero cadastrar todas as agências da minha locadora no sistema para monitorar a disponibilidade de veículos em cada agência e identificar rapidamente casos de superlotação ou falta de veículos.


Como gerente, eu quero cadastrar um novo veículo no sistema (informando placa, modelo, marca, ano, categoria e a agência na qual ele será alocado), para que ele passe a compor a frota de veículos.

Como gerente, eu quero poder alterar o status de um veículo para que eu possa mudar o status (ex: “vendido”, “em manutenção” ou “disponível”), para melhor gerenciamento.


GESTÃO DE AGÊNCIA

Como gerente eu quero cadastrar uma nova agência (filial) no sistema para que ela possa ter sua própria frota e contratos.

Como gerente eu quero consultar a lista de todas  agências cadastradas para que eu possa ter um maior controle dos processos.


OTIMIZAÇÃO

Como gerente eu quero visualizar no sistema as necessidades de cada agência para realizar transferências de veículos de agências com sobra para aquelas que estejam com falta, otimizando a distribuição da frota.

Como gerente eu quero organizar a capacidade de cada locadora para otimizar a alocação de veículos para que eu possa ter um maior controle do sistema e o balanceamento melhor das necessidades de cada uma delas.



CARTÕES CRC


Cliente 

Responsabilidades: 

1. Armazenar os dados pessoais dos clientes(nome, CNH, idade, CPF, endereço e telefone para contato).
2. Armazenar os dados do veículo alugado pelo cliente (Modelo, marca,placa, km, ano, cor).
3. Atualizar os dados do cliente sempre que houver novas informações.
4. Armazenar dados sobre o status do cliente (existência de um contrato vencido ou de um cadastro existente).



Colaboradores:
Veículo: Para atrelar os dados do veículo ao banco de dados do cliente no sistema.
Contrato de Aluguel: Armazenar as informações do contrato ao registro do cliente no sistema.



Veículos 

Responsabilidades:

1. Ter os dados de identificação (cor, ano, placa, modelo, marca, categoria)
2. Ter a sua categoria.
3. Ter os seus status atual atualizado (“disponível,”, “alugado” e “em manutenção”).
4. Permitir a alteração do seu status.
5. Fornecer seus dados para consulta.
6. Possui um contrato.

Colaboradores:


1. Agência: Para gerenciar o veículo.
2. Contrato: Para o veículo poder ser alugado

Contrato

Responsabilidades:

1. “Saber” qual cliente está alugando.
2. “Saber” qual veículo está sendo alugado.
3. “Saber” qual agência o veículo foi alugado ou retirado.
4. “Saber” suas informações (data de início e data de término).
5. “Saber” seu status (ativo e finalizado).
6. Calcular o seu valor quando o veículo for devolvido.
7. Registrar a devolução do veículo.
8. “Saber” suas informações, seu id.


Colaboradores:

1. Cliente: Para poder existir.
2. Veículo: Para poder existir.
3. Agência:  Para poder saber de onde o carro saiu e gerenciar os contratos.






Sistema Locadora (Otimização)

Responsabilidades:


1. Efetuar a transferência do veículo para uma outra locadora.
2. Implementar a otimização de frotas (saber qual agência está com sobra de veículos para a agência que está com falta).
3. Implementar a capacidade de cada agência em alocar uma quantidade máxima e mínima de veículos.

Colaboradores:


1. Agência: Para associar qual agência necessita de transferência de veículos e sua capacidade de locação.
2. Veículo: Para saber qual veículo será transferido. 



Agência

Responsabilidades:


1. Cadastrar as Agências da Locadora
2. Consultar a lista de Agências 
3. Consultar dados do cliente
4. Consultar dados do veículo
5. Consultar veículos disponíveis
6. Consultar devoluções em atraso
7. Cadastrar veículos
8. Atualizar status dos veículos


Colaboradores:
1. Cliente: Para consultar dados dos clientes e realizar alterações se necessário.
2. Veículos: Para cadastrar um veículo, consultar  e alterar status.







 
