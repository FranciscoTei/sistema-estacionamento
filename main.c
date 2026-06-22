#include <stdio.h>
#include <string.h>

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
void executarOpcaoMenu(
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
    int *totalVagasOcupadas,
    int opcao
);

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
);
int atualizarVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos,
    const char *placa
);
int excluirVeiculo(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int entradaHora[MAX_VEICULOS],
    int entradaMinuto[MAX_VEICULOS],
    int saidaHora[MAX_VEICULOS],
    int saidaMinuto[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int *totalVeiculos,
    const char *placa
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
int validarVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    int totalVagas,
    int numeroVaga
);
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
int liberarVaga(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas,
    int numeroVaga
);
int contarVagasLivres(
    int statusVagas[MAX_VAGAS],
    int totalVagas
);

void relatorioVeiculosAtivos(
    char placas[MAX_VEICULOS][TAM_PLACA],
    char modelos[MAX_VEICULOS][TAM_MODELO],
    int tipos[MAX_VEICULOS],
    int statusVeiculo[MAX_VEICULOS],
    int numeroVagaVeiculo[MAX_VEICULOS],
    int totalVeiculos
);
void relatorioVagasOcupadas(
    int statusVagas[MAX_VAGAS],
    int numeroVagas[MAX_VAGAS],
    char placasVagas[MAX_VAGAS][TAM_PLACA],
    int totalVagas
);
int calcularTempoEstacionado(
    int entradaHora,
    int entradaMinuto,
    int saidaHora,
    int saidaMinuto
);
float calcularValorEstadia(int tempoMinutos, int tipoVeiculo);

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

    (void)placas;
    (void)modelos;
    (void)tipos;
    (void)entradaHora;
    (void)entradaMinuto;
    (void)saidaHora;
    (void)saidaMinuto;
    (void)statusVeiculo;
    (void)numeroVagaVeiculo;
    (void)placasVagas;
    (void)statusVagas;
    (void)numeroVagas;
    (void)totalVeiculos;
    (void)totalVagasOcupadas;

    return 0;
}
