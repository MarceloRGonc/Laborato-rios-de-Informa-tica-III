#ifndef ___ERROS_H___
#define ___ERROS_H___

#include <stdio.h>

typedef enum{
                E_COMMAND,
                E_NO_FILE,
                E_NO_LOAD,
                E_NO_READ,
                E_INT_INVALIDO,
                E_GRAVAR,
                E_ROTATE,
                E_MEM
        } erro;

int mensagem_de_erro(erro erro_num);

#endif
