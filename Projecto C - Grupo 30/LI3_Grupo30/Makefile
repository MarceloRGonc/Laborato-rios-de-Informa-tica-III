
CC = gcc

CFLAGS = -ansi -Wall -Wextra -Wno-unused-result -pedantic -O3 -std=c99 -g

all:
	@echo
	make GESTAUTS	

Leitura.o : Leitura.c Estatisticas.h Indice_Autores.h Catalogo_Autores.h
	@echo "\n\t\tCompilando Módulo Leitura"
	$(CC) -o Leitura.o -c Leitura.c $(CFLAGS)

Estatisticas.o : Estatisticas.c Estatisticas.h
	@echo "\n\t\tCompilando Módulo Estatistica"
	$(CC) -o Estatisticas.o -c Estatisticas.c $(CFLAGS)

Indice_Autores.o : Indice_Autores.c Indice_Autores.h
	@echo "\n\t\tCompilando Módulo Indice_Autores"
	$(CC) -o Indice_Autores.o -c Indice_Autores.c $(CFLAGS)

Catalogo_Autores.o : Catalogo_Autores.c Catalogo_Autores.h
	@echo "\n\t\tCompilando Módulo Catalogo_Autores"
	$(CC) -o Catalogo_Autores.o -c Catalogo_Autores.c $(CFLAGS)

Erro.o : Erro.c Erro.h
	@echo "\n\t\tCompilando Módulo Erros"
	$(CC) -o Erro.o -c Erro.c $(CFLAGS)


GESTAUTS : Leitura.o Estatisticas.o Indice_Autores.o Catalogo_Autores.o Erro.o
	@echo "\n\t\tCompilando Gestauts"
	$(CC) Leitura.o Estatisticas.o Indice_Autores.o Catalogo_Autores.o Erro.o -lm -o GESTAUTS
	@echo

clean :
	rm -f Leitura.o
	rm -f Estatisticas.o
	rm -f Indice_Autores.o
	rm -f Catalogo_Autores.o
	rm -f Erro.o
	rm -f GESTAUTS

