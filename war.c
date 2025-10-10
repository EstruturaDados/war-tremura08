#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===============================================
// 1. CONSTANTES E DEFINIÇÕES
// ===============================================
#define MAX_MISSAO_LEN 100 // Tamanho máximo da string de missão

// ===============================================
// 2. ESTRUTURAS
// ===============================================
struct territorio {
    char nome[30];
    char cor[10]; // Cor do exército que controla o território (o "dono")
    int tropas;
};
typedef struct territorio Territorio;

// Uma struct simples para representar o "Jogador" e sua missão.
// Em um jogo real, haveria mais campos, mas aqui simplificamos a essência do desafio.
struct jogador {
    char cor[10]; // A cor do exército que o jogador controla
    char* missao; // Ponteiro para a string de missão, alocada dinamicamente
};
typedef struct jogador Jogador;


// ===============================================
// 3. PROTÓTIPOS DAS FUNÇÕES
// ===============================================

// Funções de Gerenciamento do Mapa
Territorio* alocarMapa(int total);
void cadastrarTerritorios(Territorio* mapa, int total);
void exibirMapa(Territorio* mapa, int total);

// Funções de Gerenciamento da Missão
void atribuirMissao(char* destino, char** missoes, int totalMissoes);
void exibirMissao(char* missao); // Requisito: Passagem da missão por valor (char* é o endereço, mas o valor é a string)
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador); // Verifica se o objetivo foi cumprido

// Funções de Batalha
int rolarDado();
void atacar(Territorio* atacante, Territorio* defensor);
int simularBatalha(Territorio* mapa, int total, Jogador* jogador);

// Funções de Memória
void liberarMemoria(Territorio* mapa, Jogador* jogador);


// ===============================================
// 4. VETOR DE MISSÕES PRÉ-DEFINIDAS
// ===============================================
char* missoesEstrategicas[] = {
    "Missao A: Conquistar 3 Territorios SEGUE.S",
    "Missao B: Eliminar TODAS as tropas da cor Vermelha.",
    "Missao C: Conquistar um total de 8 Territorios.",
    "Missao D: Eliminar TODAS as tropas da cor Azul.",
    "Missao E: Conquistar os Territorios 0, 1 e 2."
};
const int TOTAL_MISSOES = 5;

// ===============================================
// 5. FUNÇÃO PRINCIPAL (MAIN)
// ===============================================
int main() {
    srand(time(NULL)); 

    int totalTerritorios;
    Territorio* mapa = NULL; 
    Jogador jogadorPrincipal;

    printf("===================================================\n");
    printf("====== Sistema de Simulação de Batalha c/ Missoes ======\n");
    printf("===================================================\n");

    // 1. Configuração Inicial e Alocação do Mapa
    printf("Digite o número total de territórios para o mapa: ");
    if (scanf("%d", &totalTerritorios) != 1 || totalTerritorios <= 0) {
        printf("Número inválido. O programa será encerrado.\n");
        return 1;
    }
    mapa = alocarMapa(totalTerritorios);
    if (mapa == NULL) return 1;

    // 2. Cadastro dos Territórios
    cadastrarTerritorios(mapa, totalTerritorios);
    exibirMapa(mapa, totalTerritorios);

    // 3. Configuração do Jogador e Atribuição da Missão
    printf("\nDigite a cor do seu exército (Ex: Verde): ");
    scanf("%s", jogadorPrincipal.cor);
    
    // Alocação dinâmica da string de Missão
    jogadorPrincipal.missao = (char*)malloc(sizeof(char) * MAX_MISSAO_LEN);
    if (jogadorPrincipal.missao == NULL) {
        printf("Erro ao alocar memória para a missão.\n");
        liberarMemoria(mapa, &jogadorPrincipal);
        return 1;
    }
    
    // Atribuição e Exibição da Missão
    atribuirMissao(jogadorPrincipal.missao, missoesEstrategicas, TOTAL_MISSOES);
    printf("\n>>> Sua missão para o jogo foi atribuída: <<<\n");
    exibirMissao(jogadorPrincipal.missao); // Exibição no início

    // 4. Simulação da Batalha e Verificação da Missão
    int vencedor = simularBatalha(mapa, totalTerritorios, &jogadorPrincipal);

    if (vencedor) {
        printf("\n\n####################################################\n");
        printf("!!! PARABÉNS! O Jogador da cor %s CUMPRIU SUA MISSÃO e VENCEU O JOGO!!!\n", jogadorPrincipal.cor);
        printf("####################################################\n");
    } else {
        printf("\n\nSimulação de batalha encerrada sem cumprimento da missão.\n");
    }
    
    // 5. Liberação da Memória
    liberarMemoria(mapa, &jogadorPrincipal);
    
    printf("\nPrograma finalizado. Memória liberada com sucesso.\n");
    
    return 0; 
}


