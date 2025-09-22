#include <stdio.h>
#include <stdlib.h>

// Definição da Estrutura (Struct)
struct territorio {
	char nome[30];
	char cor[10];
	int tropas;
};

// Função principal
int main() {
    struct territorio territorios[5];
    int i;

    printf("===========================================\n");
    printf("=========Cadastro de 5 Territorios=========\n");
    printf("===========================================\n");

    for (i = 0; i < 5; i++) {
        printf("Território %d: \n", i +1);

        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do território: ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");
    }
    
    // --- Exibição dos dados ---
    // Após o cadastro, o programa exibe as informações de todos os territórios.
    // Um novo laço 'for' percorre o vetor 'territorios' do início ao fim.
    printf("===========================================\n");
    printf("=====Dados dos territórios cadastrados=====\n");
    printf("===========================================\n");
    for (i = 0; i < 5; i++) {
        // Acessa e imprime os campos de cada struct do vetor.
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }

    return 0; // Finaliza o programa com sucesso.
}