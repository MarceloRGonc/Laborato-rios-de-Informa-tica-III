
#include "Indice_Autores.h"

/* Fator de Balanceamento */
typedef enum balancefactor { LH , EH , RH } BalanceFactor;

/* Nodo da árvore */
typedef struct treeNode {
    BalanceFactor bf;
    char *nome; /* Nome do autor */
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

/* Armazena o nome com maior e menor cumprimento e a soma de todos os cumprimentos*/
typedef struct {
    char *menor;
	char *maior;
	int soma;
} Nome;

static Node insertTree(Node t, char *e, int *cresceu);

static Node autores[27]; /* Array com árvores, posição 0 é para a letra A, a 1 para a B e assim sucessivamente. A última é para caracteres especiais. */

static Nome *nome;

char **nomes;

static int nomes_inseridos; /* Total de nomes inseridos */

/* --------------------- Funções para fazer o parse dos autores ---------------------- */

/* Roda uma árvore á direita */
static Node rotateRight(Node t) {
    Node aux;
    
    if ((! t) || (! t->left)) {
        mensagem_de_erro(E_ROTATE);
    }
    
    else {
        aux = t->left;
        t->left = aux->right;
        aux->right = t;
        t = aux;
    }
    return t;
}

/* Roda uma árvore á esquerda */
static Node rotateLeft(Node t) {
    Node aux;
    
    if ((! t)||(! t->right)) {
        mensagem_de_erro(E_ROTATE);    }
    
    else {
        aux = t->right;
        t->right = aux->left;
        aux->left = t;
        t = aux;
    }
    return t;
}

/* Roda uma árvore para que esta fique balanceada rotação a esquerda */
static Node balanceRight(Node t) {
    
    if (t->right->bf==RH) {
        /* Rotacao simples a esquerda */
        t = rotateLeft(t);
        t->bf = EH;
        t->left->bf = EH;
    }
    
    else {
        /* Dupla rotacao */
        t->right = rotateRight(t->right);
        t = rotateLeft(t);
        
        switch (t->bf) {
            case EH:
                t->left->bf = EH;
                t->right->bf = EH;
                break;
            case LH:
                t->left->bf = EH;
                t->right->bf = RH;
                break;
            case RH:
                t->left->bf = LH;
                t->right->bf = EH;
        }
        t->bf = EH;
    }
    return t;
}

/* Roda uma árvore para que esta fique balanceada rotação a direita*/
static Node balanceLeft(Node t) {
    
    if (t->left->bf==LH) {
        /* Rotacao simples a direita */
        t = rotateRight(t);
        t->bf = EH;
        t->right->bf = EH;
    }
    
    else {
        /* Dupla rotacao */
        t->left = rotateLeft(t->left);
        t = rotateRight(t);
        
        switch (t->bf) {
            case EH:
                t->left->bf = EH;
                t->right->bf = EH;
                break;
            case LH:
                t->left->bf = EH;
                t->right->bf = RH;
                break;
            case RH:
                t->left->bf = LH;
                t->right->bf = EH;
        }
        t->bf = EH;
    }
    return t;

}

/* Insere um elemento numa árvore à direita */
static Node insertRight(Node t, char *e, int *cresceu) {
    t->right = insertTree(t->right,e,cresceu);
    
    if (*cresceu)
        switch (t->bf) {
            case LH:
                t->bf = EH;
                *cresceu = 0;
                break;
            case EH:
                t->bf = RH;
                *cresceu = 1;
                break;
            case RH:
                t = balanceRight(t);
                *cresceu = 0;
        }
    return t;
}

/* Insere um elemento numa árvore à esquerda */
static Node insertLeft(Node t, char *e, int *cresceu){
    t->left = insertTree(t->left,e,cresceu);
    
    if (*cresceu)
        switch (t->bf) {
            case LH:
                t = balanceLeft(t);
                *cresceu = 0;
                break;
            case EH:
                t->bf = LH;
                *cresceu = 1;
                break;
            case RH:
                t->bf = EH;
                *cresceu = 0;
        }
    return t;
}

/* Insere um elemento numa árvore AVL */
static Node insertTree(Node t, char *e, int *cresceu) {
    
    if (t==NULL) {
        t = (Node)malloc(sizeof(struct treeNode));
        t->nome = strdup(e);
        t->right = t->left = NULL;
        t->bf = EH;
        *cresceu = 1;
        
        if (!t) {
            mensagem_de_erro(E_MEM);
        }
    }
    
    else if (strcmp(e,t->nome)==0) {
        return t;
    }
    
    else if (strcmp(e,t->nome)>0)
        t = insertRight(t,e,cresceu);
    else
        t = insertLeft(t,e,cresceu);
    return t;
}

/* Encontra a árvore onde pertence determinado nome */
static int findTree(char *string){
    
    int i, j;

    for (i=0, j=65; i<27 && j<91; i++, j++) {
        if (string[0]==j){
            break;
        }
    }
    
    return i;
    
}

/* Faz o parse dos autores */
void parseAutores(char *string) {
    Node t;
    char *copia;
    int i, tamanho; int cresceu=0;
    
	if (!string) return;
    
    copia = strdup (string);
    
    tamanho = strlen(copia);
    
    if (nome->menor == NULL || tamanho < (int)strlen(nome->menor)) nome->menor = strdup(copia);
    
    if (nome->maior == NULL || tamanho > (int)strlen(nome->maior)) nome->maior = strdup(copia);
    
    i = findTree(string);
    
    t = insertTree(autores[i], copia, &cresceu);
    autores[i] = t;
    
    nomes_inseridos++;
    nome->soma += tamanho;
    
}

/* Cria as variáveis globais, para utilização posterior */
void autoresCreate(){
    int i=0;
    
    while (i<27) {
        autores[i] = NULL;
        i++;
    }
    
    nome = (Nome *)malloc(sizeof(Nome));
    
    if (!nome) {
        mensagem_de_erro(E_MEM);
    }
    
    nome->maior = NULL;
    nome->menor = NULL;
    nome->soma = 0;
    
    nomes_inseridos = 0;
    
}

/* ----------------------- Funções para resuloção das queries ----------------------- */

/* Retorna a média do cumprimento dos nomes */
int getMedia() {
    int i;
    i = (int)roundf((float)nome->soma/nomes_inseridos);
    return i;
}

/* Retorna o nome de maior cumprimento */
char *getMaior() {
    char *n = strdup(nome->maior);
    return n;
}

/* Retorna o nome de menor cumprimento */
char *getMenor() {
    char *n = strdup(nome->menor);
    return n;
}

/* Retorna o total de nomes inseridos */
int getNomes() {
    int i;
    i = nomes_inseridos;
    return i;
}

/* Retorna o nome do autor de um nodo */
char *getTNome(Node t){
    char *nome;
    nome = strdup(t->nome);
    return nome;
}

static void **gNomes(Node t, int *tam){
    nomes = (char **)realloc(nomes, (*tam+1)*sizeof(char *));
    
    if(t != NULL){
        gNomes(t->left, tam);
        nomes[*tam] = strdup(t->nome);
        (*tam)++;
        gNomes(t->right, tam);
    }
    return 0;
}

/* Devolve a árvore de determinada letra */
char **nodeGet(char *letra, int *tam){
    int i;
    Node t;
    
    i = findTree(letra);
    t = autores[i];
    
    gNomes(t, tam);
    
    return nomes;
}

/* Liberta a informação da memória */
static void freeT(Node t){
    if (t != NULL) {
        freeT(t->left);
        
        freeT(t->right);
        
        free(t);
    }
    return;
}

/* Liberta a informação da memória */
void freeIA(){
    Node t;
    int i;
    
    for (i=0; i<27; i++) {
        t = autores[i];
        if (t != NULL) freeT(t);
    }
    free(nome);
    free(nomes);
}

/* ----------------------------------------------------------------------------------- */
