#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

#define MENU_CADASTRAR 1
#define MENU_LISTAR 2
#define MENU_BUSCAR 3
#define MENU_ATUALIZAR 4
#define MENU_EXCLUIR 5
#define MENU_SAIR 0

void exibirMenuPrincipal(void);
int lerOpcaoMenu(void);
void cadastrarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int *totalVeiculos
);
void listarVeiculos(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
);
int buscarVeiculoPorPlaca(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int totalVeiculos,
    const char *placa
);
int buscarVagaLivre(
    int statusVagas[MAX_VAGAS],
    int totalVagas
);
int validarPlaca(const char *placa);
int validarTipoVeiculo(int tipo);
int validarHorario(int hora, int minuto);
int placaJaCadastrada(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int totalVeiculos,
    const char *placa
);
void inicializarVagas(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA]
);
int ocuparVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga,
    const char *placa
);

static void limparBufferEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    char placas[MAX_VEICULOS][TAM_PLACA];
    char modelos[MAX_VEICULOS][TAM_MODELO];
    int tipos[MAX_VEICULOS];
    int entradaHora[MAX_VEICULOS];
    int entradaMinuto[MAX_VEICULOS];
    int statusVeiculo[MAX_VEICULOS];
    int numeroVagaVeiculo[MAX_VEICULOS];

    char placasVagas[MAX_VAGAS][TAM_PLACA];
    int statusVagas[MAX_VAGAS];
    int numeroVagas[MAX_VAGAS];

    int totalVeiculos = 0;
    int opcao;

    for (int i = 0; i < MAX_VEICULOS; i++) {
        placas[i][0] = '\0';
        modelos[i][0] = '\0';
        tipos[i] = 0;
        entradaHora[i] = 0;
        entradaMinuto[i] = 0;
        statusVeiculo[i] = 0;
        numeroVagaVeiculo[i] = 0;
    }

    inicializarVagas(statusVagas, numeroVagas, placasVagas);

    do {
        exibirMenuPrincipal();
        opcao = lerOpcaoMenu();

        switch (opcao) {
            case MENU_CADASTRAR:
                cadastrarVeiculo(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    placasVagas,
                    statusVagas,
                    numeroVagas,
                    &totalVeiculos
                );
                break;
            case MENU_LISTAR:
                listarVeiculos(
                    placas,
                    modelos,
                    tipos,
                    entradaHora,
                    entradaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    totalVeiculos
                );
                break;
            case MENU_BUSCAR:
            case MENU_ATUALIZAR:
            case MENU_EXCLUIR:
                printf("Opcao em desenvolvimento.\n");
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

void exibirMenuPrincipal(void) {
    printf("\n=== Sistema de Estacionamento ===\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Listar veiculos\n");
    printf("3 - Buscar veiculo\n");
    printf("4 - Atualizar veiculo\n");
    printf("5 - Excluir veiculo\n");
    printf("0 - Sair\n");
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

void cadastrarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int *totalVeiculos
) {
    char placa[TAM_PLACA];
    char modelo[TAM_MODELO];
    int tipo;
    int hora;
    int minuto;
    int vagaLivre;

    if (*totalVeiculos >= MAX_VEICULOS) {
        printf("Cadastro cheio.\n");
        return;
    }

    printf("Placa: ");
    scanf(" %7s", placa);

    if (!validarPlaca(placa) || placaJaCadastrada(placas, *totalVeiculos, placa)) {
        printf("Placa invalida ou ja cadastrada.\n");
        return;
    }

    printf("Modelo: ");
    scanf(" %49s", modelo);

    printf("Tipo (1-Carro, 2-Moto, 3-PCD, 4-Eletrico): ");
    scanf("%d", &tipo);

    if (!validarTipoVeiculo(tipo)) {
        printf("Tipo invalido.\n");
        return;
    }

    printf("Hora de entrada: ");
    scanf("%d", &hora);
    printf("Minuto de entrada: ");
    scanf("%d", &minuto);

    if (!validarHorario(hora, minuto)) {
        printf("Horario invalido.\n");
        return;
    }

    vagaLivre = buscarVagaLivre(statusVagas, MAX_VAGAS);
    if (vagaLivre == -1) {
        printf("Nao ha vagas disponiveis.\n");
        return;
    }

    strcpy(placas[*totalVeiculos], placa);
    strcpy(modelos[*totalVeiculos], modelo);
    tipos[*totalVeiculos] = tipo;
    entradaHora[*totalVeiculos] = hora;
    entradaMinuto[*totalVeiculos] = minuto;
    statusVeiculo[*totalVeiculos] = STATUS_ESTACIONADO;
    numeroVagaVeiculo[*totalVeiculos] = numeroVagas[vagaLivre];

    ocuparVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagas[vagaLivre], placa);

    (*totalVeiculos)++;

    printf("Veiculo cadastrado com sucesso na vaga %d.\n", numeroVagaVeiculo[*totalVeiculos - 1]);
}

void listarVeiculos(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
) {
    int i;

    if (totalVeiculos == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    for (i = 0; i < totalVeiculos; i++) {
        printf("\nVeiculo %d\n", i + 1);
        printf("Placa: %s\n", placas[i]);
        printf("Modelo: %s\n", modelos[i]);
        printf("Tipo: %d\n", tipos[i]);
        printf("Entrada: %02d:%02d\n", entradaHora[i], entradaMinuto[i]);
        printf("Status: %s\n", statusVeiculo[i] == STATUS_ESTACIONADO ? "Estacionado" : "Saiu");
        printf("Vaga: %d\n", numeroVagaVeiculo[i]);
    }
}

int buscarVeiculoPorPlaca(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int totalVeiculos,
    const char *placa
) {
    int i;

    for (i = 0; i < totalVeiculos; i++) {
        if (strcmp(placas[i], placa) == 0) {
            return i;
        }
    }

    return -1;
}

int buscarVagaLivre(
    int statusVagas[MAX_VAGAS],
    int totalVagas
) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (statusVagas[i] == VAGA_LIVRE) {
            return i;
        }
    }

    return -1;
}

int validarPlaca(const char *placa) {
    int i;

    if (placa == NULL || strlen(placa) != 7) {
        return 0;
    }

    for (i = 0; i < 7; i++) {
        if (!isalnum((unsigned char)placa[i])) {
            return 0;
        }
    }

    return 1;
}

int validarTipoVeiculo(int tipo) {
    return tipo >= TIPO_CARRO && tipo <= TIPO_ELETRICO;
}

int validarHorario(int hora, int minuto) {
    if (hora < 0 || hora > 23) {
        return 0;
    }

    if (minuto < 0 || minuto > 59) {
        return 0;
    }

    return 1;
}

int placaJaCadastrada(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int totalVeiculos,
    const char *placa
) {
    return buscarVeiculoPorPlaca(placas, totalVeiculos, placa) != -1;
}

void inicializarVagas(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA]
) {
    int i;

    for (i = 0; i < MAX_VAGAS; i++) {
        statusVagas[i] = VAGA_LIVRE;
        numeroVagas[i] = i + 1;
        placasVagas[i][0] = '\0';
    }
}

int ocuparVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga,
    const char *placa
) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (numeroVagas[i] == numeroVaga && statusVagas[i] == VAGA_LIVRE) {
            statusVagas[i] = VAGA_OCUPADA;
            strcpy(placasVagas[i], placa);
            return 1;
        }
    }

    return 0;
}
