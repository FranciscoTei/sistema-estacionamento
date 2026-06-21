#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VEICULOS 100
#define MAX_PLACA 10
#define MAX_MODELO 50
#define MAX_PROPRIETARIO 100
#define BUFFER_TAMANHO 128
#define TARIFA_HORA 5.0f

typedef struct {
    char placa[MAX_PLACA];
    char modelo[MAX_MODELO];
    char proprietario[MAX_PROPRIETARIO];
    int vaga;
    int horaEntrada;
    int minutoEntrada;
    int estacionado;
    int ativo;
} Veiculo;

typedef struct {
    Veiculo veiculos[MAX_VEICULOS];
    int totalCadastrados;
    int vagasOcupadas;
} Estacionamento;

void inicializarEstacionamento(Estacionamento *est);
int lerInteiro(const char *mensagem, int min, int max);
void lerTexto(const char *mensagem, char *destino, int tamanho);
void limparTexto(char *texto);
void pausa(void);
void exibirMenuPrincipal(void);
void menuPrincipal(Estacionamento *est);
void opcaoCadastrarVeiculo(Estacionamento *est);
void opcaoRegistrarEntrada(Estacionamento *est);
void opcaoRegistrarSaida(Estacionamento *est);
void opcaoConsultaVeiculo(Estacionamento *est);
void opcaoAtualizarVeiculo(Estacionamento *est);
void opcaoExcluirVeiculo(Estacionamento *est);
void opcaoRelatorios(Estacionamento *est);
int validarPlaca(const char *placa);
int existePlaca(const Estacionamento *est, const char *placa);
int buscarIndicePorPlaca(const Estacionamento *est, const char *placa);
int buscarIndicePorVaga(const Estacionamento *est, int vaga);
int buscarIndiceVazio(const Estacionamento *est);
int buscarVagaLivre(const Estacionamento *est);
int compararStringsIgnorandoCase(const char *a, const char *b);
void cadastrarVeiculo(Estacionamento *est);
void registrarEntrada(Estacionamento *est);
void registrarSaida(Estacionamento *est);
void calcularTempoPermanencia(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida, int *horas, int *minutos);
float calcularValorPagar(int horas, int minutos);
void listarTodosVeiculos(const Estacionamento *est);
void listarVeiculosEstacionados(const Estacionamento *est);
void buscarVeiculoPorPlaca(Estacionamento *est);
void buscarVeiculoPorVaga(Estacionamento *est);
void atualizarVeiculo(Estacionamento *est);
void excluirVeiculo(Estacionamento *est);
void exibirMenuConsulta(void);
void menuConsulta(Estacionamento *est);
void exibirMenuRelatorios(void);
void menuRelatorios(Estacionamento *est);
void mostrarResumoVagas(const Estacionamento *est);
void mostrarRelatorioGeral(const Estacionamento *est);

int main(void) {
    Estacionamento estacionamento;
    inicializarEstacionamento(&estacionamento);
    menuPrincipal(&estacionamento);
    return 0;
}

void inicializarEstacionamento(Estacionamento *est) {
    est->totalCadastrados = 0;
    est->vagasOcupadas = 0;
    for (int i = 0; i < MAX_VEICULOS; i++) {
        est->veiculos[i].ativo = 0;
        est->veiculos[i].estacionado = 0;
        est->veiculos[i].vaga = 0;
        est->veiculos[i].horaEntrada = 0;
        est->veiculos[i].minutoEntrada = 0;
        est->veiculos[i].placa[0] = '\0';
        est->veiculos[i].modelo[0] = '\0';
        est->veiculos[i].proprietario[0] = '\0';
    }
}

