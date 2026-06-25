#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_VEICULOS 100
#define MAX_VAGAS 100
#define TAM_PLACA 8

#define TIPO_CARRO 1
#define TIPO_MOTO 2

#define STATUS_ESTACIONADO 1
#define STATUS_SAIU 2

#define VAGA_LIVRE 0
#define VAGA_OCUPADA 1

#define MENU_CADASTRO 1
#define MENU_ENTRADA 2
#define MENU_SAIDA 3
#define MENU_CONSULTA 4
#define MENU_LISTAR 5
#define MENU_SAIR 0

void exibirMenuPrincipal(void);
int lerOpcaoMenu(void);
void limparBufferEntrada(void);
void inicializarVagas(int statusVagas[MAX_VAGAS], int numeroVagas[MAX_VAGAS], char placasVagas[MAX_VAGAS][TAM_PLACA]);
int buscarVeiculoPorPlaca(char placas[MAX_VEICULOS][TAM_PLACA], int totalVeiculos, const char placa[]);
int buscarVagaLivre(int statusVagas[MAX_VAGAS], int totalVagas);
int validarPlaca(const char placa[]);
int validarTipoVeiculo(int tipo);
int validarHorario(int hora, int minuto);
int calcularTempoEstacionado(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida);
float calcularValorEstadia(int tempoMinutos, int tipoVeiculo);
int ocuparVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga,
    const char placa[]
);
int liberarVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga
);
int cadastrarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
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
    int totalVeiculos
);
void registrarEntradaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int totalVeiculos
);
void registrarSaidaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
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
    int totalVeiculos
);
void consultarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
);
void listarVeiculos(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
);

void limparBufferEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void exibirMenuPrincipal(void) {
    printf("\n==============================\n");
    printf(" Sistema de Estacionamento\n");
    printf("==============================\n");
    printf("1. Cadastro de veículo\n");
    printf("2. Registrar entrada de veículo\n");
    printf("3. Registrar saída de veículo\n");
    printf("4. Consulta de veículo\n");
    printf("5. Listar veículos\n");
    printf("0. Sair\n");
    printf("Opção: ");
}

