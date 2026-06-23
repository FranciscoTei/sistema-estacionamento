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

void inicializarVagas(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA]);
int buscarVeiculoPorPlaca(char placas[MAX_VEICULOS][TAM_PLACA], int totalVeiculos, const char *placa);
int buscarVagaLivre(int statusVagas[MAX_VAGAS], int totalVagas);
int buscarIndiceVagaPorNumero(int numeroVagas[MAX_VAGAS], int totalVagas, int numeroVaga);
int validarPlaca(const char *placa);
int validarTipoVeiculo(int tipo);
int validarHorario(int hora, int minuto);
int placaJaCadastrada(char placas[MAX_VEICULOS][TAM_PLACA], int totalVeiculos, const char *placa);
int ocuparVaga(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA], int totalVagas, int numeroVaga, const char *placa);
int liberarVaga(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA], int totalVagas, int numeroVaga);
int contarVagasLivres(int statusVagas[MAX_VAGAS], int totalVagas);
int calcularTempoEstacionado(int entradaHora, int entradaMinuto, int saidaHora, int saidaMinuto);
float calcularValorEstadia(int tempoMinutos, int tipoVeiculo);

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

static void limparBufferEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

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

void inicializarVagas(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA]) {
    int i;

    for (i = 0; i < MAX_VAGAS; i++) {
        statusVagas[i] = VAGA_LIVRE;
        numeroVagas[i] = i + 1;
        placasVagas[i][0] = '\0';
    }
}

int buscarVeiculoPorPlaca(char placas[MAX_VEICULOS][TAM_PLACA], int totalVeiculos, const char *placa) {
    int i;

    for (i = 0; i < totalVeiculos; i++) {
        if (strcmp(placas[i], placa) == 0) {
            return i;
        }
    }

    return -1;
}

int buscarVagaLivre(int statusVagas[MAX_VAGAS], int totalVagas) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (statusVagas[i] == VAGA_LIVRE) {
            return i;
        }
    }

    return -1;
}

int buscarIndiceVagaPorNumero(int numeroVagas[MAX_VAGAS], int totalVagas, int numeroVaga) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (numeroVagas[i] == numeroVaga) {
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

int placaJaCadastrada(char placas[MAX_VEICULOS][TAM_PLACA], int totalVeiculos, const char *placa) {
    return buscarVeiculoPorPlaca(placas, totalVeiculos, placa) != -1;
}

int ocuparVaga(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA], int totalVagas, int numeroVaga, const char *placa) {
    int indice = buscarIndiceVagaPorNumero(numeroVagas, totalVagas, numeroVaga);

    if (indice == -1 || statusVagas[indice] == VAGA_OCUPADA) {
        return 0;
    }

    statusVagas[indice] = VAGA_OCUPADA;
    strcpy(placasVagas[indice], placa);
    return 1;
}

int liberarVaga(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA], int totalVagas, int numeroVaga) {
    int indice = buscarIndiceVagaPorNumero(numeroVagas, totalVagas, numeroVaga);

    if (indice == -1 || statusVagas[indice] == VAGA_LIVRE) {
        return 0;
    }

    statusVagas[indice] = VAGA_LIVRE;
    placasVagas[indice][0] = '\0';
    return 1;
}

int contarVagasLivres(int statusVagas[MAX_VAGAS], int totalVagas) {
    int i;
    int livres = 0;

    for (i = 0; i < totalVagas; i++) {
        if (statusVagas[i] == VAGA_LIVRE) {
            livres++;
        }
    }

    return livres;
}

int calcularTempoEstacionado(int entradaHora, int entradaMinuto, int saidaHora, int saidaMinuto) {
    int entradaTotal = entradaHora * 60 + entradaMinuto;
    int saidaTotal = saidaHora * 60 + saidaMinuto;

    if (saidaTotal < entradaTotal) {
        return 0;
    }

    return saidaTotal - entradaTotal;
}

