#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *vetorAuxiliar;
    int tamanhoTotal;
    int qtdElementos;
} EstruturaAuxiliar;

EstruturaAuxiliar vetorPrincipal[TAM];


int ehPosicaoValida(int posicao)
{
    if(posicao < 1 || posicao > TAM)
    {
        return POSICAO_INVALIDA;
    }
    return SUCESSO;
}

void inicializar()
{
    for(int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].vetorAuxiliar = NULL;
        vetorPrincipal[i].tamanhoTotal = 0;
        vetorPrincipal[i].qtdElementos = 0;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;
    int idx = posicao - 1;

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        retorno = POSICAO_INVALIDA;
    }
    else if (tamanho < 1) {
        retorno = TAMANHO_INVALIDO;
    }
    else if (vetorPrincipal[idx].vetorAuxiliar != NULL) {
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
    else {
        vetorPrincipal[idx].vetorAuxiliar = (int *) malloc(tamanho * sizeof(int));

        if (vetorPrincipal[idx].vetorAuxiliar == NULL) {
            retorno = SEM_ESPACO_DE_MEMORIA;
        } else {
            // 6. Deu tudo certo, inicializa os dados
            vetorPrincipal[idx].tamanhoTotal = tamanho;
            vetorPrincipal[idx].qtdElementos = 0;
            retorno = SUCESSO;
        }
    }
    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1;

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {
            temEspaco = (vetorPrincipal[idx].qtdElementos < vetorPrincipal[idx].tamanhoTotal);

            if (temEspaco)
            {
                vetorPrincipal[idx].vetorAuxiliar[vetorPrincipal[idx].qtdElementos] = valor;
                vetorPrincipal[idx].qtdElementos++;
                
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    return retorno;
}
/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temElementos = 0;
    int posicao_invalida = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1;

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {
            temElementos = (vetorPrincipal[idx].qtdElementos > 0);
            if (temElementos)
            {
                vetorPrincipal[idx].qtdElementos--;
                
                retorno = SUCESSO;
            }
            else
            {
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;
    int existeEstruturaAuxiliar = 0;
    int temElementos = 0;
    int posicao_invalida = 0;
    int achou = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1;

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {
            temElementos = (vetorPrincipal[idx].qtdElementos > 0);

            if (temElementos)
            {
                int i, achouIdx = -1;

                for (i = 0; i < vetorPrincipal[idx].qtdElementos; i++)
                {
                    if (vetorPrincipal[idx].vetorAuxiliar[i] == valor)
                    {
                        achou = 1;
                        achouIdx = i;
                        break; 
                    }
                }

                if (achou)
                {
                    for (i = achouIdx; i < vetorPrincipal[idx].qtdElementos - 1; i++)
                    {
                        vetorPrincipal[idx].vetorAuxiliar[i] = vetorPrincipal[idx].vetorAuxiliar[i + 1];
                    }

                    vetorPrincipal[idx].qtdElementos--;
                    
                    retorno = SUCESSO;
                }
                else
                {
                    retorno = NUMERO_INEXISTENTE;
                }
            }
            else
            {
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    return retorno;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int posicao_invalida = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1; 

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {
            for (int i = 0; i < vetorPrincipal[idx].qtdElementos; i++)
            {
                vetorAux[i] = vetorPrincipal[idx].vetorAuxiliar[i];
            }

            retorno = SUCESSO;
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int posicao_invalida = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1; 

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {
            for (int i = 0; i < vetorPrincipal[idx].qtdElementos; i++)
            {
                vetorAux[i] = vetorPrincipal[idx].vetorAuxiliar[i];
            }

            int n = vetorPrincipal[idx].qtdElementos;
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - i - 1; j++)
                {
                    if (vetorAux[j] > vetorAux[j + 1])
                    {
                        int temp = vetorAux[j];
                        vetorAux[j] = vetorAux[j + 1];
                        vetorAux[j + 1] = temp;
                    }
                }
            }

            retorno = SUCESSO;
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int todasVazias = 0;
    int totalElementos = 0;

    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].vetorAuxiliar != NULL)
        {
            totalElementos += vetorPrincipal[i].qtdElementos;
        }
    }

    todasVazias = (totalElementos == 0);

    if (todasVazias)
    {
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    else
    {
        int k = 0;

        for (int i = 0; i < TAM; i++)
        {
            if (vetorPrincipal[i].vetorAuxiliar != NULL)
            {
                for (int j = 0; j < vetorPrincipal[i].qtdElementos; j++)
                {
                    vetorAux[k] = vetorPrincipal[i].vetorAuxiliar[j];
                    k++;
                }
            }
        }

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int todasVazias = 0;
    int totalElementos = 0;

    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].vetorAuxiliar != NULL)
        {
            totalElementos += vetorPrincipal[i].qtdElementos;
        }
    }

    todasVazias = (totalElementos == 0);

    if (todasVazias)
    {
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    else
    {
        int k = 0;

        for (int i = 0; i < TAM; i++)
        {
            if (vetorPrincipal[i].vetorAuxiliar != NULL)
            {
                for (int j = 0; j < vetorPrincipal[i].qtdElementos; j++)
                {
                    vetorAux[k] = vetorPrincipal[i].vetorAuxiliar[j];
                    k++;
                }
            }
        }

        for (int i = 0; i < k - 1; i++)
        {
            for (int j = 0; j < k - i - 1; j++)
            {
                if (vetorAux[j] > vetorAux[j + 1])
                {
                    int temp = vetorAux[j];
                    vetorAux[j] = vetorAux[j + 1];
                    vetorAux[j + 1] = temp;
                }
            }
        }

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int novoTamanhoValido = 0;
    int posicao_invalida = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1;

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {

            int tamanhoFinal = vetorPrincipal[idx].tamanhoTotal + novoTamanho;

            novoTamanhoValido = (tamanhoFinal >= 1);

            if (novoTamanhoValido)
            {
                int *novoVetor = (int *) realloc(vetorPrincipal[idx].vetorAuxiliar, tamanhoFinal * sizeof(int));

                if (novoVetor == NULL)
                {
                    retorno = SEM_ESPACO_DE_MEMORIA;
                }
                else
                {
                    vetorPrincipal[idx].vetorAuxiliar = novoVetor;
                    vetorPrincipal[idx].tamanhoTotal = tamanhoFinal;

                    if (vetorPrincipal[idx].qtdElementos > tamanhoFinal)
                    {
                        vetorPrincipal[idx].qtdElementos = tamanhoFinal;
                    }

                    retorno = SUCESSO;
                }
            }
            else
            {
                retorno = NOVO_TAMANHO_INVALIDO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int posicao_invalida = 0;

    posicao_invalida = (ehPosicaoValida(posicao) == POSICAO_INVALIDA);

    if (posicao_invalida)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        int idx = posicao - 1;

        existeEstruturaAuxiliar = (vetorPrincipal[idx].vetorAuxiliar != NULL);

        if (existeEstruturaAuxiliar)
        {
            if (vetorPrincipal[idx].qtdElementos > 0)
            {
                retorno = vetorPrincipal[idx].qtdElementos;
            }
            else
            {
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetorAuxiliar != NULL) {
            totalElementos += vetorPrincipal[i].qtdElementos;
        }
    }

    if (totalElementos == 0)
        return NULL;

    No *cabecote = (No *) malloc(sizeof(No));
    if (cabecote == NULL)
        return NULL;

    cabecote->conteudo = -1;
    cabecote->prox = NULL;

    No *atual = cabecote;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetorAuxiliar != NULL) {
            for (int j = 0; j < vetorPrincipal[i].qtdElementos; j++) {
                No *novo = (No *) malloc(sizeof(No));
                if (novo != NULL) {
                    novo->conteudo = vetorPrincipal[i].vetorAuxiliar[j];
                    novo->prox = NULL;
                    atual->prox = novo;
                    atual = novo;
                }
            }
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL)
        return;

    No *atual = inicio->prox;
    int k = 0;
    while (atual != NULL) {
        vetorAux[k++] = atual->conteudo;
        atual = atual->prox;
    }
}


/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
    if (inicio == NULL || *inicio == NULL)
        return;

    No *atual = *inicio;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    *inicio = NULL;
}


/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetorAuxiliar != NULL) {
            free(vetorPrincipal[i].vetorAuxiliar);
            vetorPrincipal[i].vetorAuxiliar = NULL;
        }
        vetorPrincipal[i].tamanhoTotal = 0;
        vetorPrincipal[i].qtdElementos = 0;
    }
}

