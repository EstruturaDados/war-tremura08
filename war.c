#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===============================================
// 1. DEFINIÇÃO DA ESTRUTURA
// ===============================================
struct territorio {
    char nome[30];
    char cor[10]; // Cor do exército que controla o território (o "dono")
    int tropas;
};
typedef struct territorio Territorio;

// ===============================================
// 2. PROTÓTIPOS DAS FUNÇÕES
// ===============================================
void cadastrarTerritorios(Territorio* mapa, int total);
void exibirTerritorios(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
int rolarDado();
void simularBatalha(Territorio* mapa, int total);
void liberarMemoria(Territorio* mapa);

// ===============================================
// 3. FUNÇÃO PRINCIPAL (MAIN)
// ===============================================
int main() {
    // Inicializa a semente para a função rand(), garantindo aleatoriedade nos dados
    srand(time(NULL)); 

    int totalTerritorios;
    Territorio* mapa = NULL; // Ponteiro para o vetor de territórios

    printf("===================================================\n");
    printf("====== Sistema de Simulação de Batalha (WAR) ======\n");
    printf("===================================================\n");

    // Requisito: Alocação dinâmica de memória (tamanho informado pelo usuário)
    printf("Digite o número total de territórios para o mapa: ");
    if (scanf("%d", &totalTerritorios) != 1 || totalTerritorios <= 0) {
        printf("Número inválido. O programa será encerrado.\n");
        return 1;
    }
    
    // Alocação dinâmica de memória para o vetor de struct Territorio
    // Usando calloc para inicializar a memória com zeros
    mapa = (Territorio*)calloc(totalTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória. O programa será encerrado.\n");
        return 1;
    }

    // Etapa 1: Cadastro dos territórios
    cadastrarTerritorios(mapa, totalTerritorios);
    exibirTerritorios(mapa, totalTerritorios);

    // Etapa 2: Simulação de ataques
    simularBatalha(mapa, totalTerritorios);
    
    // Etapa 3: Liberação da memória
    liberarMemoria(mapa);
    
    printf("\nPrograma finalizado. Memória liberada com sucesso.\n");
    
    return 0; 
}

// ===============================================
// 4. IMPLEMENTAÇÃO DAS FUNÇÕES
// ===============================================

/**
 * @brief Cadastra os dados de N territórios dinamicamente alocados.
 * @param mapa Ponteiro para o primeiro elemento do vetor de Territórios.
 * @param total Número total de territórios a cadastrar.
 */
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("\n===========================================\n");
    printf("======== Cadastro de %d Territórios ========\n", total);
    printf("===========================================\n");

    for (int i = 0; i < total; i++) {
        // Uso de ponteiros para acessar e modificar os campos da struct
        Territorio* t = mapa + i; // Aponta para a struct atual no vetor
        
        printf("\nTerritório %d: \n", i + 1);

        printf(" Nome: ");
        scanf("%s", t->nome); // O operador -> (seta) é usado para acessar membros de uma struct através de um ponteiro

        printf(" Cor do Exército (Ex: Azul, Vermelho): ");
        scanf("%s", t->cor);

        printf(" Quantidade de tropas (mínimo 2): ");
        scanf("%d", &(t->tropas));
        
        // Garante pelo menos 2 tropas para poder atacar
        if (t->tropas < 2) t->tropas = 2; 
    }
}

/**
 * @brief Exibe os dados de todos os territórios.
 * @param mapa Ponteiro para o primeiro elemento do vetor de Territórios.
 * @param total Número total de territórios.
 */
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n===========================================\n");
    printf("===== Dados dos Territórios no Mapa =====\n");
    printf("===========================================\n");
    for (int i = 0; i < total; i++) {
        // Uso de ponteiros para exibir os campos da struct
        Territorio* t = mapa + i; 
        
        printf("[%d] %s:\n", i, t->nome); // Exibe o índice para facilitar a seleção
        printf("    Cor do Exército: %s\n", t->cor);
        printf("    Tropas: %d\n", t->tropas);
        printf("----------------------------------------\n");
    }
}

/**
 * @brief Simula a rolagem de um dado de 6 faces.
 * @return Um número inteiro aleatório entre 1 e 6.
 */
int rolarDado() {
    // (rand() % 6) gera um número entre 0 e 5. Somando 1, temos entre 1 e 6.
    return (rand() % 6) + 1; 
}

