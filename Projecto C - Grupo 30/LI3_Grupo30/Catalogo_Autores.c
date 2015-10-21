
#include "Catalogo_Autores.h"

/* Fator de Balanceamento */
typedef enum balancefactor { LH , EH , RH } BalanceFactor;

/* Ano de uma publicação */
typedef struct {
    int ano; /* Ano da publicação */
	int pub; /* Numero de publicações nesse ano */
} Ano;

/* Coautor */
typedef struct {
    struct treeAut *autor; /* Coautor com quem publicou */
	int elems; /* Número de vezes que publicou com este autor */
} CoAut;

/* Autor */
typedef struct treeAut {
	char *nome; /* Nome do Autor */
    Ano **anos; /* Array com os anos em que publicou */
    int a_elems; /* Número de anos em que publicou */
	CoAut **coautores; /* Array com os coautores com quem publicou */
    int elems_CoA; /* Número de coautores com quem publicou */
    BalanceFactor bf;
    struct treeAut *left;
    struct treeAut *right;
} Autor;

static Tree insertTree(Tree t, char *e, int *ano, int *cresceu);

static Tree arvAut[27]; /* Array com árvores, posição 0 é para a letra A, a 1 para a B e assim sucessivamente. A última é para caracteres especiais. */

static Autor **coAuts; /* Apontador auxiliar, serve para auxiliar na colocação dos coautores e na resolução de algumas queries */
static int coAuts_elems;/* Número de elementos existentes na variável anterior */

static char **nomes; /* Apontador auxiliar, serve para auxiliar na resolução de algumas queries */
static int *pub;/* Apontador auxiliar, serve para auxiliar na resolução de algumas queries */

/* ---------------- Funções para fazer o parse dos autores e datas ------------------- */

/* Troca duas posições do array anos*/
static int arraySwap (Tree t, int indA, int indB) {
	void *aux;
	
    if (indA < 0 || indA > t->a_elems) return 0;
	
    else if (indB < 0 || indB > t->a_elems) return 0;
	
    else {
		aux = t->anos[indA];
		t->anos[indA] = t->anos[indB];
		t->anos[indB] = aux;
	}
	
    return 1;
}

/* Ordena o array anos */
static void sortAnos(Tree t){
    int i,j;
    
    for (i=t->a_elems;i >= 0 ;i--) {
        j=i-1;
        
        while (j>=0 && t->anos[i]->ano < t->anos[j]->ano) {
            arraySwap(t,i,j);
            j--;
        }
    }
    
    t->a_elems++;
}

/* Aloca memória para um novo elemento no array anos*/
static Ano **allocAno (Tree t, int ano) {
    int i;
    i = 0;
    
    t->anos = (Ano **)malloc(sizeof(Ano *));
    t->anos[i] = (Ano *)malloc(sizeof(Ano));
    t->anos[i]->ano = ano;
    t->anos[i]->pub = 1;
    t->a_elems = 0;
    
    sortAnos(t);
    
    if (!t->anos) mensagem_de_erro(E_MEM);
    
    return t->anos;
}

/* Procura um ano no array */
static int findAno(Tree t, int ano){
    int i;
    
    for (i=0; i < t->a_elems; i++) {
        if (t->anos[i]->ano == ano){
            return i;
        }
    }
    return 0;
    
}

/* Edita dados do array anos */
static int incAno(Tree t, int ano){
    
    int i;
    
    i = findAno(t,ano);
    
    if(i && t->anos[i]->ano == ano){
        t->anos[i]->pub++;
        return 1;
    }
    
    i = t->a_elems;
    t->anos = (Ano **)realloc(t->anos, (i+1)*sizeof(Ano *));
    t->anos[i] = (Ano *)malloc(sizeof(Ano));
    t->anos[i]->ano = ano;
    t->anos[i]->pub = 1;
    
    sortAnos(t);
    
    if (!t->anos) mensagem_de_erro(E_MEM);
    
    return 0;
    
}

