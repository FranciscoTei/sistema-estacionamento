#include "parking.h"
#include <string.h>
#include <ctype.h>

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

int calcularTempoEstacionado(
    int entradaHora,
    int entradaMinuto,
    int saidaHora,
    int saidaMinuto
) {
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