int lerInteiro(const char *mensagem, int min, int max) {
    char buffer[BUFFER_TAMANHO];
    long valor;
    char *fim;

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }
        if (buffer[0] == '\n') {
            printf("Entrada vazia. Tente novamente.\n");
            continue;
        }
        valor = strtol(buffer, &fim, 10);
        if (fim == buffer) {
            printf("Entrada inválida. Informe um número inteiro.\n");
            continue;
        }
        while (*fim == ' ' || *fim == '\t') {
            fim++;
        }
        if (*fim != '\n' && *fim != '\0') {
            printf("Entrada inválida. Informe um número inteiro.\n");
            continue;
        }
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo (%d a %d). Tente novamente.\n", min, max);
            continue;
        }
        return (int)valor;
    }
}

void limparTexto(char *texto) {
    char *inicio = texto;
    while (*inicio == ' ' || *inicio == '\t') {
        inicio++;
    }
    char *fim = inicio + strlen(inicio);
    while (fim > inicio && (fim[-1] == ' ' || fim[-1] == '\t')) {
        fim--;
    }
    *fim = '\0';
    if (inicio != texto) {
        memmove(texto, inicio, fim - inicio + 1);
    }
}

void lerTexto(const char *mensagem, char *destino, int tamanho) {
    char buffer[BUFFER_TAMANHO];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }
        size_t len = strcspn(buffer, "\n");
        buffer[len] = '\0';
        limparTexto(buffer);
        if (buffer[0] == '\0') {
            printf("Campo não pode ficar vazio. Tente novamente.\n");
            continue;
        }
        strncpy(destino, buffer, tamanho - 1);
        destino[tamanho - 1] = '\0';
        return;
    }
}
    char buffer[BUFFER_TAMANHO];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }
        size_t len = strcspn(buffer, "\n");
        buffer[len] = '\0';
        if (len == 0) {
            printf("Campo não pode ficar vazio. Tente novamente.\n");
            continue;
        }
        strncpy(destino, buffer, tamanho - 1);
        destino[tamanho - 1] = '\0';
        return;
    }
}

void pausa(void) {
    printf("\nPressione ENTER para voltar ao menu...");
    while (getchar() != '\n') {
        ;
    }
}

int compararStringsIgnorandoCase(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (toupper((unsigned char)*a) != toupper((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

int validarPlaca(const char *placa) {
    size_t len = strlen(placa);
    if (len == 0 || len >= MAX_PLACA) {
        printf("Placa inválida. Use até %d caracteres.\n", MAX_PLACA - 1);
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        char c = placa[i];
        if (!isalnum((unsigned char)c) && c != '-') {
            printf("Placa inválida. Use apenas letras, números ou '-'.\n");
            return 0;
        }
    }
    return 1;
}

int buscarIndicePorPlaca(const Estacionamento *est, const char *placa) {
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (est->veiculos[i].ativo && compararStringsIgnorandoCase(est->veiculos[i].placa, placa)) {
            return i;
        }
    }
    return -1;
}

int buscarIndicePorVaga(const Estacionamento *est, int vaga) {
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (est->veiculos[i].ativo && est->veiculos[i].vaga == vaga) {
            return i;
        }
    }
    return -1;
}

int buscarIndiceVazio(const Estacionamento *est) {
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (!est->veiculos[i].ativo) {
            return i;
        }
    }
    return -1;
}

int existePlaca(const Estacionamento *est, const char *placa) {
    return buscarIndicePorPlaca(est, placa) != -1;
}

void cadastrarVeiculo(Estacionamento *est) {
    int indice = buscarIndiceVazio(est);
    if (indice == -1) {
        printf("Nao e possivel cadastrar mais veiculos. Limite de %d atingido.\n", MAX_VEICULOS);
        return;
    }

    char placa[MAX_PLACA];
    while (1) {
        lerTexto("Placa: ", placa, MAX_PLACA);
        if (!validarPlaca(placa)) {
            continue;
        }
        if (existePlaca(est, placa)) {
            printf("Placa ja cadastrada. Informe outra placa.\n");
            continue;
        }
        break;
    }

    lerTexto("Modelo: ", est->veiculos[indice].modelo, MAX_MODELO);
    lerTexto("Proprietario: ", est->veiculos[indice].proprietario, MAX_PROPRIETARIO);

    strcpy(est->veiculos[indice].placa, placa);
    est->veiculos[indice].vaga = 0;
    est->veiculos[indice].horaEntrada = 0;
    est->veiculos[indice].minutoEntrada = 0;
    est->veiculos[indice].estacionado = 0;
    est->veiculos[indice].ativo = 1;
    est->totalCadastrados++;

    printf("Veiculo cadastrado com sucesso!\n");
}

void listarTodosVeiculos(const Estacionamento *est) {
    int encontrados = 0;
    printf("\nLista de todos os veiculos cadastrados:\n");
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (est->veiculos[i].ativo) {
            encontrados++;
            printf("\nPlaca: %s\n", est->veiculos[i].placa);
            printf("Modelo: %s\n", est->veiculos[i].modelo);
            printf("Proprietario: %s\n", est->veiculos[i].proprietario);
            printf("Estacionado: %s\n", est->veiculos[i].estacionado ? "Sim" : "Nao");
            if (est->veiculos[i].estacionado) {
                printf("Vaga: %d\n", est->veiculos[i].vaga);
                printf("Entrada: %02d:%02d\n", est->veiculos[i].horaEntrada, est->veiculos[i].minutoEntrada);
            }
        }
    }
    if (!encontrados) {
        printf("Nenhum veiculo cadastrado encontrado.\n");
    }
}