/**
 * @brief Simula um ataque entre dois territórios.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Requisito: Simulação com dados aleatórios
    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    
    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (Cor: %s) ataca %s (Cor: %s)\n", 
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);

    // Lógica do ataque
    if (dadoAtacante > dadoDefensor) {
        printf("!!! VITÓRIA DO ATACANTE !!!\n");
        
        // Requisito: Atualização dos dados (mudança de dono)
        // O atacante vence: O defensor muda de cor (dono)
        strcpy(defensor->cor, atacante->cor);
        
        // O atacante perde uma tropa, mas transfere metade de suas tropas para o defensor
        int tropasTransferidas = atacante->tropas / 2;

        atacante->tropas -= 1; // Perde uma tropa no combate
        
        if (atacante->tropas < tropasTransferidas) {
             tropasTransferidas = atacante->tropas;
        }

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas; // O novo dono assume com tropas

        printf("%s conquistou %s. Novo dono: %s\n", atacante->nome, defensor->nome, defensor->cor);
        printf("Tropas transferidas: %d\n", tropasTransferidas);
        
    } else { // Inclui o empate, onde o defensor vence.
        printf("!!! VITÓRIA DO DEFENSOR !!!\n");
        // Requisito: Se o atacante perder, ele perde uma tropa.
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("%s perdeu 1 tropa. Tropas restantes: %d\n", atacante->nome, atacante->tropas);
        } else {
            printf("%s não pode mais perder tropas.\n", atacante->nome);
        }
    }
    printf("---------------------------\n");
}

/**
 * @brief Gerencia o fluxo de simulação de batalha.
 * @param mapa Ponteiro para o vetor de Territórios.
 * @param total Número total de territórios.
 */
void simularBatalha(Territorio* mapa, int total) {
    int idAtacante, idDefensor;
    char continuar;
    
    do {
        // Interface amigável: Exibir lista antes de cada ataque
        exibirTerritorios(mapa, total);
        
        printf("\n===========================================\n");
        printf("=========== INICIAR NOVO ATAQUE ===========\n");
        printf("===========================================\n");
        
        // 1. Escolha do Atacante
        printf("Selecione o ID do Território ATACANTE (0 a %d): ", total - 1);
        if (scanf("%d", &idAtacante) != 1 || idAtacante < 0 || idAtacante >= total) {
            printf("ID inválido. Tente novamente.\n");
            continue;
        }
        
        // Validação: Atacante precisa de pelo menos 2 tropas (1 para atacar, 1 para permanecer)
        if ((mapa + idAtacante)->tropas < 2) {
             printf("Território %s não pode atacar: precisa de pelo menos 2 tropas.\n", (mapa + idAtacante)->nome);
             continue;
        }

        // 2. Escolha do Defensor
        printf("Selecione o ID do Território DEFENSOR (0 a %d): ", total - 1);
        if (scanf("%d", &idDefensor) != 1 || idDefensor < 0 || idDefensor >= total) {
            printf("ID inválido. Tente novamente.\n");
            continue;
        }
        
        // Validação: Não pode ser o mesmo território
        if (idAtacante == idDefensor) {
            printf("Um território não pode atacar a si mesmo. Escolha IDs diferentes.\n");
            continue;
        }
        
        // Requisito Adicional: Validar se o jogador não ataca um território da própria cor
        if (strcmp((mapa + idAtacante)->cor, (mapa + idDefensor)->cor) == 0) {
            printf("Erro: Não é possível atacar um território da mesma cor (%s).\n", (mapa + idAtacante)->cor);
            continue;
        }
        
        // 3. Execução do ataque (uso de ponteiros)
        atacar(mapa + idAtacante, mapa + idDefensor);

        // Requisito: Exibição pós-ataque
        exibirTerritorios(mapa, total);

        // Pergunta se deseja continuar atacando
        printf("Deseja simular outro ataque? (S/N): ");
        // Limpa o buffer para a próxima leitura de char
        while (getchar() != '\n'); 
        scanf("%c", &continuar);

    } while (continuar == 'S' || continuar == 's');
}

/**
 * @brief Libera a memória alocada dinamicamente para o mapa.
 * @param mapa Ponteiro para o vetor de Territórios a ser liberado.
 */
void liberarMemoria(Territorio* mapa) {
    // Requisito: Gerenciamento de memória - liberar o espaço alocado.
    if (mapa != NULL) {
        free(mapa);
    }
}