int lerOpcaoMenu(void) {
    int opcao;

    if (scanf("%d", &opcao) != 1) {
        limparBufferEntrada();
        return -1;
    }

    limparBufferEntrada();
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

int buscarVeiculoPorPlaca(char placas[MAX_VEICULOS][TAM_PLACA], int totalVeiculos, const char placa[]) {
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

int validarPlaca(const char placa[]) {
    int i;

    if (placa == NULL || strlen(placa) != 7) {
        return 0;
    }

    for (i = 0; i < 3; i++) {
        if (!((placa[i] >= 'A' && placa[i] <= 'Z') || (placa[i] >= 'a' && placa[i] <= 'z'))) {
            return 0;
        }
    }

    for (i = 3; i < 7; i++) {
        if (placa[i] < '0' || placa[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int validarTipoVeiculo(int tipo) {
    return tipo == TIPO_CARRO || tipo == TIPO_MOTO;
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

int calcularTempoEstacionado(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida) {
    int entradaTotal = horaEntrada * 60 + minutoEntrada;
    int saidaTotal = horaSaida * 60 + minutoSaida;

    if (saidaTotal < entradaTotal) {
        return 0;
    }

    return saidaTotal - entradaTotal;
}

float calcularValorEstadia(int tempoMinutos, int tipoVeiculo) {
    int horas;
    float valorHora;

    if (tempoMinutos <= 0) {
        return 0.0f;
    }

    horas = (tempoMinutos + 59) / 60;

    if (tipoVeiculo == TIPO_MOTO) {
        valorHora = 5.0f;
    } else {
        valorHora = 8.0f;
    }

    return horas * valorHora;
}

int ocuparVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga,
    const char placa[]
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

int liberarVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga
) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (numeroVagas[i] == numeroVaga && statusVagas[i] == VAGA_OCUPADA) {
            statusVagas[i] = VAGA_LIVRE;
            placasVagas[i][0] = '\0';
            return 1;
        }
    }

    return 0;
}

int cadastrarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
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
    int totalVeiculos
) {
    char placa[TAM_PLACA];
    int tipo;
    int vagaLivre;

    if (totalVeiculos >= MAX_VEICULOS) {
        printf("Cadastro cheio.\n");
        return 0;
    }

    printf("Placa (7 caracteres, ex: ABC1234): ");
    scanf(" %s", placa);
    limparBufferEntrada();

    if (!validarPlaca(placa) || buscarVeiculoPorPlaca(placas, totalVeiculos, placa) != -1) {
        printf("Placa inválida ou já cadastrada.\n");
        return 0;
    }

    printf("Tipo (1-Carro, 2-Moto): ");
    scanf("%d", &tipo);
    limparBufferEntrada();

    if (!validarTipoVeiculo(tipo)) {
        printf("Tipo inválido.\n");
        return 0;
    }

    vagaLivre = buscarVagaLivre(statusVagas, MAX_VAGAS);
    if (vagaLivre == -1) {
        printf("Não há vagas disponíveis.\n");
        return 0;
    }

    strcpy(placas[totalVeiculos], placa);
    tipos[totalVeiculos] = tipo;
    entradaHora[totalVeiculos] = 0;
    entradaMinuto[totalVeiculos] = 0;
    saidaHora[totalVeiculos] = 0;
    saidaMinuto[totalVeiculos] = 0;
    statusVeiculo[totalVeiculos] = STATUS_SAIU;
    numeroVagaVeiculo[totalVeiculos] = 0;

    printf("Veículo cadastrado. Use a entrada para ocupar a vaga %d.\n", numeroVagas[vagaLivre]);
    return 1;
}

void registrarEntradaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int totalVeiculos
) {
    char placa[TAM_PLACA];
    int indice;
    int hora;
    int minuto;
    int vagaLivre;

    printf("Placa: ");
    scanf(" %7s", placa);
    limparBufferEntrada();

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veículo não cadastrado.\n");
        return;
    }

    if (statusVeiculo[indice] == STATUS_ESTACIONADO) {
        printf("Veículo já está estacionado.\n");
        return;
    }

    printf("Hora de entrada: ");
    scanf("%d", &hora);
    limparBufferEntrada();
    printf("Minuto de entrada: ");
    scanf("%d", &minuto);
    limparBufferEntrada();

    if (!validarHorario(hora, minuto)) {
        printf("Horário inválido.\n");
        return;
    }

    vagaLivre = buscarVagaLivre(statusVagas, MAX_VAGAS);
    if (vagaLivre == -1) {
        printf("Não há vagas disponíveis.\n");
        return;
    }

    entradaHora[indice] = hora;
    entradaMinuto[indice] = minuto;
    statusVeiculo[indice] = STATUS_ESTACIONADO;
    numeroVagaVeiculo[indice] = numeroVagas[vagaLivre];

    if (ocuparVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagas[vagaLivre], placa)) {
        printf("Entrada registrada na vaga %d.\n", numeroVagaVeiculo[indice]);
    }
}

void registrarSaidaVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
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
    int totalVeiculos
) {
    char placa[TAM_PLACA];
    int indice;
    int hora;
    int minuto;
    int tempo;
    float valor;

    printf("Placa: ");
    scanf(" %7s", placa);
    limparBufferEntrada();

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veículo não cadastrado.\n");
        return;
    }

    if (statusVeiculo[indice] == STATUS_SAIU) {
        printf("Veículo já está fora do estacionamento.\n");
        return;
    }

    printf("Hora de saída: ");
    scanf("%d", &hora);
    limparBufferEntrada();
    printf("Minuto de saída: ");
    scanf("%d", &minuto);
    limparBufferEntrada();

    if (!validarHorario(hora, minuto)) {
        printf("Horário inválido.\n");
        return;
    }

    if (hora < entradaHora[indice] || (hora == entradaHora[indice] && minuto < entradaMinuto[indice])) {
        printf("Horário de saída inválido.\n");
        return;
    }

    saidaHora[indice] = hora;
    saidaMinuto[indice] = minuto;
    statusVeiculo[indice] = STATUS_SAIU;
    tempo = calcularTempoEstacionado(entradaHora[indice], entradaMinuto[indice], saidaHora[indice], saidaMinuto[indice]);
    valor = calcularValorEstadia(tempo, tipos[indice]);

    if (numeroVagaVeiculo[indice] > 0) {
        liberarVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagaVeiculo[indice]);
    }

    numeroVagaVeiculo[indice] = 0;
    printf("Saída registrada com sucesso.\n");
    printf("Tempo estacionado: %d minutos\n", tempo);
    printf("Valor a pagar: R$ %.2f\n", valor);
}

void consultarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
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
    int tempo;
    float valor;

    printf("Placa: ");
    scanf(" %7s", placa);
    limparBufferEntrada();

    indice = buscarVeiculoPorPlaca(placas, totalVeiculos, placa);
    if (indice == -1) {
        printf("Veículo não encontrado.\n");
        return;
    }

    printf("\nPlaca: %s\n", placas[indice]);
    printf("Tipo: %s\n", tipos[indice] == TIPO_MOTO ? "Moto" : "Carro");
    printf("Entrada: %02d:%02d\n", entradaHora[indice], entradaMinuto[indice]);
    printf("Saída: %02d:%02d\n", saidaHora[indice], saidaMinuto[indice]);
    printf("Status: %s\n", statusVeiculo[indice] == STATUS_ESTACIONADO ? "Estacionado" : "Saiu");
    printf("Vaga: %d\n", numeroVagaVeiculo[indice]);

    if (statusVeiculo[indice] == STATUS_SAIU) {
        tempo = calcularTempoEstacionado(
            entradaHora[indice],
            entradaMinuto[indice],
            saidaHora[indice],
            saidaMinuto[indice]
        );
        valor = calcularValorEstadia(tempo, tipos[indice]);
        printf("Tempo estacionado: %d minutos\n", tempo);
        printf("Valor estimado: R$ %.2f\n", valor);
    }
}

void listarVeiculos(
    char placas[MAX_VEICULOS][TAM_PLACA],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
) {
    int i;

    if (totalVeiculos == 0) {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    for (i = 0; i < totalVeiculos; i++) {
        printf("\nVeículo %d\n", i + 1);
        printf("Placa: %s\n", placas[i]);
        printf("Tipo: %s\n", tipos[i] == TIPO_MOTO ? "Moto" : "Carro");
        printf("Entrada: %02d:%02d\n", entradaHora[i], entradaMinuto[i]);
        printf("Saída: %02d:%02d\n", saidaHora[i], saidaMinuto[i]);
        printf("Status: %s\n", statusVeiculo[i] == STATUS_ESTACIONADO ? "Estacionado" : "Saiu");
        printf("Vaga: %d\n", numeroVagaVeiculo[i]);
    }
}

int main(void) {
    setlocale(LC_ALL, ".UTF8");

    char placas[MAX_VEICULOS][TAM_PLACA];
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
    int opcao;
    int i;

    for (i = 0; i < MAX_VEICULOS; i++) {
        placas[i][0] = '\0';
        tipos[i] = 0;
        entradaHora[i] = 0;
        entradaMinuto[i] = 0;
        saidaHora[i] = 0;
        saidaMinuto[i] = 0;
        statusVeiculo[i] = STATUS_SAIU;
        numeroVagaVeiculo[i] = 0;
    }

    inicializarVagas(statusVagas, numeroVagas, placasVagas);

    do {
        exibirMenuPrincipal();
        opcao = lerOpcaoMenu();
        if (opcao == -1) {
            printf("Opcao invalida.\n");
            continue;
        }
        switch (opcao) {
            case MENU_CADASTRO:
                if (cadastrarVeiculo(
                        placas,
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
                        totalVeiculos
                    )) {
                    totalVeiculos++;
                }
                break;
            case MENU_ENTRADA:
                registrarEntradaVeiculo(
                    placas,
                    entradaHora,
                    entradaMinuto,
                    statusVeiculo,
                    numeroVagaVeiculo,
                    placasVagas,
                    statusVagas,
                    numeroVagas,
                    totalVeiculos
                );
                break;
            case MENU_SAIDA:
                registrarSaidaVeiculo(
                    placas,
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
                    totalVeiculos
                );
                break;
            case MENU_CONSULTA:
                consultarVeiculo(
                    placas,
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
            case MENU_LISTAR:
                listarVeiculos(
                    placas,
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
            case MENU_SAIR:
                printf("Encerrando o sistema.\n");
                break;
            default:
                printf("Opção inválida.\n");
                limparBufferEntrada();
                break;
        }
    } while (opcao != MENU_SAIR);

    return 0;
}