void listarVeiculosEstacionados(const Estacionamento *est) {
    int encontrados = 0;
    printf("\nVeiculos atualmente estacionados:\n");
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (est->veiculos[i].ativo && est->veiculos[i].estacionado) {
            encontrados++;
            printf("\nPlaca: %s\n", est->veiculos[i].placa);
            printf("Modelo: %s\n", est->veiculos[i].modelo);
            printf("Proprietario: %s\n", est->veiculos[i].proprietario);
            printf("Vaga: %d\n", est->veiculos[i].vaga);
            printf("Entrada: %02d:%02d\n", est->veiculos[i].horaEntrada, est->veiculos[i].minutoEntrada);
        }
    }
    if (!encontrados) {
        printf("Nenhum veiculo estacionado no momento.\n");
    }
}

void buscarVeiculoPorPlaca(Estacionamento *est) {
    char placa[MAX_PLACA];
    lerTexto("Informe a placa: ", placa, MAX_PLACA);
    int indice = buscarIndicePorPlaca(est, placa);
    if (indice == -1) {
        printf("Veiculo com placa '%s' nao encontrado.\n", placa);
        return;
    }
    printf("\nPlaca: %s\n", est->veiculos[indice].placa);
    printf("Modelo: %s\n", est->veiculos[indice].modelo);
    printf("Proprietario: %s\n", est->veiculos[indice].proprietario);
    printf("Estacionado: %s\n", est->veiculos[indice].estacionado ? "Sim" : "Nao");
    if (est->veiculos[indice].estacionado) {
        printf("Vaga: %d\n", est->veiculos[indice].vaga);
        printf("Entrada: %02d:%02d\n", est->veiculos[indice].horaEntrada, est->veiculos[indice].minutoEntrada);
    }
}

void buscarVeiculoPorVaga(Estacionamento *est) {
    int vaga = lerInteiro("Informe o numero da vaga: ", 1, MAX_VEICULOS);
    int indice = buscarIndicePorVaga(est, vaga);
    if (indice == -1) {
        printf("Nenhum veiculo encontrado na vaga %d.\n", vaga);
        return;
    }
    printf("\nPlaca: %s\n", est->veiculos[indice].placa);
    printf("Modelo: %s\n", est->veiculos[indice].modelo);
    printf("Proprietario: %s\n", est->veiculos[indice].proprietario);
    printf("Estacionado: %s\n", est->veiculos[indice].estacionado ? "Sim" : "Nao");
    printf("Vaga: %d\n", est->veiculos[indice].vaga);
    printf("Entrada: %02d:%02d\n", est->veiculos[indice].horaEntrada, est->veiculos[indice].minutoEntrada);
}

