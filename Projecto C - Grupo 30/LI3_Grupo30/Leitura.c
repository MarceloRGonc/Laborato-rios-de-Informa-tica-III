
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "Indice_Autores.h"
#include "Estatisticas.h"
#include "Catalogo_Autores.h"
#include "Erro.h"

char *strsep(char **from, const char *delim);

char *strdup(const char *str);

/* Variável que guarda a informação se o ficheiro foi ou não lido, 0 se não foi 1 se estiver */
static int load;

/* -------------------------------- Funções Auxiliares -------------------------------- */

/* Retira os espaços antes e depois da String */
static char *trim(char *s){
    int i = 0;
    int j = strlen(s)-1;
    int k = 0;
    
    while (isspace(s[i]) && s[i] != '\0')
        i++;
    
    while (isspace(s[j]) && j >= 0)
        j--;
    
    while (i<=j)
        s[k++] = s[i++];
    
    s[k] = '\0';
    
    return s;
}
/* Coloca no final da sequência de cracteres caracter de fim de string */
static void EoS(char *args){
    int tam;
    
    tam = (int)(strlen(args)-1);
    
    if (args[tam] == '\n'){
        args[tam] = '\0';
    }
}
/* Imprime as sequências de nomes divididas em páginas com 15 elementos */
static void imprimeP(char **nome, int nomes){
    int cont=0, contador=0, num=0, i, total;
    char d = 'p'; /* Resposta da pessoa */
    int page = 1;
    float x;
    x = (float)nomes/15;
    total = (int)ceil(x);
    
    while(cont<nomes) {
        
        if(d == 'p'){
            system("clear");
            
            if((nomes-contador) < 15) num = (nomes-contador);
            else num = 15;
            
            for(i=0; i < num; i++, contador++){
                if(nome[contador] == NULL) break;
                printf("%s\n", nome[contador]);
            }
            printf("\nPágina: %d/%d\n", page, total);
            
            if(page >= 1 && page != total)
                printf("\nPara consultar a página seguinte: 'p'  Para saír: 'e' ");
            else if(page==total)
                printf("Saír: 'e' ");
            
            page++;
            cont+=15;
            
            d = getchar();
            getchar(); /* Avançar o \n*/
        }
        else if(d == 'e') break;
        else{
            
            if(page >= 1 && page != total)
                printf("\nPara consultar a página seguinte: 'p'  Para saír: 'e' ");
            else if(page==total)
                printf("Prima qualquer tecla para sair: ");
            
            d = getchar();
            getchar();
        }
    }
    system("clear");
}
/* Imprime as sequências de datas divididas em páginas com 15 elementos */
static void imprimeD(char *args){
    int cont=0, contador=0, num=0, i, total, w;
    char d = 'p'; /* Resposta da pessoa */
    int page = 1;
    float x;
    w = getArray_Elems();
    x = (float)w/15;
    total = (int)ceil(x);
    
    while(cont<w) {
        
        if(d == 'p'){
            system("clear");
            
            if((w-contador) < 15) num = (w-contador);
            else num = 15;
            
            printf ( " ________________________________________ \n" );
            printf ( "|  Data  |     Número de Publicações     |\n" );
            printf ( " ---------------------------------------- \n" );
            
            if (!args) {
                for (i=0; i < num; i++, contador++) {
                    printf ( "|  %d  |          %20d |\n", getData(contador), getDPub(contador));
                    printf ( " ---------------------------------------- \n" );
                }
            }
            else {
                for (i=0; i < num; i++, contador++) {
                    printf ( "|  %d  |          %20d |\n", getData(contador), getAno_pub(args, getData(contador)));
                    printf ( " ---------------------------------------- \n");
                }
            }
            printf("\nPágina: %d/%d\n", page, total);
            
            if(page >= 1 && page != total)
                printf("\nPara consultar a página seguinte: 'p'  Para saír: 'e' ");
            else if(page==total)
                printf("Prima qualquer tecla para sair: ");
            
            page++;
            cont+=15;
            
            d = getchar();
            getchar(); /* Avançar o \n*/
        }
        else if(d == 'e') break;
        else{
            
            if(page >= 1 && page != total)
                printf("\nPara consultar a página seguinte: 'p'  Para saír: 'e' ");
            else if(page==total)
                printf("Saír: 'e' ");
            
            d = getchar();
            getchar();
        }
    }
    system("clear");

}
/* Divide a linha em autores e ano e envia a informação para os módulos */
static int parseLinha(char *string) {
    
    int i=0;
    char *lido = NULL; int ano;
    char *copia, **autores;
    
	if (!string) return 0;
    copia = strdup (string);
    
    autores = (char **)malloc(sizeof(char *));
    autores[i] = (char *)malloc(sizeof(char));
    
    while (((lido = strsep(&copia, ",")) != NULL) && copia != NULL) {
        trim(lido);
        parseAutores(lido);
        autores[i] = lido;
        
        i++;
        
        autores = (char **)realloc(autores,(i+1)*sizeof(char *));
        autores[i] = (char *)malloc(sizeof(char));
        
    }
    
    if (i) {
        trim(lido);
        parseDatas(lido, i);
        ano = atoi(lido);
        parseArv(autores,ano,i);
    }
    
    free(*autores);
    free(copia);
    
    return i;
}

