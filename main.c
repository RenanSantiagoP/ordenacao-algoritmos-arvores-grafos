#include <stdio.h>
#include <stdlib.h>

#define TAM 1000

//feito por Eva Júlia e Sophia (mostrar vetor, copiar e bubble)
void mostrarVetor(int vetor[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void copiar(int vetor1[], int vetor2[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        vetor2[i] = vetor1[i];
    }
}


void bubbleSort(int vetor[], int tam, int *comp, int *trocas) {
    int i, j, aux;

    for (i = 0; i < tam - 1; i++) {
        for (j = 0; j < tam - 1 - i; j++) {
            (*comp)++;
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                (*trocas)++;
            }
        }
    }
}

// Feito por Marcos, Renan e Felipe (selection, insertion, dividir e quick sort)
void selectionSort(int vetor[], int tam, int *comp, int *trocas) {
    int i, j, menor, aux;

    for (i = 0; i < tam - 1; i++) {
        menor = i;

        for (j = i + 1; j < tam; j++) {
            (*comp)++;
            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
            (*trocas)++;
        }
    }
}

void insertionSort(int vetor[], int tam, int *comp, int *trocas) {
    int i, j, chave;

    for (i = 1; i < tam; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > chave) {
            (*comp)++;
            vetor[j + 1] = vetor[j];
            (*trocas)++;
            j--;
        }

        if (j >= 0) {
            (*comp)++;
        }

        vetor[j + 1] = chave;
    }
}

int dividir(int vetor[], int inicio, int fim, int *comp, int *trocas) {
    int pivo = vetor[fim];
    int i = inicio - 1;
    int j, aux;

    for (j = inicio; j < fim; j++) {
        (*comp)++;
        if (vetor[j] < pivo) {
            i++;
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            (*trocas)++;
        }
    }

    aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = aux;
    (*trocas)++;

    return i + 1;
}

void quick(int vetor[], int inicio, int fim, int *comp, int *trocas) {
    int pivo;

    if (inicio < fim) {
        pivo = dividir(vetor, inicio, fim, comp, trocas);
        quick(vetor, inicio, pivo - 1, comp, trocas);
        quick(vetor, pivo + 1, fim, comp, trocas);
    }
}

void quickSort(int vetor[], int tam, int *comp, int *trocas) {
    quick(vetor, 0, tam - 1, comp, trocas);
}

void juntar(int vetor[], int inicio, int meio, int fim, int *comp, int *trocas) {
    int i, j, k;
    int tam1 = meio - inicio + 1;
    int tam2 = fim - meio;

    int esquerda[tam1];
    int direita[tam2];

    for (i = 0; i < tam1; i++) {
        esquerda[i] = vetor[inicio + i];
    }

    for (j = 0; j < tam2; j++) {
        direita[j] = vetor[meio + 1 + j];
    }

    i = 0;
    j = 0;
    k = inicio;

    while (i < tam1 && j < tam2) {
        (*comp)++;
        if (esquerda[i] <= direita[j]) {
            vetor[k] = esquerda[i];
            i++;
        } else {
            vetor[k] = direita[j];
            j++;
        }
        (*trocas)++;
        k++;
    }

    while (i < tam1) {
        vetor[k] = esquerda[i];
        i++;
        k++;
        (*trocas)++;
    }

    while (j < tam2) {
        vetor[k] = direita[j];
        j++;
        k++;
        (*trocas)++;
    }
}

//feito por mateus e lucas (merge e menu)
void merge(int vetor[], int inicio, int fim, int *comp, int *trocas) {
    int meio;

    if (inicio < fim) {
        meio = (inicio + fim) / 2;
        merge(vetor, inicio, meio, comp, trocas);
        merge(vetor, meio + 1, fim, comp, trocas);
        juntar(vetor, inicio, meio, fim, comp, trocas);
    }
}

void mergeSort(int vetor[], int tam, int *comp, int *trocas) {
    merge(vetor, 0, tam - 1, comp, trocas);
}

int main() {
    int vetor[TAM], copia[TAM];
    int opcao;
    int qtd;
    int num;
    int tamAtual = 0;
    int i;
    int comp, trocas;

    printf("Escolha o algoritmo:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    printf("\nQuantos valores deseja inserir? ");
    scanf("%d", &qtd);

    for (i = 0; i < qtd; i++) {
        comp = 0;
        trocas = 0;

        printf("\nDigite o valor: ");
        scanf("%d", &num);

        vetor[tamAtual] = num;
        tamAtual++;

        copiar(vetor, copia, tamAtual);

        switch (opcao) {
            case 1:
                bubbleSort(copia, tamAtual, &comp, &trocas);
                break;
            case 2:
                selectionSort(copia, tamAtual, &comp, &trocas);
                break;
            case 3:
                insertionSort(copia, tamAtual, &comp, &trocas);
                break;
            case 4:
                quickSort(copia, tamAtual, &comp, &trocas);
                break;
            case 5:
                mergeSort(copia, tamAtual, &comp, &trocas);
                break;
            default:
                printf("Opcao invalida!\n");
                return 1;
        }

        copiar(copia, vetor, tamAtual);

        printf("Estrutura atual: ");
        mostrarVetor(vetor, tamAtual);

        printf("Comparacoes: %d\n", comp);
        printf("Trocas: %d\n", trocas);
    }

    return 0;
}