void atualizarVeiculo(Estacionamento *est) {
    char placa[MAX_PLACA];
    lerTexto("Informe a placa do veiculo a atualizar: ", placa, MAX_PLACA);
    int indice = buscarIndicePorPlaca(est, placa);
    if (indice == -1) {
        printf("Veiculo com placa '%s' nao encontrado.\n", placa);
        return;
    }
    printf("\nModelo atual: %s\n", est->veiculos[indice].modelo);
    printf("Proprietario atual: %s\n", est->veiculos[indice].proprietario);
    lerTexto("Novo modelo: ", est->veiculos[indice].modelo, MAX_MODELO);
    lerTexto("Novo proprietario: ", est->veiculos[indice].proprietario, MAX_PROPRIETARIO);
    printf("Dados do veiculo atualizados com sucesso.\n");
}

void excluirVeiculo(Estacionamento *est) {
    char placa[MAX_PLACA];
    lerTexto("Informe a placa do veiculo a excluir: ", placa, MAX_PLACA);
    int indice = buscarIndicePorPlaca(est, placa);
    if (indice == -1) {
        printf("Veiculo com placa '%s' nao encontrado.\n", placa);
        return;
    }
    if (est->veiculos[indice].estacionado) {
        est->veiculos[indice].estacionado = 0;
        est->vagasOcupadas--;
    }
    est->veiculos[indice].ativo = 0;
    est->veiculos[indice].vaga = 0;
    est->veiculos[indice].horaEntrada = 0;
    est->veiculos[indice].minutoEntrada = 0;
    est->veiculos[indice].placa[0] = '\0';
    est->veiculos[indice].modelo[0] = '\0';
    est->veiculos[indice].proprietario[0] = '\0';
    if (est->totalCadastrados > 0) {
        est->totalCadastrados--;
    }
    printf("Veiculo excluido com sucesso.\n");
}

int buscarVagaLivre(const Estacionamento *est) {
    for (int vaga = 1; vaga <= MAX_VEICULOS; vaga++) {
        int ocupado = 0;
        for (int i = 0; i < MAX_VEICULOS; i++) {
            if (est->veiculos[i].ativo && est->veiculos[i].estacionado && est->veiculos[i].vaga == vaga) {
                ocupado = 1;
                break;
            }
        }
        if (!ocupado) {
            return vaga;
        }
    }
    return -1;
}

void calcularTempoPermanencia(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida, int *horas, int *minutos) {
    int totalEntrada = horaEntrada * 60 + minutoEntrada;
    int totalSaida = horaSaida * 60 + minutoSaida;
    int diferenca = totalSaida - totalEntrada;
    if (diferenca < 0) {
        diferenca = 0;
    }
    *horas = diferenca / 60;
    *minutos = diferenca % 60;
}

float calcularValorPagar(int horas, int minutos) {
    int totalMinutos = horas * 60 + minutos;
    if (totalMinutos <= 0) {
        return 0.0f;
    }
    return totalMinutos * (TARIFA_HORA / 60.0f);
}

