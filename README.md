# Projeto de Laboratório de Algoritmos

## Informações do trabalho

- **Disciplina:** Laboratório de Algoritmos
- **Professor:** Bruno Borges
- **Aluno:** Francisco das Chagas Teixeira Filho
- **Aluno 2:** Aluno 2
- **Aluno 3:** Aluno 3

## Sobre o projeto

Este trabalho consiste no desenvolvimento de um **sistema de estacionamento de shopping** em linguagem C.

A proposta do sistema é organizar, em memória, o controle dos veículos estacionados, das vagas disponíveis e das operações básicas de cadastro, busca, atualização e exclusão.

Nesta etapa inicial, o projeto foi estruturado com foco acadêmico, utilizando:

- arrays estáticos;
- constantes com `#define`;
- funções separadas por responsabilidade;
- validações básicas;
- modelagem em memória sem alocação dinâmica.

O arquivo `main.c` presente neste repositório contém o **esqueleto inicial** do sistema, servindo como base para as próximas entregas do projeto.

## O que o sistema representa

O sistema simula o funcionamento de um estacionamento de shopping, permitindo futuramente:

- cadastrar veículos;
- listar veículos cadastrados;
- buscar veículo pela placa;
- atualizar dados do veículo;
- remover veículos;
- controlar vagas livres e ocupadas;
- calcular tempo de permanência;
- calcular valor da estadia.

## Conteúdos da ementa utilizados

Este trabalho utiliza diretamente conteúdos vistos na disciplina de Laboratório de Algoritmos, como:

- tipos primitivos e variáveis;
- escopo de variáveis;
- estruturas condicionais;
- estruturas de repetição;
- vetores e matrizes;
- modularização por funções;
- passagem de parâmetros;
- organização de dados em memória;
- validação de entrada do usuário.

## Estrutura do projeto

- `main.c`: arquivo principal com a base do sistema.
- `checkpoint1_estacionamento.md`: documentação do primeiro checkpoint do projeto.

## Como compilar

### Usando GCC no Windows

Abra o terminal na pasta do projeto e execute:

```bash
gcc main.c -o estacionamento.exe
```

### Usando GCC no Linux ou macOS

```bash
gcc main.c -o estacionamento
```

## Como rodar

### Windows

```bash
estacionamento.exe
```

### Linux ou macOS

```bash
./estacionamento
```

## Observações

- O projeto foi montado sem uso de `struct`, conforme orientação do professor.
- Também não utiliza alocação dinâmica.
- Nesta fase, o arquivo principal está apenas como base estrutural para a implementação futura.

