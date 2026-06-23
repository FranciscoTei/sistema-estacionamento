#include "parking.h"
#include <string.h>
#include <ctype.h>

void exibirMenuPrincipal(void) {
    printf("\n==============================\n");
    printf(" Sistema de Estacionamento\n");
    printf("==============================\n");
    printf("1. Cadastro de veiculo\n");
    printf("2. Registrar entrada de veiculo\n");
    printf("3. Registrar saida de veiculo\n");
    printf("4. Consulta de veiculo\n");
    printf("5. Listar veiculos\n");
    printf("0. Sair\n");
    printf("Opcao: ");
}

int lerOpcaoMenu(void) {
    int opcao;

    if (scanf("%d", &opcao) != 1) {
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
    } else if (tipoVeiculo == TIPO_PCD) {
        valorHora = 0.0f;
    } else if (tipoVeiculo == TIPO_ELETRICO) {
        valorHora = 7.0f;
    } else {
        valorHora = 10.0f;
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
    int totalVeiculos
) {
    char placa[TAM_PLACA];
    char modelo[TAM_MODELO];
    int tipo;
    int vagaLivre;

    if (totalVeiculos >= MAX_VEICULOS) {
        printf("Cadastro cheio.\n");
        return 0;
    }

    printf("Placa: ");
    scanf(" %7s", placa);

    if (!validarPlaca(placa) || buscarVeiculoPorPlaca(placas, totalVeiculos, placa) != -1) {
        printf("Placa invalida ou ja cadastrada.\n");
        return 0;
    }

    printf("Modelo: ");
    scanf(" %49s", modelo);

    printf("Tipo (1-Carro, 2-Moto, 3-PCD, 4-Eletrico): ");
    scanf("%d", &tipo);

    if (!validarTipoVeiculo(tipo)) {
        printf("Tipo invalido.\n");
        return 0;
    }

    vagaLivre = buscarVagaLivre(statusVagas, MAX_VAGAS);
    if (vagaLivre == -1) {
        printf("Nao ha vagas disponiveis.\n");
        return 0;
    }

    strcpy(placas[totalVeiculos], placa);
    strcpy(modelos[totalVeiculos], modelo);
    tipos[totalVeiculos] = tipo;
    entradaHora[totalVeiculos] = 0;
    entradaMinuto[totalVeiculos] = 0;
    saidaHora[totalVeiculos] = 0;
    saidaMinuto[totalVeiculos] = 0;
    statusVeiculo[totalVeiculos] = STATUS_SAIU;
    numeroVagaVeiculo[totalVeiculos] = 0;

    printf("Veiculo cadastrado. Use a entrada para ocupar a vaga %d.\n", numeroVagas[vagaLivre]);
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
    statusVeiculo[indice] = STATUS_ESTACIONADO;
    numeroVagaVeiculo[indice] = numeroVagas[vagaLivre];

    if (ocuparVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagas[vagaLivre], placa)) {
        printf("Entrada registrada na vaga %d.\n", numeroVagaVeiculo[indice]);
    }
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
    int totalVeiculos
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
        printf("Veiculo ja esta fora do estacionamento.\n");
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

    if (numeroVagaVeiculo[indice] > 0) {
        liberarVaga(statusVagas, numeroVagas, placasVagas, MAX_VAGAS, numeroVagaVeiculo[indice]);
    }

    numeroVagaVeiculo[indice] = 0;
    printf("Saida registrada com sucesso.\n");
}

void consultarVeiculo(
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
    int tempo;
    float valor;

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
        printf("Saida: %02d:%02d\n", saidaHora[i], saidaMinuto[i]);
        printf("Status: %s\n", statusVeiculo[i] == STATUS_ESTACIONADO ? "Estacionado" : "Saiu");
        printf("Vaga: %d\n", numeroVagaVeiculo[i]);
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
    int opcao;
    int i;

    for (i = 0; i < MAX_VEICULOS; i++) {
        placas[i][0] = '\0';
        modelos[i][0] = '\0';
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

        switch (opcao) {
            case MENU_CADASTRO:
                if (cadastrarVeiculo(
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
            case MENU_LISTAR:
                listarVeiculos(
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
