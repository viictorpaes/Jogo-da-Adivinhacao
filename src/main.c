#include "utils/utils.h"
#include "include/tipos.h"

int main(void) 
{
    Partida p;
    utils_inicializar_semente();
    partida_inicializar(&p, "Teste");
    p.numeroSecreto = utils_aleatorio_intervalo(1, 100);
    partida_imprimir(&p);
    return 0;
}