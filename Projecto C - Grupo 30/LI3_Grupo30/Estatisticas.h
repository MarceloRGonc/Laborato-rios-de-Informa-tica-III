# ifndef Estatisticas
# define Estatisticas

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Erro.h"

typedef struct arrayList *ArrayList_TAD;

/* ---------------------- Funções para fazer o parse das datas ---------------------- */

/* Faz o parse das datas;
    @param char *string - ano da publicação;
    @param int autores - número de autores; */
void parseDatas(char *string, int autores);
/* Cria as variáveis globais; */
void createDatas();

/* ----------------------- Funções para resuloção das queries ----------------------- */

/* Retorna uma cópia do ano da publicação mais antiga; */
int getFirst();
/* Retorna uma cópia do ano da publicação mais recente; */
int getLast();
/* Retorna uma cópia do número de datas onde existiram publicações; */
int getArray_Elems();
/* Retorna uma cópia do ano que se encontra no indice;
    @param int indice - posição do array que se quer aceder; */
int getData(int indice);
/* Retorna uma cópia do número de elementos que se encontra no indice;
    @param int indice - posição do array que se quer aceder; */
int getDPub(int indice);
/* Retorna uma cópia do número de autores de uma publicação;
    @param int indice1 - posição do array da data que se quer aceder;
    @param int indice2 - posição do array de publicações que se quer aceder; */
int get_ElemPub(int indice1,int indice2);
/* Dado um intervalo de anos retorna o número de publicações desse intervalo;
    @param int indice1 - posição do array da data que se quer aceder;
    @param int indice2 - posição do array de publicações que se quer aceder; */
int total_Pub(int fst, int lst);
/* Indica o número de publicações com 1 2 ou 3 autores;
    @param int *a1 - variável onde se guardará o número de publicações com 1 autor;
    @param int *a2 - variável onde se guardará o número de publicações com 2 autor;
    @param int *a3 - variável onde se guardará o número de publicações com 3 autor; */
void get_Pub123(int *a1, int *a2, int *a3, int ano);
/* Liberta a informação da memória */
void freeA();

# endif
