#include "parking.h"
#include <string.h>

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

    strcpy(placas[*totalVeiculos], placa);
    strcpy(modelos[*totalVeiculos], modelo);
    tipos[*totalVeiculos] = tipo;
    entradaHora[*totalVeiculos] = 0;
    entradaMinuto[*totalVeiculos] = 0;
    saidaHora[*totalVeiculos] = 0;
    saidaMinuto[*totalVeiculos] = 0;
    statusVeiculo[*totalVeiculos] = STATUS_SAIU;
    numeroVagaVeiculo[*totalVeiculos] = 0;

    (*totalVeiculos)++;
    printf("Veiculo cadastrado com sucesso.\n");
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

    if (statusVeiculo[indice] == STATUS_SAIU && saidaHora[indice] >= 0 && saidaMinuto[indice] >= 0) {
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
