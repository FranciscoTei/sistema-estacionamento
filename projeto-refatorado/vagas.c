#include "parking.h"
#include <string.h>

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

int buscarVagaLivre(int statusVagas[MAX_VAGAS], int totalVagas) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (statusVagas[i] == VAGA_LIVRE) {
            return i;
        }
    }

    return -1;
}

int buscarIndiceVagaPorNumero(
    int numeroVagas[MAX_VAGAS],
    int totalVagas,
    int numeroVaga
) {
    int i;

    for (i = 0; i < totalVagas; i++) {
        if (numeroVagas[i] == numeroVaga) {
            return i;
        }
    }

    return -1;
}

int ocuparVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga,
    const char *placa
) {
    int indice = buscarIndiceVagaPorNumero(numeroVagas, totalVagas, numeroVaga);

    if (indice == -1 || statusVagas[indice] == VAGA_OCUPADA) {
        return 0;
    }

    statusVagas[indice] = VAGA_OCUPADA;
    strcpy(placasVagas[indice], placa);
    return 1;
}

int liberarVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga
) {
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
