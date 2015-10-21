# ifndef Indice_Autores
# define Indice_Autores

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Erro.h"

typedef struct treeNode *Node;

char *strdup(const char *str);

/* Faz o parse dos autores;
    @param char *string - autor que queremos inserir;
 */
void parseAutores(char *string);

/* Cria as variáveis globais, para utilização posterior */
void autoresCreate();

/* Retorna a média do cumprimento dos nomes */
int getMedia();

/* Retorna o nome de maior cumprimento */
char *getMaior();

/* Retorna o nome de menor cumprimento */
char *getMenor();

/* Retorna o total de nomes inseridos */
int getNomes();

/* Retorna o nome do autor de um nodo;
    @param Node t - Nodo da árvore onde nos encontramos;
 */
char *getTNome(Node t);

/* Devolve a árvore de determinada letra;
    @param char *letra - letra que queremos consultar;
    @param int *tam - tamanho do array que foi criado;
 */
char **nodeGet(char *letra, int *tam);

/* Liberta a informação da memória */
void freeIA();

# endif