void registrarEntrada(Estacionamento *est) {
    if (est->vagasOcupadas >= MAX_VEICULOS) {
        printf("Estacionamento lotado. Nao e possivel registrar nova entrada.\n");
        return;
    }

    char placa[MAX_PLACA];
    lerTexto("Informe a placa do veiculo: ", placa, MAX_PLACA);
    int indice = buscarIndicePorPlaca(est, placa);
    if (indice == -1) {
        printf("Veiculo com placa '%s' nao cadastrado.\n", placa);
        return;
    }
    if (est->veiculos[indice].estacionado) {
        printf("Veiculo com placa '%s' ja esta estacionado.\n", placa);
        return;
    }

    int vaga = buscarVagaLivre(est);
    if (vaga == -1) {
        printf("Nao ha vagas disponiveis no momento.\n");
        return;
    }

    int horaEntrada = lerInteiro("Hora de entrada (0-23): ", 0, 23);
    int minutoEntrada = lerInteiro("Minuto de entrada (0-59): ", 0, 59);

    est->veiculos[indice].vaga = vaga;
    est->veiculos[indice].horaEntrada = horaEntrada;
    est->veiculos[indice].minutoEntrada = minutoEntrada;
    est->veiculos[indice].estacionado = 1;
    est->vagasOcupadas++;

    printf("Entrada registrada com sucesso na vaga %d.\n", vaga);
}

void registrarSaida(Estacionamento *est) {
    char placa[MAX_PLACA];
    lerTexto("Informe a placa do veiculo: ", placa, MAX_PLACA);
    int indice = buscarIndicePorPlaca(est, placa);
    if (indice == -1) {
        printf("Veiculo com placa '%s' nao cadastrado.\n", placa);
        return;
    }
    if (!est->veiculos[indice].estacionado) {
        printf("Veiculo com placa '%s' nao esta estacionado.\n", placa);
        return;
    }

    int horaSaida = lerInteiro("Hora de saida (0-23): ", 0, 23);
    int minutoSaida = lerInteiro("Minuto de saida (0-59): ", 0, 59);

    int horaEntrada = est->veiculos[indice].horaEntrada;
    int minutoEntrada = est->veiculos[indice].minutoEntrada;
    int totalEntrada = horaEntrada * 60 + minutoEntrada;
    int totalSaida = horaSaida * 60 + minutoSaida;
    if (totalSaida < totalEntrada) {
        printf("Horario de saida anterior ao de entrada. Operacao cancelada.\n");
        return;
    }

    int horas, minutos;
    calcularTempoPermanencia(horaEntrada, minutoEntrada, horaSaida, minutoSaida, &horas, &minutos);
    float valor = calcularValorPagar(horas, minutos);

    est->veiculos[indice].estacionado = 0;
    est->veiculos[indice].vaga = 0;
    est->veiculos[indice].horaEntrada = 0;
    est->veiculos[indice].minutoEntrada = 0;
    if (est->vagasOcupadas > 0) {
        est->vagasOcupadas--;
    }

    printf("Saida registrada com sucesso. Tempo de permanencia: %d horas e %d minutos.\n", horas, minutos);
    printf("Valor a pagar: R$ %.2f\n", valor);
}

void exibirMenuConsulta(void) {
    printf("\n----- Consulta de Veiculos -----\n");
    printf("1. Buscar por placa\n");
    printf("2. Buscar por vaga\n");
    printf("3. Listar todos os veiculos\n");
    printf("4. Listar veiculos estacionados\n");
    printf("0. Voltar\n");
}

void menuConsulta(Estacionamento *est) {
    int opcao;
    do {
        exibirMenuConsulta();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 4);
        switch (opcao) {
            case 1:
                buscarVeiculoPorPlaca(est);
                break;
            case 2:
                buscarVeiculoPorVaga(est);
                break;
            case 3:
                listarTodosVeiculos(est);
                break;
            case 4:
                listarVeiculosEstacionados(est);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        if (opcao != 0) {
            pausa();
        }
    } while (opcao != 0);
}

void exibirMenuRelatorios(void) {
    printf("\n----- Relatorios e Controle de Vagas -----\n");
    printf("1. Mostrar total de vagas\n");
    printf("2. Mostrar vagas ocupadas\n");
    printf("3. Mostrar vagas livres\n");
    printf("4. Relatorio geral do estacionamento\n");
    printf("0. Voltar\n");
}

