# Pool de Conexões Concorrente

## Objetivo do projeto
Este projeto é uma implementação em C++ de um Pool de Conexões, desenvolvido para a disciplina de Programação Concorrente. O objetivo é gerenciar o acesso simultâneo a recursos limitados, simulando um servidor onde 20 requisições (threads) concorrem por exatamente 5 conexões de banco de dados disponíveis. A solução atende rigorosamente aos requisitos do problema "Pool de Conexões" utilizando a abstração de Monitores.

## Arquitetura e Sincronização
A arquitetura baseia-se na classe `ConnectionPool`, que atua como um Monitor. Todo o estado compartilhado (quantidade de conexões totais, conexões em uso e o status individual de cada conexão) é encapsulado e inacessível externamente. 

O controle de concorrência é construído exclusivamente com a API nativa do C++11:
* **Exclusão Mútua:** O acesso e a modificação do estado interno são protegidos por `std::mutex` combinado com `std::unique_lock`, impedindo condições de corrida durante a alocação e devolução de conexões.
* **Variável de Condição:** O bloqueio das requisições excedentes é gerenciado por uma `std::condition_variable`. Quando o pool está vazio, a thread invoca `wait()`, suspendendo sua execução no sistema operacional sem causar espera ocupada (*busy waiting*). A devolução de uma conexão aciona `notify_one()`, despertando uma thread bloqueada para prosseguir.

## Estrutura do projeto
O projeto é modularizado separando as definições de classe e as implementações lógicas.

```text
.
├── include/
│   └── ConnectionPool.hpp
├── src/
│   ├── ConnectionPool.cpp
│   └── main.cpp
└── README.md
```

## Como compilar e executar
Certifique-se de ter um ambiente configurado com suporte a C++11 e a biblioteca pthreads.
Navegue até o diretório raiz do projeto e execute o comando de compilação:

```bash
g++ -std=c++11 -Wall -Wextra -pthread src/ConnectionPool.cpp src/main.cpp -o pool_conexoes
```
Para executar a simulação:
```bash
./pool_conexoes
