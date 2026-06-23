#include "parking.h"

static void limparDadosVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS]
) {
    int i;

    for (i = 0; i < MAX_VEICULOS; i++) {
        placas[i][0] = '\0';
        modelos[i][0] = '\0';
        tipos[i] = 0;
        entradaHora[i] = 0;
        entradaMinuto[i] = 0;
        saidaHora[i] = 0;
        saidaMinuto[i] = 0;
        statusVeiculo[i] = 0;
        numeroVagaVeiculo[i] = 0;
    }
}

int main(void) {
    char placas[MAX_VEICULOS][TAM_PLACA];
    char modelos[MAX_VEICULOS][TAM_MODELO];
    int tipos[MAX_VEICULOS];
    int entradaHora[MAX_VEICULOS];
    int entradaMinuto[MAX_VEICULOS];
    int saidaHora[MAX_VEICULOS];
    int saidaMinuto[MAX_VEICULOS];
    int statusVeiculo[MAX_VEICULOS];
    int numeroVagaVeiculo[MAX_VEICULOS];
    char placasVagas[MAX_VAGAS][TAM_PLACA];
    int statusVagas[MAX_VAGAS];
    int numeroVagas[MAX_VAGAS];
    int totalVeiculos = 0;
    int totalVagasOcupadas = 0;
    int opcao;

    limparDadosVeiculo(
        placas,
        modelos,
        tipos,
        entradaHora,
        entradaMinuto,
        saidaHora,
        saidaMinuto,
        statusVeiculo,
        numeroVagaVeiculo
    );
    inicializarVagas(statusVagas, numeroVagas, placasVagas);

    do {
        exibirMenuPrincipal();
        opcao = lerOpcaoMenu();

        switch (opcao) {
            case MENU_CADASTRO:
                cadastrarVeiculo(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    saidaHora,
                    saidaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    placasVagas,
                    statusVagas,
                    numeroVagas,
                    &totalVeiculos,
                    &totalVagasOcupadas
                );
                break;
            case MENU_ENTRADA:
                registrarEntradaVeiculo(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    saidaHora,
                    saidaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    placasVagas,
                    statusVagas,
                    numeroVagas,
                    totalVeiculos,
                    &totalVagasOcupadas
                );
                break;
            case MENU_SAIDA:
                registrarSaidaVeiculo(
                    placas,
                    entradaHora,
                    entradaMinuto,
                    saidaHora,
                    saidaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    placasVagas,
                    statusVagas,
                    numeroVagas,
                    totalVeiculos,
                    &totalVagasOcupadas
                );
                break;
            case MENU_CONSULTA:
                consultaVeiculo(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    saidaHora,
                    saidaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    totalVeiculos
                );
                break;
            case MENU_ATUALIZAR:
                atualizarVeiculo(placas, modelos, tipos, totalVeiculos);
                break;
            case MENU_EXCLUIR:
                excluirVeiculo(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    saidaHora,
                    saidaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    placasVagas,
                    statusVagas,
                    numeroVagas,
                    &totalVeiculos,
                    &totalVagasOcupadas
                );
                break;
            case MENU_RELATORIOS:
                relatoriosControleVagas(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    saidaHora,
                    saidaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    statusVagas,
                    numeroVagas,
                    placasVagas,
                    totalVeiculos,
                    totalVagasOcupadas
                );
                break;
            case MENU_SAIR:
                printf("Encerrando o sistema.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != MENU_SAIR);

    return 0;
}
