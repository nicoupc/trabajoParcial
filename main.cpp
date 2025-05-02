#include "pch.h"
#include "Juego.h"

int main()
{
    // Inicializar el juego
    Juego juego;

    // Configurar el entorno inicial
    juego.inicializar();

    // Ejecutar el bucle principal del juego
    juego.buclePrincipal();

    // Finalizar el programa
    std::cout << "Juego terminado. ¡Gracias por jugar!" << std::endl;
    return 0;
}
