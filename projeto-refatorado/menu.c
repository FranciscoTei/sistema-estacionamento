#include "parking.h"

static void limparBufferEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void exibirMenuPrincipal(void) {
    printf("\n==============================\n");
    printf(" Sistema de Estacionamento\n");
    printf("==============================\n");
    printf("1. Cadastro de veiculo\n");
    printf("2. Registrar entrada de veiculo\n");
    printf("3. Registrar saida de veiculo\n");
    printf("4. Consulta de veiculo\n");
    printf("5. Atualizar dados do veiculo\n");
    printf("6. Excluir veiculo\n");
    printf("7. Relatorios e controle de vagas\n");
    printf("0. Sair\n");
    printf("Opcao: ");
}

int lerOpcaoMenu(void) {
    int opcao;

    if (scanf("%d", &opcao) != 1) {
        limparBufferEntrada();
        return -1;
    }

    return opcao;
}
