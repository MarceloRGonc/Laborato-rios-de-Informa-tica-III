
#include "Erro.h"

/**
* Reporta o erro escrevendo uma mensagem no standard error
* @param erro_num O numero do erro que vem da tabela de erros. Usar SEMPRE o define e nao o valor numerico para maior legibilidade.
*/
int mensagem_de_erro(erro erro_num) {
	char* erro[] =
	{
  		"Comando nao existe",
  		"Erro o ficheiro que indicou não existe",
  		"Ainda não fez load do ficheiro",
  		"A leitura do ficheiro não foi realizada",
        "Introduziu um intervalo inválido",
  		"Nao se consegue gravar o ficheiro",
  		"Erro na rotação",
  		"Erro de alocacao de memoria"
	};
	(void) fprintf(stderr, "%s\n", erro[erro_num]);
	return -1 - erro_num;
}