/* ------------------------------------- Queries ------------------------------------- */

/* Lê a informação do ficheiro, linha a linha */
static int loadFile (char *nameFile){
    FILE *fp;
    int linhas = 0;
    char line[1024];
    
    fp = fopen(nameFile,"r");
	if (fp){
        
        autoresCreate();
        createDatas();
        arvCreate();
        
		while ((fgets(line, 1024, fp)) != NULL) {
            if(parseLinha(line)){
                linhas++;
            }
        }
	}
    else{
        mensagem_de_erro(E_NO_FILE);
    }
    fclose (fp);
    
    return linhas;
    
}
/* Faz o load do ficheiro */
static int cmd_load() {
    int linhas = 0;
    clock_t ti, tf;
    double tempo_gasto;
    char args[1024];
    
    if (load) {
        freeInf();
        freeA();
    }
    
    load = 0;
    
    printf("Indique o nome do ficheiro que quer usar: ");
    
    fgets(args, 1024, stdin);
    
    EoS(args);
    
    trim(args);

    ti = clock();

    linhas = loadFile(args);

    tf = clock();

    tempo_gasto = ((double)(tf - ti))/CLOCKS_PER_SEC;

    if (!linhas) return mensagem_de_erro(E_NO_READ);
    
    load = 1;
    printf ("O nome do ficheiro lido é: %s;\n", args);
    printf ("O tempo dispendido a ler o ficheiro: %.2f s\n", tempo_gasto);
    printf ("O numero de linhas lidas foi: %d;\n", linhas);
    printf ("O número de nomes inserido %d;\n", getNomes());
    printf ("O intervalo de datas é [%d, %d];\n", getFirst(), getLast());
    
    return 1;
}
/* Imprime tabela com o Ano e número de publicações para esse ano */
static int cmd_showTab(){
    char *args = NULL;
    if (load){
        
        imprimeD(args);
        
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
}
/* Imprime o número de publicações de um autor em cada ano ou num só ano */
static int cmd_AutPub(int flag){
    int i,ano=0;
    char args[1024];
    char *autor;
    
    if (load){
        printf("Indique o nome do Autor: ");
        
        fgets(args, 1024, stdin);
        
        EoS(args);
        
        autor = strdup(args);
        
        trim(autor);
        
        if (flag) {
            
            printf("Indique o ano que gostaria de consultar: ");
            
            fgets(args, 1024, stdin);

            trim(args);
            ano = atoi(args);
            
            i = getAno_pub(autor, ano);
            
            printf ("O Autor %s fez %d publicações em %d;\n", autor, i, ano);
            
            return 1;
        }
        else{
            
            imprimeD(args);
            
            return 1;
        }
    }
    else{
        return mensagem_de_erro(E_NO_LOAD);
    }
}
/* Imprime o número de autores que publicaram sempre sozinhos */
static int cmd_AutSolo() {
    
    if (load){
        printf("O número de Autores que só publicaram a solo é: %d;\n", get_AutS());
    }
    else return mensagem_de_erro(E_NO_LOAD);
    
    return 1;
}
/* Imprime o nome de todos os autores começados por uma letra */
static int cmd_impAut(){
    char args[3];
    char letra;
    char **t;
    int tam=0;
    
    if (load){
        
        printf("Indique a letra que pretende consultar: \n");
        
        fgets(args, 3, stdin);
        
        EoS(args);
        
        trim(args);
        
        letra = toupper(args[0]);
        
        t = nodeGet(&letra, &tam);
        
        imprimeP(t, tam);
        
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Imprime o número de publicações num intervalo de anos */
static int cmd_totPub(){
    int i,j,tot;
    char args[25];
    char *fst;
    char *lst;
    
    if (load){
        printf("Indique o intervalo de anos que pretende consultar(formato 'ano a ano'): \n");
    
        fgets(args, 25, stdin);
        lst = strdup(args);
        fst = strsep(&lst, "a");
    
        trim(fst); trim(lst);
    
        i = atoi(fst);
        j = atoi(lst);
    
        tot = total_Pub(i,j);
    
        printf("O número total de publicações registadas neste intervalo é: %d;\n", tot);
    
        return 1;
    }
    
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Imprime os co-autores com quem mais publicou um autor */
static int cmd_MCaut(){
    int tam=0;
    char args[1024];
    char *autor;
    char **lista;
    
    if (load){
        printf("Indique o nome do Autor que pretende consultar: \n");
        
        fgets(args, 1024, stdin);
        
        EoS(args);
        
        autor = strdup(args);
        
        trim(autor);
        
        lista = BestsCoaut(autor, &tam);
        
        if(!tam){
            printf("Esse autor não possui nenhum co-autor. \n");
            return 1;
        }
        
        imprimeP(lista, tam);
        
        return 1;
    }
    
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Imprime o nome dos autores que publicaram num intervalo fechado de anos */
static int cmd_RAut(){
    int i,j, aux,tam = 0;
    char args[25];
    char **lista;
    char *fst;
    char *lst;
    
    if (load){
        printf("Indique o intervalo de anos que pretende consultar(formato 'ano a ano'): \n");
        
        fgets(args, 25, stdin);
        EoS(args);
        trim(args);
        lst = strdup(args);
        fst = strsep(&lst, "a");
        
        if (!lst || !strlen(lst)) return mensagem_de_erro(E_INT_INVALIDO);
        
        trim(fst); trim(lst);
        
        i = atoi(fst);
        j = atoi(lst);
        
        if (j<i) {
            aux = j;
            j=i;
            i=aux;
        }
        
        lista = regularAut(i,j, &tam);
        tam--;
        imprimeP(lista, tam);
        
        if  (tam==0) printf("Nenhum autor publicou em todas essas datas;\n");
        return 1;
    }
    
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Imprime uma tabela com o número total de publicações de 1, 2 ou 3 autores */
static int cmd_Tab_10(){
    int ano, a1=0, a2=0, a3=0;
    char args[40], *nameFile;
    FILE *fp;
    
    if (load){
        printf("Indique um nome para o ficheiro: ");
        
        fgets(args, 40, stdin);
        
        EoS(args);
        trim(args);
        nameFile = strdup(args);
        
        printf("Indique o ano a consultar: ");
        
        fgets(args, 40, stdin);
        
        EoS(args);
        trim(args);
        ano = atoi(args);
        
        fp = fopen(nameFile, "w");

        if (!fp) {
            return mensagem_de_erro(E_GRAVAR);
        }
        get_Pub123(&a1,&a2,&a3, ano);
        
        fprintf (fp, " ____________________________ \n");
        fprintf (fp, "| Ano:            %10d |\n", ano);
        fprintf (fp, " ---------------------------- \n");
        fprintf (fp, "| Um autor:       %10d |\n", a1);
        fprintf (fp, " ---------------------------- \n");
        fprintf (fp, "| Dois autores:   %10d |\n", a2);
        fprintf (fp, " ---------------------------- \n");
        fprintf (fp, "| Três autores:   %10d |\n", a3);
        fprintf (fp, " ---------------------------- \n");
        
        fclose(fp);
        
        printf (" __________________________ \n");
        printf ("| Ano:          %10d | \n", ano);
        printf (" -------------------------- \n");
        printf ("| Um autor:     %10d |\n", a1);
        printf (" -------------------------- \n");
        printf ("| Dois autores: %10d |\n", a2);
        printf (" -------------------------- \n");
        printf ("| Três autores: %10d |\n", a3);
        printf (" -------------------------- \n");
        
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
}
/* Cria um ficheiro em formato CSV com a informação das publicações de todos os anos */
static int file_CSV(){
    int i, j, z, cont, flag = 0;
    char args[40], *nameFile;
    char *ext = ".csv";
    FILE *fp;
    
    if (load){
        printf("Indique um nome para o ficheiro CSV(indique sem extensão): ");
        
        fgets(args, 40, stdin);
        
        EoS(args);
        trim(args);

        strcat(args,ext);
        
        nameFile = strdup(args);
        
        fp = fopen(nameFile, "w");

        if (!fp) {
            return mensagem_de_erro(E_GRAVAR);
        }
        
        fprintf (fp, "#Ano  #Autores  #Artigos\n");

        for (i=0; i < getArray_Elems(); i++) {
            cont = flag = 0;
            
            for (j=1; flag < getDPub(i); j++) {
                cont = 0;
                
                for (z=0; z < getDPub(i); z++) {
                    if(j == get_ElemPub(i,z)) {cont++; flag++;}
                }
                
                if (cont) fprintf (fp, "%d  %d  %d\n", getData(i), j, cont);
            }
        }
        
        fclose(fp);
        
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
}
/* Imprime os autores que mais publicaram num dado um ano */
static int cmd_MPub(){
    char args[40];
    int ano, tam,i;
    char **lista;
    
    if (load){
        
        printf("Indique o ano a consultar: ");
    
        fgets(args, 40, stdin);
        EoS(args);
        trim(args);
        ano = atoi(args);
       
        if(ano < getFirst() || ano > getLast()){
            printf("Nenhum autor publicou nesse ano.\n");
            return 1;
        }
        
        printf("Indique o tamanho da lista que deseja: ");
        
        fgets(args, 40, stdin);
        EoS(args);
        trim(args);
        tam = atoi(args);
        
        lista = BestsAut(ano, tam);
        
        for (i=0; lista[i] != NULL; i++) {
            printf("%s - %d;\n", lista[i], getPub(i));
        }
        if(!i) printf("Nenhum autor publicou nessa data;");
        
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Imprime a percentagem de publicações de um autor num dado ano */
static int cmd_Stats(){
    char args[40];
    int ano;
    char *autor;
    float f;
    
    if (load){
        
        printf("Indique o nome do autor a consultar: ");
        
        fgets(args, 40, stdin);
        EoS(args);
        trim(args);
        autor = strdup(args);
        
        printf("Indique o ano que deseja consultar: ");
        
        fgets(args, 40, stdin);
        EoS(args);
        trim(args);
        ano = atoi(args);
        
        if(ano < getFirst() || ano > getLast()){
            printf("Nenhum autor publicou nesse ano.\n");
            return 1;
        }
        
        f = ((float)getAno_pub(autor,ano))/((float)total_Pub(ano,ano));
        printf("A percentagem de publicações deste autor nesse ano é: %.2f\n", f*100);
            
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Imprime o autor com o maior e menor nome e a média do comprimento dos nomes de todos os autores */
static int cmd_showStats(){
    
    if (load){
        
        printf ("O menor nome no ficheiro é %s;\n", getMenor());
        printf ("O maior nome no ficheiro é %s;\n", getMaior());
        printf ("A média do tamanho dos nomes inseridos é %d caracteres;\n", getMedia());
        
        return 1;
    }
    else return mensagem_de_erro(E_NO_LOAD);
    
}
/* Sai da aplicação */
static int cmd_exit(){
    char args[3];
    char letra;
    printf("Deseja sair da Aplicação(Y/N)? ");
    
    fgets(args, 3, stdin);
    
    EoS(args);
    
    trim(args);
    
    letra = toupper(args[0]);
    
    if (letra == 'Y') {
        if (load) {
            freeInf();
            freeA();
            load = 0;
        }
        printf("Obrigado pela utilização.\n");
        return 0;
    }
    else return 1;
}

/* ---------------------------  Interpretador de comandos  --------------------------- */

/* Vê que Querie foi invocada */
static int interpretar(char *linha){
    char comando[1024];
    char args[1024];
    int nargs;
    nargs = sscanf(linha, "%s %[^\n]", comando, args);
    
    trim(comando);
    
    if (nargs == 1) {
        nargs = atoi(comando);
        switch (nargs) {
            case 1: return cmd_load();
            case 2: return cmd_showTab();
            case 3: return cmd_AutPub(1);
            case 4: return cmd_AutSolo();
            case 5: return cmd_AutPub(0);
            case 6: return cmd_impAut();
            case 7: return cmd_totPub();
            case 8: return cmd_MCaut();
            case 9: return cmd_RAut();
            case 10: return cmd_Tab_10();
            case 11: return file_CSV();
            case 12: return cmd_MPub();
            case 13: return cmd_Stats();
            case 14: return cmd_showStats();
            case 0: return cmd_exit();
            default: return mensagem_de_erro(E_COMMAND);
        }
    }
    else return mensagem_de_erro(E_COMMAND);
}
/* Imprime o menu da aplicação */
static int menu(){
    printf("\n\n .:: Aplicação Gestauts ::. \n\n");
    printf(" 1:\tPrima 1 para fazer load do seu ficheiro; \n");
    printf(" 2:\tPrima 2 para ver o número de publicações em cada ano;\n");
    printf(" 3:\tPrima 3 para ver o número de publicações de um autor num dado ano;\n");
    printf(" 4:\tPrima 4 para ver o número de autores que publicaram sempre sozinhos;\n");
    printf(" 5:\tPrima 5 para ver as publicações de um autor em cada ano;\n");
    printf(" 6:\tPrima 6 para ver o nome de todos os autores começados por uma letra\n");
    printf(" 7:\tPrima 7 para ver o número de publicações num intervalo de anos;\n");
    printf(" 8:\tPrima 8 para ver os co-autores com quem mais publicou um autor; \n");
    printf(" 9:\tPrima 9 para ver o nome dos autores que publicaram num intervalo fechado de anos; \n");
    printf(" 10:\tPrima 10 para ver o número total de publicações de 1, 2 ou 3 autores\n");
    printf(" 11:\tPrima 11 para criar um ficheiro em formato CSV com a informação das publicações de todos os anos;\n");
    printf(" 12:\tPrima 12 para ver os autores que mais publicaram num dado um ano;\n");
    printf(" 13:\tPrima 13 para ver a percentagem de publicações de um autor num dado ano;\n");
    printf(" 14:\tPrima 14 para ver o autor com o maior e menor nome e a média do comprimento dos nomes de todos os autores;\n");
    printf(" 0:\tPrima 0 para sair da aplicação;\n");
    printf("\n Escolha a sua opção: ");
    return 1;
}
/* Lê a linha que inserimos */
static void interpretador() {
    int resultado = 0;
    char linha[1024];
    int ciclo = 1;
    while(ciclo && menu() && fgets(linha, 1024, stdin) != NULL){
        system("clear");
        resultado = interpretar(linha);

        if(resultado == 0)
            ciclo = 0;
    }
}
/* Ativa o programa */
int main(){
    
    load = 0;
    
    system("clear");
    
    interpretador();
    
    return 0;
}
