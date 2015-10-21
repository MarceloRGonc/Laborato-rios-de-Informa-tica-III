# ifndef Catalogo_Autores
# define Catalogo_Autores

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Erro.h"

typedef struct treeAut *Tree;

char *strdup(const char *str);


/* Cria as variáveis globais, para utilização posterior */
void arvCreate();

/* Faz o parse de uma publicação;
    @param char **string - autores da publicação a inserir;
    @param int ano - ano da publicação;
    @param int elems - número de autores;
 */
void parseArv(char **string, int ano, int elems);

/* Retorna o número de publicações de um autor num dado ano;
    @param char *nome - nome do autor a consultar;
    @param int ano - ano a consultar;
 */
int getAno_pub(char *nome, int ano);

/* Retorna o número de autores que publicaram a solo */
int get_AutS();

/* Retorna os autores com quem mais publicou;
    @param char *nome - nome do autor a consultar;
    @param int *tam - tamanho do array de retorno;
 */
char **BestsCoaut(char *nome, int *tam);

/* Retorna um array de autores que publicou num certo período de tempo;
    @param int fst - Desde este ano;
    @param int lst - Até este ano;
    @param int *tam - tamanho do array de nomes;
 */
char **regularAut(int fst, int lst, int *tam);

/* Retorna um array os autores que mais publicaram num dado ano;
    @param int ano - Ano a consultar;
    @param int size - Tamanho do array;
 */
char **BestsAut(int ano, int size);

/* Retorna o número de publicações;
    @param int indice - indice do ano a consultar;
 */
int getPub(int indice);

/* Liberta a informação da memória */
void freeInf();

# endif
