#ifndef PARKING_H
#define PARKING_H

#include <stdio.h>

#define MAX_VEICULOS 100
#define MAX_VAGAS 100
#define TAM_PLACA 8
#define TAM_MODELO 50

#define TIPO_CARRO 1
#define TIPO_MOTO 2
#define TIPO_PCD 3
#define TIPO_ELETRICO 4

#define STATUS_ESTACIONADO 1
#define STATUS_SAIU 2

#define VAGA_LIVRE 0
#define VAGA_OCUPADA 1

#define MENU_CADASTRO 1
#define MENU_ENTRADA 2
#define MENU_SAIDA 3
#define MENU_CONSULTA 4
#define MENU_ATUALIZAR 5
#define MENU_EXCLUIR 6
#define MENU_RELATORIOS 7
#define MENU_SAIR 0

void exibirMenuPrincipal(void);
int lerOpcaoMenu(void);

void cadastrarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int *totalVeiculos,
    int *totalVagasOcupadas
);
void registrarEntradaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int totalVeiculos,
    int *totalVagasOcupadas
);
void registrarSaidaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int totalVeiculos,
    int *totalVagasOcupadas
);
void consultaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
);
void atualizarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int totalVeiculos
);
void excluirVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int *totalVeiculos,
    int *totalVagasOcupadas
);
void relatoriosControleVagas(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVeiculos,
    int totalVagasOcupadas
);

void inicializarVagas(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA]
);
int buscarVeiculoPorPlaca(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int totalVeiculos,
    const char *placa
);
int buscarVagaLivre(int statusVagas[MAX_VAGAS], int totalVagas);
int buscarIndiceVagaPorNumero(
    int numeroVagas[MAX_VAGAS],
    int totalVagas,
    int numeroVaga
);
int validarPlaca(const char *placa);
int validarTipoVeiculo(int tipo);
int validarHorario(int hora, int minuto);
int placaJaCadastrada(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int totalVeiculos,
    const char *placa
);
int ocuparVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga,
    const char *placa
);
int liberarVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga
);
int contarVagasLivres(int statusVagas[MAX_VAGAS], int totalVagas);
int calcularTempoEstacionado(
    int entradaHora,
    int entradaMinuto,
    int saidaHora,
    int saidaMinuto
);
float calcularValorEstadia(int tempoMinutos, int tipoVeiculo);

#endif