float calcularValorEstadia(int tempoMinutos, int tipoVeiculo) {
    float valorHora;
    int horas;

    if (tempoMinutos <= 0) {
        return 0.0f;
    }

    horas = (tempoMinutos + 59) / 60;

    if (tipoVeiculo == TIPO_MOTO) {
        valorHora = 5.0f;
    } else if (tipoVeiculo == TIPO_PCD) {
        valorHora = 0.0f;
    } else if (tipoVeiculo == TIPO_ELETRICO) {
        valorHora = 7.0f;
    } else {
        valorHora = 10.0f;
    }

    return horas * valorHora;
}

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
    saidaHora[*totalVeiculos] = 0;
    saidaMinuto[*totalVeiculos] = 0;
    statusVeiculo[*totalVeiculos] = STATUS_ESTACIONADO;
    numeroVagaVeiculo[*totalVeiculos] = numeroVagas[vagaLivre];

    if (!ocuparVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagas[vagaLivre], placa)) {
        printf("Nao foi possivel ocupar a vaga.\n");
        return;
    }

    (*totalVeiculos)++;
    (*totalVagasOcupadas)++;
    printf("Veiculo cadastrado com sucesso na vaga %d.\n", numeroVagaVeiculo[*totalVeiculos - 1]);
}

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
) {
    char placa[TAM_PLACA];
    int indice;
    int hora;
    int minuto;
    int vagaLivre;

    printf("Placa: ");
    scanf(" %7s", placa);

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veiculo nao cadastrado.\n");
        return;
    }

    if (statusVeiculo[indice] == STATUS_ESTACIONADO) {
        printf("Veiculo ja esta estacionado.\n");
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

    entradaHora[indice] = hora;
    entradaMinuto[indice] = minuto;
    saidaHora[indice] = 0;
    saidaMinuto[indice] = 0;
    statusVeiculo[indice] = STATUS_ESTACIONADO;
    numeroVagaVeiculo[indice] = numeroVagas[vagaLivre];

    if (!ocuparVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagas[vagaLivre], placa)) {
        printf("Nao foi possivel ocupar a vaga.\n");
        return;
    }

    (*totalVagasOcupadas)++;
    printf("Entrada registrada com sucesso na vaga %d.\n", numeroVagaVeiculo[indice]);
}

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
) {
    char placa[TAM_PLACA];
    int indice;
    int hora;
    int minuto;

    printf("Placa: ");
    scanf(" %7s", placa);

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veiculo nao cadastrado.\n");
        return;
    }

    if (statusVeiculo[indice] == STATUS_SAIU) {
        printf("Veiculo ja foi retirado.\n");
        return;
    }

    printf("Hora de saida: ");
    scanf("%d", &hora);
    printf("Minuto de saida: ");
    scanf("%d", &minuto);

    if (!validarHorario(hora, minuto)) {
        printf("Horario invalido.\n");
        return;
    }

    if (hora < entradaHora[indice] || (hora == entradaHora[indice] && minuto < entradaMinuto[indice])) {
        printf("Horario de saida invalido.\n");
        return;
    }

    saidaHora[indice] = hora;
    saidaMinuto[indice] = minuto;
    statusVeiculo[indice] = STATUS_SAIU;

    liberarVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagaVeiculo[indice]);
    numeroVagaVeiculo[indice] = 0;

    if (*totalVagasOcupadas > 0) {
        (*totalVagasOcupadas)--;
    }

    printf("Saida registrada com sucesso.\n");
}

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
) {
    char placa[TAM_PLACA];
    int indice;

    printf("Placa: ");
    scanf(" %7s", placa);

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    printf("\nPlaca: %s\n", placas[indice]);
    printf("Modelo: %s\n", modelos[indice]);
    printf("Tipo: %d\n", tipos[indice]);
    printf("Entrada: %02d:%02d\n", entradaHora[indice], entradaMinuto[indice]);
    printf("Saida: %02d:%02d\n", saidaHora[indice], saidaMinuto[indice]);
    printf("Status: %s\n", statusVeiculo[indice] == STATUS_ESTACIONADO ? "Estacionado" : "Saiu");
    printf("Vaga: %d\n", numeroVagaVeiculo[indice]);

    if (statusVeiculo[indice] == STATUS_SAIU && saidaHora[indice] >= 0 && saidaMinuto[indice] >= 0) {
        int tempo = calcularTempoEstacionado(entradaHora[indice], entradaMinuto[indice], saidaHora[indice], saidaMinuto[indice]);
        float valor = calcularValorEstadia(tempo, tipos[indice]);

        printf("Tempo estacionado: %d minutos\n", tempo);
        printf("Valor estimado: R$ %.2f\n", valor);
    }
}

void atualizarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int totalVeiculos
) {
    char placa[TAM_PLACA];
    int indice;
    char novoModelo[TAM_MODELO];
    int novoTipo;

    printf("Placa: ");
    scanf(" %7s", placa);

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    printf("Novo modelo: ");
    scanf(" %49s", novoModelo);
    printf("Novo tipo (1-Carro, 2-Moto, 3-PCD, 4-Eletrico): ");
    scanf("%d", &novoTipo);

    if (!validarTipoVeiculo(novoTipo)) {
        printf("Tipo invalido.\n");
        return;
    }

    strcpy(modelos[indice], novoModelo);
    tipos[indice] = novoTipo;
    printf("Dados atualizados com sucesso.\n");
}

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
) {
    char placa[TAM_PLACA];
    int indice;
    int i;

    printf("Placa: ");
    scanf(" %7s", placa);

    indice = buscarVeiculoPorPlaca(placas, *totalVeiculos, placa);
    if (indice == -1) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    if (statusVeiculo[indice] == STATUS_ESTACIONADO) {
        liberarVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagaVeiculo[indice]);
        if (*totalVagasOcupadas > 0) {
            (*totalVagasOcupadas)--;
        }
    }

    for (i = indice; i < (*totalVeiculos) - 1; i++) {
        strcpy(placas[i], placas[i + 1]);
        strcpy(modelos[i], modelos[i + 1]);
        tipos[i] = tipos[i + 1];
        entradaHora[i] = entradaHora[i + 1];
        entradaMinuto[i] = entradaMinuto[i + 1];
        saidaHora[i] = saidaHora[i + 1];
        saidaMinuto[i] = saidaMinuto[i + 1];
        statusVeiculo[i] = statusVeiculo[i + 1];
        numeroVagaVeiculo[i] = numeroVagaVeiculo[i + 1];
    }

    (*totalVeiculos)--;
    printf("Veiculo excluido com sucesso.\n");
}

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
) {
    int i;

    printf("\nVagas livres: %d\n", contarVagasLivres(statusVagas, MAX_VAGAS));
    printf("Vagas ocupadas: %d\n", totalVagasOcupadas);

    printf("\nVeiculos estacionados:\n");
    for (i = 0; i < totalVeiculos; i++) {
        if (statusVeiculo[i] == STATUS_ESTACIONADO) {
            printf("- %s | %s | Vaga %d\n", placas[i], modelos[i], numeroVagaVeiculo[i]);
        }
    }

    printf("\nVagas ocupadas:\n");
    for (i = 0; i < MAX_VAGAS; i++) {
        if (statusVagas[i] == VAGA_OCUPADA) {
            printf("- Vaga %d | Placa %s\n", numeroVagas[i], placasVagas[i]);
        }
    }
}