void menuRelatorios(Estacionamento *est) {
    int opcao;
    do {
        exibirMenuRelatorios();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 4);
        switch (opcao) {
            case 1:
                mostrarResumoVagas(est);
                break;
            case 2:
                printf("\nVagas ocupadas: %d\n", est->vagasOcupadas);
                break;
            case 3:
                printf("\nVagas livres: %d\n", MAX_VEICULOS - est->vagasOcupadas);
                break;
            case 4:
                mostrarRelatorioGeral(est);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        if (opcao != 0) {
            pausa();
        }
    } while (opcao != 0);
}

void mostrarResumoVagas(const Estacionamento *est) {
    printf("\nResumo de vagas:\n");
    printf("Total de vagas: %d\n", MAX_VEICULOS);
    printf("Vagas ocupadas: %d\n", est->vagasOcupadas);
    printf("Vagas livres: %d\n", MAX_VEICULOS - est->vagasOcupadas);
}

void mostrarRelatorioGeral(const Estacionamento *est) {
    printf("\nRelatorio geral do estacionamento:\n");
    printf("Total de veiculos cadastrados: %d\n", est->totalCadastrados);
    printf("Vagas ocupadas: %d\n", est->vagasOcupadas);
    printf("Vagas livres: %d\n", MAX_VEICULOS - est->vagasOcupadas);
    if (est->vagasOcupadas == 0) {
        printf("Nenhum veiculo estacionado no momento.\n");
        return;
    }
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (est->veiculos[i].ativo && est->veiculos[i].estacionado) {
            printf("\nPlaca: %s\n", est->veiculos[i].placa);
            printf("Modelo: %s\n", est->veiculos[i].modelo);
            printf("Proprietario: %s\n", est->veiculos[i].proprietario);
            printf("Vaga: %d\n", est->veiculos[i].vaga);
            printf("Entrada: %02d:%02d\n", est->veiculos[i].horaEntrada, est->veiculos[i].minutoEntrada);
        }
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
    printf("5. Atualizar dados do veículo\n");
    printf("6. Excluir veículo\n");
    printf("7. Relatórios e controle de vagas\n");
    printf("0. Sair\n");
}

void menuPrincipal(Estacionamento *est) {
    int opcao;
    do {
        exibirMenuPrincipal();
        opcao = lerInteiro("Escolha uma opção: ", 0, 7);
        switch (opcao) {
            case 1:
                opcaoCadastrarVeiculo(est);
                break;
            case 2:
                opcaoRegistrarEntrada(est);
                break;
            case 3:
                opcaoRegistrarSaida(est);
                break;
            case 4:
                opcaoConsultaVeiculo(est);
                break;
            case 5:
                opcaoAtualizarVeiculo(est);
                break;
            case 6:
                opcaoExcluirVeiculo(est);
                break;
            case 7:
                opcaoRelatorios(est);
                break;
            case 0:
                printf("Encerrando o sistema. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

void opcaoCadastrarVeiculo(Estacionamento *est) {
    printf("\n[Cadastro de veículo]\n");
    cadastrarVeiculo(est);
    pausa();
}

void opcaoRegistrarEntrada(Estacionamento *est) {
    printf("\n[Registrar entrada de veículo]\n");
    registrarEntrada(est);
    pausa();
}

void opcaoRegistrarSaida(Estacionamento *est) {
    printf("\n[Registrar saída de veículo]\n");
    registrarSaida(est);
    pausa();
}

void opcaoConsultaVeiculo(Estacionamento *est) {
    menuConsulta(est);
}

void opcaoAtualizarVeiculo(Estacionamento *est) {
    printf("\n[Atualizar dados do veículo]\n");
    atualizarVeiculo(est);
    pausa();
}

void opcaoExcluirVeiculo(Estacionamento *est) {
    printf("\n[Excluir veículo]\n");
    excluirVeiculo(est);
    pausa();
}

void opcaoRelatorios(Estacionamento *est) {
    printf("\n[Relatórios e controle de vagas]\n");
    menuRelatorios(est);
}
