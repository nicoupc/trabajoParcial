#include "Menu.h"
#include "Juego.h"

int main()
{
    // Reproducir música de carga y mostrar barra de carga
    playMusic(L"loading.wav");
    mostrarBarraDeCarga();

    // Bucle principal del menú
    while (true)
    {
        setFontSize(0, 24); // Ajustar el tamaño de la fuente
        mostrarMenu(); // Mostrar el menú principal

        char opcion = _getch(); // Leer la opción seleccionada
        switch (opcion)
        {
        case '1':
            {
                // Jugar
                setFontSize(0, 16);
                playMusic(L"game.wav");
                Juego juego; // Crear una instancia del juego
                juego.inicializar(); // Inicializar el juego
                juego.buclePrincipal(); // Ejecutar el bucle principal del juego
                break;
            }
        case '2': // Mostrar instrucciones
            setFontSize(0, 16);
            mostrarInstrucciones();
            break;
        case '3': // Mostrar créditos
            setFontSize(0, 16);
            mostrarCreditos();
            break;
        case '4': // Salir
            centrarTexto("Saliendo...");
            Sleep(1000);
            return 0;
        default:
            centrarTexto("Opcion no valida. Intente de nuevo.");
            Sleep(500);
            break;
        }
    }

    return 0;
}