// ===============================================
// 6. IMPLEMENTAÇÃO DAS FUNÇÕES
// ===============================================

/**
 * @brief Aloca dinamicamente a memória para o vetor de Territórios.
 * @param total Número total de territórios.
 * @return Ponteiro para o vetor alocado, ou NULL em caso de erro.
 */
Territorio* alocarMapa(int total) {
    Territorio* mapa = (Territorio*)calloc(total, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
    }
    return mapa;
}

/**
 * @brief Cadastra os dados de N territórios.
 * @param mapa Ponteiro para o primeiro elemento do vetor de Territórios.
 * @param total Número total de territórios a cadastrar.
 */
void cadastrarTerritorios(Territorio* mapa, int total) {
    // ... (Lógica de cadastro idêntica à anterior) ...
    printf("\n===========================================\n");
    printf("======== Cadastro de %d Territórios ========\n", total);
    printf("===========================================\n");

    for (int i = 0; i < total; i++) {
        Territorio* t = mapa + i; 
        
        printf("\nTerritório %d: \n", i + 1);

        printf(" Nome: ");
        scanf("%s", t->nome); 

        printf(" Cor do Exército (Ex: Azul, Vermelho, Verde): ");
        scanf("%s", t->cor);

        printf(" Quantidade de tropas (mínimo 2): ");
        scanf("%d", &(t->tropas));
        
        if (t->tropas < 2) t->tropas = 2; 
    }
}

/**
 * @brief Exibe os dados de todos os territórios.
 * @param mapa Ponteiro para o primeiro elemento do vetor de Territórios.
 * @param total Número total de territórios.
 */
void exibirMapa(Territorio* mapa, int total) {
    printf("\n===========================================\n");
    printf("===== Dados dos Territórios no Mapa =====\n");
    printf("===========================================\n");
    for (int i = 0; i < total; i++) {
        Territorio* t = mapa + i; 
        
        printf("[%d] %s:\n", i, t->nome); 
        printf("    Cor do Exército: %s\n", t->cor);
        printf("    Tropas: %d\n", t->tropas);
        printf("----------------------------------------\n");
    }
}

/**
 * @brief Sorteia uma missão e a copia para o destino.
 * @param destino Ponteiro de destino (por referência) para a string da missão do jogador.
 * @param missoes Vetor de strings contendo as missões.
 * @param totalMissoes Número total de missões no vetor.
 */
