#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define tam_fila 100 // tamanho max. fila

// ED para fila
//------------------------------------------------------
// Tipo fila
typedef struct
{
    int A[tam_fila]; // Simplificacao p/ aplicacao
    int inicio, fim;
} fila;
//------------------------------------------------------

// Operações da fila
//------------------------------------------------------
// Cria uma fila vazia
void Definir(fila *q)
{
    q->fim = 0;
    q->inicio = 0;
    // Obs: ponteiro de início atrasado: aponta para uma posição anterior ao início
}

// Retorna true se fila não contém elementos, false caso contrário
bool Vazia(fila *q)
{
    if (q->inicio == q->fim)
        return true;
    return false;
}

// Retorna true se fila cheia, false caso contrário
bool Cheia(fila *q)
{
    if (q->inicio == ((q->fim + 1) % tam_fila))
        return true;
    return false;
    // Obs: os dois ponteiros diferem de uma posição
}

// Adiciona um elemento no fim da fila q (retorna true se sucesso, false c.c.)
// Note que uma posição da fila nunca será preenchida
bool Inserir(fila *q, int elem)
{
    if (Cheia(q))
        return false;
    q->fim = (q->fim + 1) % tam_fila;
    q->A[q->fim] = elem;
    return true;
}

// Remove um elemento do início da fila q (retorna true se sucesso, false c.c.)
bool Remover(fila *q, int *elem)
{
    if (Vazia(q))
        return false;
    q->inicio = (q->inicio + 1) % tam_fila;
    *elem = q->A[q->inicio];
    return true;
}
//------------------------------------------------------

//------------------------------------------------------
// Principal
// matriz A (de adj.): representa as conexões entre as cidades 0,...,N-1,
// vetor 'dist': dist[i] é a distância da cidade fixada 'c' até cada cidade 'i'
int main()
{
    // Inicialização da matriz com as cidades interconectadas
    fila F;
    FILE *fp;
    int i, j, c = 0;
    int nos = 0;
    int noini, nofim, peso;

    // Exercicio 1
    fp = fopen("digrafo.txt", "r");
    // if (fp == NULL) printf("Erro ao abrir o arquivo.\n"); return 10;
    fscanf(fp, "%d ", &nos);
    int A[nos][nos], dist[nos];
    for (i = 0; i < nos; i++)
        for (j = 0; j < nos; j++)
            A[i][j] = 0;

    while (!feof(fp))
    {
        fscanf(fp, "%d %d %d", &noini, &nofim, &peso);
        A[noini][nofim] = peso;
        A[nofim][noini] = peso;
    }
    fclose(fp);

    for (j = 0; j < nos; j++)
        dist[j] = -1; // Seta dist[j] = inf, todo j

    // Exercicio 2
    printf("qual nó deseja ver o caminho mínimo:");
    for (i = 0; i < nos; i++)
        printf("%d ", i);
    printf("\n");
    scanf("%d", &c);
    printf("\n");
    dist[c] = 0;

    Definir(&F);    // Cria fila
    Inserir(&F, c); // Insere na fila

    // Roda até que todos os nós tenham sido checados pelo critério abaixo:
    // tira da fila uma cidade i, e coloca na fila as cidades vizinhas j com distancias ñ computadas

    while (!Vazia(&F))
    {
        Remover(&F, &i); // Remove da fila (i é o elemento corrente a partir daqui)

        for (j = 0; j < nos; j++)
            if (A[i][j] > 0 && dist[j] == -1) // Se i tem conexao com j E j ainda nao checado
            {
                dist[j] = dist[i] + A[i][j];
                Inserir(&F, j);
            }
    }

    // Imprime vetor de distâncias de 'c' para as demais cidades 'i'
    for (i = 0; i < nos; i++)
        printf("dist[%d]: %d\n", i, dist[i]);

    return (0);
}