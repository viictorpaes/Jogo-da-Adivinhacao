#include "ui/frontend.h"
#include "history/historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main(void) 
{
    setlocale(LC_ALL, "");
    
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    inicializar_historico();
    inicializar_historico_memoria();
    executar_frontend();
    
    return 0;
}