void atribuirMissao(char* destino, char** missoes, int totalMissoes) {
    // Sorteia um índice entre 0 e totalMissoes - 1
    int indiceSorteado = rand() % totalMissoes; 
    
    // Copia a string da missão sorteada para a memória alocada do jogador (destino)
    // Requisito: Uso de strcpy para cópia
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * @brief Exibe a missão do jogador.
 * @param missao Ponteiro para a string da missão (Passagem por valor, pois é apenas para leitura).
 */
void exibirMissao(char* missao) {
    printf("--- Missão: %s ---\n", missao);
}

/**
 * @brief Verifica se a missão do jogador foi cumprida.
 * * Lógica simples implementada para cumprir o requisito:
 * - Se a missão for 'Missao C', verifica se o jogador controla 4 ou mais territórios.
 * - Outras missões retornam 0 (Não Cumprida) por simplicidade inicial.
 * * @param missao A string de missão a ser verificada.
 * @param mapa O vetor de territórios.
 * @param tamanho O número total de territórios.
 * @param corJogador A cor do exército do jogador.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    // Exemplo de lógica de verificação (Simplificada)
    if (strstr(missao, "Missao C") != NULL) {
        // Missao C: Conquistar um total de 8 Territorios (Vamos simular 4 para este mapa menor)
        int territoriosControlados = 0;
        for (int i = 0; i < tamanho; i++) {
            Territorio* t = mapa + i;
            // Verifica se a cor do território é a mesma do jogador
            if (strcmp(t->cor, corJogador) == 0) {
                territoriosControlados++;
            }
        }
        
        // Se o mapa tem, digamos, 5 territórios, 4 controlados é uma boa vitória.
        int objetivo = (tamanho > 3) ? 4 : tamanho; // Mínimo de 4 ou todos
        
        if (territoriosControlados >= objetivo) {
            return 1; // Missão cumprida!
        }
    }
    
    // As outras missões (A, B, D, E) são deixadas como 0 (Não Cumprida) por simplicidade inicial, 
    // conforme solicitado (crie uma lógica simples inicial).
    return 0; 
}


/**
 * @brief Simula a rolagem de um dado de 6 faces.
 * @return Um número inteiro aleatório entre 1 e 6.
 */
int rolarDado() {
    return (rand() % 6) + 1; 
}

/**
 * @brief Simula um ataque entre dois territórios.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // ... (Lógica de ataque idêntica à anterior) ...
    if (atacante->tropas < 2) {
        printf("Ataque cancelado: %s precisa de pelo menos 2 tropas.\n", atacante->nome);
        return;
    }

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    
    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (Cor: %s, Tropas: %d) ataca %s (Cor: %s, Tropas: %d)\n", 
           atacante->nome, atacante->cor, atacante->tropas, defensor->nome, defensor->cor, defensor->tropas);
    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("!!! VITÓRIA DO ATACANTE !!!\n");
        
        // Mudança de dono
        strcpy(defensor->cor, atacante->cor);
        
        // Perde 1 tropa no combate
        atacante->tropas -= 1; 
        
        // Transfere metade das tropas restantes para o território conquistado
        int tropasTransferidas = atacante->tropas / 2;

        if (atacante->tropas < 1) { // Garante que o atacante não fique com 0 tropas
            tropasTransferidas = 0;
        }

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas; 

        printf("%s conquistou %s. Novo dono: %s\n", atacante->nome, defensor->nome, defensor->cor);
        printf("Tropas transferidas: %d\n", tropasTransferidas);
        
    } else { 
        printf("!!! VITÓRIA DO DEFENSOR !!!\n");
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("%s perdeu 1 tropa no ataque. Tropas restantes: %d\n", atacante->nome, atacante->tropas);
        } else {
            printf("%s não pode mais perder tropas.\n", atacante->nome);
        }
    }
    printf("---------------------------\n");
}

/**
 * @brief Gerencia o fluxo de simulação de batalha, com loops e verificação de missão.
 * @param mapa Ponteiro para o vetor de Territórios.
 * @param total Número total de territórios.
 * @param jogador Ponteiro para a struct do jogador principal.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int simularBatalha(Territorio* mapa, int total, Jogador* jogador) {
    int idAtacante, idDefensor;
    char continuar;
    
    do {
        exibirMapa(mapa, total);
        
        printf("\n===========================================\n");
        printf("=========== INICIAR NOVO ATAQUE ===========\n");
        printf("===========================================\n");
        
        printf("Selecione o ID do seu Território ATACANTE (Cor: %s): ", jogador->cor);
        if (scanf("%d", &idAtacante) != 1 || idAtacante < 0 || idAtacante >= total) {
            printf("ID inválido. Tente novamente.\n");
            continue;
        }

        // Validação: Atacante deve ser do jogador
        if (strcmp((mapa + idAtacante)->cor, jogador->cor) != 0) {
            printf("Erro: Você só pode atacar com um território da sua cor (%s).\n", jogador->cor);
            continue;
        }

        // Validação: Atacante precisa de pelo menos 2 tropas
        if ((mapa + idAtacante)->tropas < 2) {
             printf("Território %s não pode atacar: precisa de pelo menos 2 tropas.\n", (mapa + idAtacante)->nome);
             continue;
        }

        printf("Selecione o ID do Território DEFENSOR: ");
        if (scanf("%d", &idDefensor) != 1 || idDefensor < 0 || idDefensor >= total) {
            printf("ID inválido. Tente novamente.\n");
            continue;
        }
        
        if (idAtacante == idDefensor) {
            printf("Um território não pode atacar a si mesmo.\n");
            continue;
        }
        
        // Requisito Adicional: Validar ataque a inimigo
        if (strcmp((mapa + idAtacante)->cor, (mapa + idDefensor)->cor) == 0) {
            printf("Erro: Não é possível atacar um território da própria cor (%s).\n", (mapa + idAtacante)->cor);
            continue;
        }
        
        // Execução do ataque
        atacar(mapa + idAtacante, mapa + idDefensor);

        // Requisito: Verificação da Missão após o ataque
        if (verificarMissao(jogador->missao, mapa, total, jogador->cor)) {
            return 1; // Retorna 1 (Vitória) se a missão foi cumprida
        }

        // Pergunta se deseja continuar atacando
        printf("\nDeseja simular outro ataque? (S/N): ");
        while (getchar() != '\n'); 
        scanf("%c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    return 0; // Retorna 0 (Não Venceu) se o loop terminar
}

/**
 * @brief Libera toda a memória alocada dinamicamente.
 * @param mapa Ponteiro para o vetor de Territórios.
 * @param jogador Ponteiro para a struct do jogador (para liberar a missão).
 */
void liberarMemoria(Territorio* mapa, Jogador* jogador) {
    // 1. Libera a memória da missão do jogador
    if (jogador != NULL && jogador->missao != NULL) {
        free(jogador->missao);
        jogador->missao = NULL;
    }
    
    // 2. Libera a memória do mapa (vetor de territórios)
    if (mapa != NULL) {
        free(mapa);
        mapa = NULL;
    }
}