/* Roda uma árvore á direita */
static Tree rotateRight(Tree t) {
    Tree aux;
    
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
static Tree rotateLeft(Tree t) {
    Tree aux;
    
    if ((! t)||(! t->right)) {
        mensagem_de_erro(E_ROTATE);
    }
    
    else {
        aux = t->right;
        t->right = aux->left;
        aux->left = t;
        t = aux;
    }
    return t;
}

/* Roda uma árvore para que esta fique balanceada rotação a esquerda */
static Tree balanceRight(Tree t) {
    
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
static Tree balanceLeft(Tree t) {
    
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
static Tree insertRight(Tree t, char *e, int *ano, int *cresceu) {
    t->right = insertTree(t->right,e,ano,cresceu);
    
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
static Tree insertLeft(Tree t, char *e, int *ano, int *cresceu){
    t->left = insertTree(t->left,e,ano,cresceu);
    
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
static Tree insertTree(Tree t, char *e, int *ano, int *cresceu) {
    
    if (t==NULL) {
        t = (Autor *)malloc(sizeof(Autor));
        t->nome = e;
        t->anos = allocAno(t,*ano);
        t->elems_CoA = 0;
        t->coautores = (CoAut **)malloc(sizeof(CoAut*));
        t->right = t->left = NULL;
        t->bf = EH;
        coAuts[coAuts_elems] = t;
        coAuts_elems++;
        *cresceu = 1;
    }
    
    else if (strcmp(e,t->nome)==0) {
        coAuts[coAuts_elems] = t;
        coAuts_elems++;
        incAno(t,*ano);
        return t;
    }
    
    else if (strcmp(e,t->nome)>0)
        t = insertRight(t,e,ano,cresceu);
    else
        t = insertLeft(t,e,ano,cresceu);
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

/* Aloca memória para um novo elemento no array de coautores*/
static void allocCoAut(Autor *t, Autor *new) {
    int i;
    
    for(i=0; i<t->elems_CoA; i++)
		if(t->coautores[i]->autor==new){
			t->coautores[i]->elems++;
            
			return;
		}
    
    t->coautores = (CoAut **)realloc(t->coautores,(t->elems_CoA+1)*sizeof(CoAut*));
    t->coautores[t->elems_CoA] = (CoAut *)malloc(sizeof(CoAut));
    t->coautores[t->elems_CoA]->autor = new;
    t->coautores[t->elems_CoA]->elems = 1;
    t->elems_CoA++;
    
    if (!t->coautores) mensagem_de_erro(E_MEM);
    
}

/* Insere um elemento no array de coautores */
static void insertCoAut(int elems){
    int i, j;
    
    for (j=0; j<elems; j++) {
        
        for (i=0; i<j; i++) {
            allocCoAut(coAuts[j],coAuts[i]);
        }
        
        for (i=j+1; i<elems; i++) {
            allocCoAut(coAuts[j],coAuts[i]);
        }
    }
}

/* Faz o parse de uma publicação */
void parseArv(char **string, int ano, int elems) {
    
    Tree t;
    
    int i=0,j, cresceu=0;
    char *autor;
    
    coAuts = (Autor **)malloc(elems*(sizeof (Autor *)));
    coAuts_elems = 0;
    
    while (i<elems) {
        coAuts[i] = NULL;
        i++;
    }
    
	if (!string) return;
    
    for (j=0; j < elems; j++){

        cresceu=0;

        i = findTree(string[j]);
        
        autor = strdup(string[j]);
        
        t = insertTree(arvAut[i], autor, &ano, &cresceu);
        
        arvAut[i] = t;
        
        t = NULL;
    }
    
    insertCoAut(elems);
    
    free(coAuts);
    
}

/* Cria as variáveis globais, para utilização posterior */
void arvCreate(){
    int i=0;
    
    while (i<27) {
        arvAut[i] = NULL;
        i++;
    }
    
}

/* ----------------------- Funções para resuloção das queries ----------------------- */

/* Procura um autor numa árvore */
static Autor* procuraAVL(Tree t , char *author){
    Autor* autor;
    
    if(t != NULL){
        if(strcmp(author,t->nome)==0) return t;
    	
        else if(strcmp(author,t->nome)>0){
            autor = procuraAVL(t->right,author);
        }
        
        else{
            autor = procuraAVL(t->left,author);
        }
    }
    else {
        return NULL;
    }
    
    return autor;
    
}

/* Percorre AVL e devolve número de Autores que só publicaram a solo */
static int percorreAVL(Tree t){
    int cont = 0;
    
    if(t != NULL){
        if(t->elems_CoA == 0){
            cont = 1 + percorreAVL(t->right) + percorreAVL(t->left);
            }
        
        else cont = percorreAVL(t->right) + percorreAVL(t->left);
    }
    
    return cont;
}

/* Retorna o número de publicações de um autor num dado ano */
int getAno_pub(char *nome, int ano){
    int i, total;
    Tree t;
    Autor *autor;
	i = findTree(nome);
	t = arvAut[i];
    
	autor = procuraAVL(t, nome);
    if (!autor) return 0;
    for (i=0; i<autor->a_elems; i++) {
        if (autor->anos[i]->ano == ano) {
            total = autor->anos[i]->pub;
            return total;
        }
    }
	return 0;
}

/* Retorna o número de autores que publicaram a solo */
int get_AutS(){
    int soma = 0, i;
    
    for (i=0; i<27; i++) {
        soma += percorreAVL(arvAut[i]);
    }
    
    return soma;
}

/* Retorna os autores com quem mais publicou */
char **BestsCoaut(char *nome, int *tam){
    Autor *author;
    int i,j=0, elems, maior=0, flag = 0;
    char **lista;
    Tree t;
	i = findTree(nome);
	t = arvAut[i];
    
    author = procuraAVL(t , nome);
    
    if(!author) return 0;
    
    elems = author->elems_CoA;
    
    coAuts = (Autor **)malloc(elems*(sizeof (Autor *)));
    coAuts_elems = 0;
    
    while (i < elems) {
        coAuts[i] = NULL;
        i++;
    }
    
    for (i=0; i<elems; i++) {
        flag = 0;
        
        if (author->coautores[i]->elems > maior){
            j=0;
            while (j < coAuts_elems) {
                coAuts[i] = NULL;
                j++;
            }
            
            coAuts_elems = 0;
            
            coAuts[coAuts_elems] = author->coautores[i]->autor;
            coAuts_elems++;
            maior = author->coautores[i]->elems;
            flag = 1;
        }
        
        if (author->coautores[i]->elems == maior && !flag){
            coAuts[coAuts_elems] = author->coautores[i]->autor;
            coAuts_elems++;
        }
    }
    
    lista = (char **)malloc((coAuts_elems+1)*(sizeof (char*)));
    
    for (i=0; i<coAuts_elems; i++) {
        lista[i] = strdup(coAuts[i]->nome);
    }
    
    *tam = coAuts_elems;
    
    free(coAuts);
    
    return lista;
}

/* Verifica se um Autor publicou no certo período de anos */
static int findPub(Tree t, int fst, int lst){
    int i;
    
    i = findAno(t,fst);
    if (!i && t->anos[i]->ano != fst){
        return 0;
    }
    
    for (; fst <= lst && i<t->a_elems; i++) {
        if (t->anos[i]->ano != fst) return 0;
        fst++;

    }

    return 1;
}

/* Adiciona ao array de autores que publicou num certo período de tempo ao array */
static void rAutTree(Tree t, int fst, int lst){
    
    if(t != NULL){
        rAutTree(t->left,fst,lst);
        
        if(findPub(t,fst,lst)){
            nomes = (char **)realloc(nomes, (coAuts_elems+1)*sizeof(char *));
            nomes[coAuts_elems] = strdup(t->nome);
            coAuts_elems++;
        }
        rAutTree(t->right,fst,lst);
    }
}

/* Retorna um array de autores que publicou num certo período de tempo */
char **regularAut(int fst, int lst, int *tam){
    int i;
    Tree t;
    coAuts_elems = 0;
    
    for (i=0; i<27; i++) {
        t = arvAut[i];
        rAutTree(t,fst,lst);
    }
    *tam=coAuts_elems+1;
    
    return nomes;
    
}

/* Troca duas posições dos arrays */
static int swapN(int indA, int indB) {
	void *aux; int x;
	
    if (indA < 0 || indA > coAuts_elems) return 0;
	
    else if (indB < 0 || indB > coAuts_elems) return 0;
	
    else {
		x = pub[indA];
		pub[indA] = pub[indB];
		pub[indB] = x;
        
        aux = nomes[indA];
		nomes[indA] = nomes[indB];
		nomes[indB] = aux;
	}
	
    return 1;
}

/* Ordena array de pub */
static void sortPub(){
    int i,j;
    
    for (i = coAuts_elems; i >= 0; i--) {
        j=i-1;
        
        while (j>=0 && pub[i] < pub[j]) {
            swapN(i,j);
            j--;
        }
    }
}

/* Remove um elemento do indice */
static int RemoveFrom (int ind) {
	int i;
	if (ind < 0 || ind > coAuts_elems-1) return 0;
	else {
		for (i=ind;i<(coAuts_elems-1);i++){
			pub[i] = pub[i+1];
            nomes[i] = nomes[i+1];
        }
		coAuts_elems--;
	}
	return 1;
}

/* Verifica os autores que mais publicaram num dado ano */
static void BAutTree(Tree t, int fst, int size){
    int i;
    
    if(t != NULL){
        BAutTree(t->left,fst,size);
        
        if((i=findAno(t,fst))){
            if (coAuts_elems < size) {
                nomes[coAuts_elems] = strdup(t->nome);
                pub[coAuts_elems] = t->anos[i]->pub;
                sortPub();
                coAuts_elems++;
            }
            else{
                if (t->anos[i]->pub > pub[0]){
                    RemoveFrom(0);
                    nomes[coAuts_elems] = strdup(t->nome);
                    pub[coAuts_elems] = t->anos[i]->pub;
                    sortPub();
                    coAuts_elems++;
                }
            }
        }
        BAutTree(t->right,fst,size);
    }
}

/* Retorna um array com os autores que mais publicaram num dado ano */
char **BestsAut(int ano, int size){
    int i;
    Tree t;

    nomes = (char **)malloc((size+1)*sizeof(char *));
    pub = (int *)malloc((size+1)*sizeof(int));
    coAuts_elems = 0;
    
    for (i=0; i<27; i++) {
        t = arvAut[i];
        BAutTree(t,ano,size);
    }
    
    nomes[size] = NULL;
    
    return nomes;
    
}

/* Retorna o número de publicações */
int getPub(int indice){
    return pub[indice];
}

/* Liberta a informação da memória */
static void freeN(){
    int i = 0;
    if (nomes != NULL) {
        while (i<coAuts_elems) {
            free(nomes[i]);
            i++;
        }
        free(nomes);
        free(pub);
    }
}

/* Liberta a informação da memória */
static void freeT(Tree t){
    int i = 0;
    if (t != NULL) {
        freeT(t->left);
        freeT(t->right);
    
        while (i<t->a_elems) {
            free(t->anos[i]);
            i++;
        }

        free(t->anos);
        
        i=0;
        
        while (i<t->elems_CoA) {
            free(t->coautores[i]);
            i++;
        }

        free(t->coautores);
        free(t);
    }
    return;
}

/* Liberta a informação da memória */
void freeInf(){
    Tree t; int i;
    
    for (i=0; i<27; i++) {
        t = arvAut[i];
        if (t != NULL) freeT(t);
    }
    freeN();
}

/* ----------------------------------------------------------------------------------- */

