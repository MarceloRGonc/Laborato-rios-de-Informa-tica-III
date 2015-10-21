
#include "Estatisticas.h"

typedef struct {
    int ano;   /* Ano das publicações */
    int elems; /* Número de publicacões */
    int *pub;  /* Número de Co-Autores */
} Data;

/* Todas as datas presentes no ficheiro */
typedef struct arrayList {
    Data **list;  /* Armazena todas as datas */
    int elems;    /* Número de elementos */
    int size;     /* Tamanho da ArrayList */
} ArrayList;

/* ---------------------- Funções para fazer o parse das datas ---------------------- */

/* Apontador para todas as datas */
static ArrayList *datas;

/* Cria expaço para uma nova ArrayList */
static ArrayList *newArrayList () {
    int i;
	ArrayList *new = (ArrayList *) malloc(sizeof(ArrayList));
	if (!new) mensagem_de_erro(E_MEM);
	new->size = 1;
	new->elems = 0;
	new->list = (Data **) malloc(sizeof(Data *));
    i = new->elems;
    new->list[i] = (Data *)malloc(sizeof(Data));
    new->list[i]->pub = (int *)malloc(sizeof(int));
    new->list[i]->elems=0;
	if (!new->list) mensagem_de_erro(E_MEM);
	return new; 
}

/* Cria espaço para uma nova data */
static int dataAlloc () {
    int i;
    i = datas->elems;
    datas->list = (Data **)realloc(datas->list,(i+1)*sizeof(Data *));
    i = datas->elems;
	datas->list[i] = (Data *)malloc(sizeof(Data));
    datas->list[i]->pub = (int *) malloc(sizeof(int));
    datas->list[i]->elems=0;
    datas->size += 1;
    if (!datas->list[i]) return mensagem_de_erro(E_MEM);
    return 0;
}

/* Aloca espaço para uma nova publicação */
static int pubAlloc (int z) {
    int i = datas->list[z]->elems;
    datas->list[z]->pub = (int *)realloc(datas->list[z]->pub,(i+1)*sizeof(int));
    if (!datas->list[z]->pub) return mensagem_de_erro(E_MEM);
    return 0;
}

/* Encontra uma data e coloca em x o indice onde encontrou */
static int arrayFind(int *data, int *x){
    int i;
    if (datas->elems==0) {
        return 0;
    }
    for (i = 0; i<datas->elems; i++) {
        if (datas->list[i]->ano == *data) {
            *x=i;
            return 1;
        }
    }
    return 0;
}

/* Troca duas datas de posição */
static int arraySwap (int indA, int indB) {
	void *aux;
	if (indA < 0 || indA > datas->elems) return 0;
	else if (indB < 0 || indB > datas->elems) return 0;
	else {
		aux = datas->list[indA];
		datas->list[indA] = datas->list[indB];
		datas->list[indB] = aux;
	}
	return 1;
}

/*Ordena as datas por ordem crescente */
static void arraySort (){
    int i,j;
    
		for (i=datas->elems-1;i >= 0 ;i--) {
            j=i-1;
            
            while (j>=0 && datas->list[i]->ano < datas->list[j]->ano) {
                arraySwap(i,j);
                j--;
            }
        }
}

/* Insere uma data */
static void arrayInsert (int *data, int *autores) {
	int i;
    
    if(arrayFind(data,&i)){
        pubAlloc(i);
        datas->list[i]->pub[datas->list[i]->elems] = *autores;
        datas->list[i]->elems++;
        return;
    }
    
    dataAlloc();
    
    i = datas->elems;

    datas->list[i]->ano = *data;
    
    datas->list[i]->elems += 1;

    datas->list[i]->pub[0] = *autores;
    
    datas->elems += 1;
    
    arraySort();
}

/* Faz o parse das datas */
void parseDatas(char *string, int autores) {
    int ano;
    ano = atoi(string);
    arrayInsert(&ano,&autores);
}

/* Cria as variáveis globais */
void createDatas() {
    datas = newArrayList();
}

/* ----------------------- Funções para resuloção das queries ----------------------- */

/* Retorna o ano da publicação mais antiga; */
int getFirst(){
    int i = datas->list[0]->ano;
    return i;
}

/* Retorna o ano da publicação mais recente; */
int getLast(){
    int i = datas->list[datas->elems-1]->ano;
    return i;
}

/* Retorna o número de datas onde existiram publicações; */
int getArray_Elems(){
    int i = datas->elems;
    return i;
}

/* Retorna o ano que se encontra no indice; */
int getData(int indice){
    int i = datas->list[indice]->ano;
    return i;
}

/* Retorna o número de elementos que se encontra no indice; */
int getDPub(int indice){
    int i = datas->list[indice]->elems;
    return i;
}

/* Retorna o número de autores de uma publicação; */
int get_ElemPub(int indice1,int indice2){
    int i = datas->list[indice1]->pub[indice2];
    return i;
}

/* Dado um intervalo de anos indica o número de publicações; */
int total_Pub(int fst, int lst){
    int i=0, j=0, pub = 0;
    
    if (fst < datas->list[0]->ano) fst = datas->list[0]->ano;
    if (!arrayFind(&fst ,&i)) {
        fst++;
        return total_Pub(fst,lst);
    };
    if (lst > datas->list[datas->elems-1]->ano) lst = datas->list[datas->elems-1]->ano;
    
    if (!arrayFind(&lst ,&j)) {
        lst--;
        return total_Pub(fst,lst);
    };
    
    while (i <= j) {
        pub += getDPub(i);
        i++;
    }
    
    return pub;
}

/* Indica o número de publicações com 1 2 ou 3 autores; */
void get_Pub123(int *a1, int *a2, int *a3, int ano){
    int i, j=0;
    arrayFind(&ano, &j);
    
    for (i=0; i < datas->list[j]->elems; i++) {
        if(datas->list[j]->pub[i] == 1){
            (*a1)++;
        }
        else{
            if(datas->list[j]->pub[i] == 2){
                (*a2)++;
            }
            else{
                if(datas->list[j]->pub[i] == 3){
                    (*a3)++;
                }
            }
        }
    }
}

/* Liberta a informação da memória */
void freeA(){
    int i;
    
    for (i=0; i<datas->elems; i++){
        free(datas->list[i]->pub);
    }
    free(datas);
}
/* ----------------------------------------------------------------------------------- */
