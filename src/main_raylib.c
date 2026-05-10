#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ui/frontend.h"

int main(void) {
    // Configuração de encoding
    setlocale(LC_ALL, "");
    
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Executar o frontend com raylib
    executar_frontend();
    
    return 0;
}
