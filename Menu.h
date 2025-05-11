//
// Created by c0d3r on 10/05/2025.
//

#ifndef MENU_H
#define MENU_H

#include "Personaje.h"
#include "Enemigo.h"
#include "Aliado.h"
#include <iostream> // Para usar std::cout
#include <windows.h> // Para usar funciones de la consola
#include <vector> // Para usar std::vector
#include <sstream> // Para usar std::istringstream
#include <conio.h> // Para usar _kbhit()
#pragma comment(lib, "winmm.lib") // Para usar PlaySound

using namespace std;
void mostrarMenu();
void mostrarCreditos();

void playMusic(const wchar_t* filename)
{
    PlaySoundW(filename, nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void centrarTexto(const std::string& texto)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    int anchoConsola = info.srWindow.Right - info.srWindow.Left + 1;
    int longitudTexto = texto.length();
    int numEspacios = (anchoConsola - longitudTexto) / 2;
    for (int i = 0; i < numEspacios; ++i) cout << " ";
    cout << texto << endl;
}

void setFontSize(int width, int height)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
    wcscpy_s(fontInfo.FaceName, L"Consolas"); // o "Lucida Console"
    fontInfo.dwFontSize.X = width;
    fontInfo.dwFontSize.Y = height;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);
}

int maxConsole()
{
    HWND consoleWindow = GetConsoleWindow();
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    MoveWindow(consoleWindow, 0, 0, desktop.right, desktop.bottom, TRUE);
    return 0;
}

void centrarYMostrar(const string& frame)
{
    istringstream stream(frame);
    string line;
    while (getline(stream, line)) centrarTexto(line);
}

string logoUPC = R"(
                                           **
                                        +****
                                       *****
                          +=          ******                   +
                        **+          *******                    **
                      ***           *********                    ***
                     ***           **********+                    ***+
                   +***            +***********                    ****
                  +****            **************                  *****
                 +*****            ****************                 *****
                 *****             +****************                *****
                ******             ******************               ******
                ******              ******************              *******
               *******               ******************             *******
               +*******               *****************             *******
               ********                +***************            ********
               ********+                 **************            ********
               *********+                  ************           *********
               **********                    **********          **********
               ************                  **********         ***********
                ************                  *******+        +************
                =************+                ******+       +*************
                 ***************              *****+      ***************
                  *****************+          ****    =*****************+
                   ************************+=**************************
                    **************************************************
                     ************************************************
                       ********************************************+
                         ****************************************+
                           ************************************
                             +*******************************
                                 +***********************
                                       =**********=
)";

void mostrarBarraDeCarga()
{
    maxConsole();
    system("color 4F");
    system("cls");
    centrarYMostrar(logoUPC);
    int total = 30;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int pad = max((cols - total - 2) / 2, 0);
    cout << string(pad, ' ') << "[";
    for (int i = 0; i < total; ++i)
    {
        cout << "=" << flush;
        Sleep(80);
    }
    cout << "]" << endl;
    Sleep(800);
}

void dibujarPersonajes()
{
    int xInicio = 35; // Coordenada X inicial para los personajes
    int yInicio = 10; // Coordenada Y inicial para los personajes
    int separacion = 30; // Separación horizontal entre los personajes

    // Mostrar al personaje principal
    gotoxy(xInicio, yInicio);
    cout << "Jugador:";
    Personaje personajeMenu(xInicio, yInicio + 1);
    personajeMenu.dibujar();

    // Mostrar al enemigo
    gotoxy(xInicio + separacion, yInicio);
    cout << "Enemigo:";
    Enemigo enemigoTemp(xInicio + separacion, yInicio + 1);
    enemigoTemp.dibujar();

    // Mostrar al aliado de velocidad
    gotoxy(xInicio + 2 * separacion, yInicio);
    cout << "Aliado de Velocidad:";
    Aliado aliadoVelocidadTemp(xInicio + 2 * separacion, yInicio + 1);
    aliadoVelocidadTemp.dibujar();

    // Mostrar al aliado de vida
    gotoxy(xInicio + 3 * separacion, yInicio);
    cout << "Aliado de Vida:";
    Aliado aliadoVidaTemp(xInicio + 3 * separacion, yInicio + 1, true);
    aliadoVidaTemp.dibujar();
}

void mostrarRecursosTecnologicos()
{
    int xInicio = 35; // Coordenada X inicial para los recursos
    int yInicio = 17; // Coordenada Y inicial debajo de los personajes
    int separacion = 30; // Separación horizontal entre los recursos

    color(15); // Cambiar color a blanco
    // Dibujar Inteligencia Artificial (IA)
    gotoxy(xInicio, yInicio);
    cout << "Inteligencia Artificial (IA)";
    gotoxy(xInicio, yInicio + 1);
    cout << " /\\ ";
    gotoxy(xInicio, yInicio + 2);
    cout << "<@@>";
    gotoxy(xInicio, yInicio + 3);
    cout << " \\/ ";

    // Dibujar Energías Sostenibles (ES)
    gotoxy(xInicio + separacion, yInicio);
    cout << "Energias Sostenibles (ES)";
    gotoxy(xInicio + separacion, yInicio + 1);
    cout << "(~~)";
    gotoxy(xInicio + separacion, yInicio + 2);
    cout << "(~~)";
    gotoxy(xInicio + separacion, yInicio + 3);
    cout << " || ";

    // Dibujar Robótica (RB)
    gotoxy(xInicio + 2 * separacion, yInicio);
    cout << "Robotica (RB)";
    gotoxy(xInicio + 2 * separacion, yInicio + 1);
    cout << " [] ";
    gotoxy(xInicio + 2 * separacion, yInicio + 2);
    cout << "[==]";
    gotoxy(xInicio + 2 * separacion, yInicio + 3);
    cout << " [] ";

    // Dibujar Big Data (BD)
    gotoxy(xInicio + 3 * separacion, yInicio);
    cout << "Big Data (BD)";
    gotoxy(xInicio + 3 * separacion, yInicio + 1);
    cout << "+--+";
    gotoxy(xInicio + 3 * separacion, yInicio + 2);
    cout << "|##|";
    gotoxy(xInicio + 3 * separacion, yInicio + 3);
    cout << "-__-";
}

void dibujarRecursosHumanos()
{
    int xInicio = 35; // Coordenada X inicial para los recursos humanos
    int yInicio = 22; // Coordenada Y inicial debajo de los recursos tecnológicos
    int separacion = 30; // Separación horizontal entre los recursos humanos

    color(15); // Cambiar color a blanco

    // Dibujar Empatía
    gotoxy(xInicio, yInicio);
    cout << "Empatia";
    gotoxy(xInicio, yInicio + 1);
    cout << " (^^)";
    gotoxy(xInicio, yInicio + 2);
    cout << " (- )";
    gotoxy(xInicio, yInicio + 3);
    cout << " (e )";

    // Dibujar Creatividad
    gotoxy(xInicio + separacion, yInicio);
    cout << "Creatividad";
    gotoxy(xInicio + separacion, yInicio + 1);
    cout << " /\\ ";
    gotoxy(xInicio + separacion, yInicio + 2);
    cout << "/~~\\";
    gotoxy(xInicio + separacion, yInicio + 3);
    cout << "|  |";
    gotoxy(xInicio + separacion, yInicio + 4);
    cout << "(c )";

    // Dibujar Trabajo en equipo
    gotoxy(xInicio + 2 * separacion, yInicio);
    cout << "Trabajo en equipo";
    gotoxy(xInicio + 2 * separacion, yInicio + 1);
    cout << "()()";
    gotoxy(xInicio + 2 * separacion, yInicio + 2);
    cout << "||||";
    gotoxy(xInicio + 2 * separacion, yInicio + 3);
    cout << "||||";
    gotoxy(xInicio + 2 * separacion, yInicio + 4);
    cout << "(t )";


    // Dibujar Ética
    gotoxy(xInicio + 3 * separacion, yInicio);
    cout << "Etica";
    gotoxy(xInicio + 3 * separacion, yInicio + 1);
    cout << "(^^)";
    gotoxy(xInicio + 3 * separacion, yInicio + 2);
    cout << "(- )";
    gotoxy(xInicio + 3 * separacion, yInicio + 3);
    cout << "(h )";
}

void mostrarInstrucciones()
{
    int pagina = 1;
    while (true)
    {
        system("cls");
		color(14);
        cout << "Presione 'q' para volver al menu" << endl;
        if (pagina == 1)
        {
            centrarTexto("INSTRUCCIONES");
            color(15);
            centrarTexto("Desplazate con las flechas direccionales del teclado");
            centrarTexto("Recolecta los elementos de cada mundo y evita los enemigos");
            centrarTexto("Construye en los cuadrantes con los materiales recoletados - acercate a ellos");
			color(14);
            centrarTexto("------------");
			color(15);
            centrarTexto("Mundo 1: Recolecta recursos tecnologicos");
            centrarTexto("Mundo 2: Recolecta recursos humanos");
            centrarTexto("Mundo 3: Construye el mundo equilibrado");
			color(14);
            centrarTexto("------------");
			color(15);
            dibujarPersonajes();
            mostrarRecursosTecnologicos();
            dibujarRecursosHumanos();
			color(7); // Cambiar color a blanco
        }
        else if (pagina == 2)
        {
            centrarTexto("INSTRUCCIONES - PAGINA 2");
            cout << "\n";
            centrarTexto("Historia:");
			color(15);
            centrarTexto("El jugador es el 'Vigilante del Equilibrio' viajando entre mundos.");
            centrarTexto("Debe recolectar recursos para construir un nuevo mundo equilibrado.");
            centrarTexto("El primer mundo es humano, ecologico, pero poco tecnologico.");
            centrarTexto("El segundo mundo posee alta tecnologia, aunque es uno sin emociones.");
            centrarTexto("El mundo 3 es donde tu apareces...");
            centrarTexto("Tu eres el destinado a crear un nuevo mundo lleno de equilibrio");
            centrarTexto("Existen aliados que te beneficiaran durante tu mision");
        }
		color(14);
        centrarTexto("\n<- izquierda | derecha -> para cambiar pagina");
		color(15);
        char tecla = _getch();
        if (tecla == 'q') break;
        if (tecla == 77 && pagina == 1) pagina = 2;
        if (tecla == 75 && pagina == 2) pagina = 1;
    }
}

void mostrarCreditos()
{
    system("cls");
    centrarTexto("Creditos:");
    centrarTexto("Hecho por:");
    centrarTexto("Sebastian Sayago");
    centrarTexto("Italo Damacen");
    centrarTexto("Nicolas Ventosilla");
    Sleep(5000);
    mostrarMenu();
}

void mostrarMenu()
{
    system("color 07");
    playMusic(L"menu.wav");
    system("cls");
    setFontSize(0, 30);
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

    centrarTexto(
        "   ####   ##   ##  ######    #####   ##   ##   #####   ######     ##     ####       ##     ##   ##    ####   #######");
    centrarTexto(
        "  ##  ##  ##   ##   ##  ##  ##   ##  ###  ##  ##   ##   ##  ##   ####     ##       ####    ###  ##   ##  ##   ##   #");
    centrarTexto(
        " ##       ##   ##   ##  ##  ##   ##  #### ##  ##   ##   ##  ##  ##  ##    ##      ##  ##   #### ##  ##        ## #");
    centrarTexto(
        " ##       #######   #####   ##   ##  ## ####  ##   ##   #####   ##  ##    ##      ##  ##   ## ####  ##        ####");
    centrarTexto(
        " ##       ##   ##   ## ##   ##   ##  ##  ###  ##   ##   ##  ##  ######    ##   #  ######   ##  ###  ##        ## #");
    centrarTexto(
        "  ##  ##  ##   ##   ##  ##  ##   ##  ##   ##  ##   ##   ##  ##  ##  ##    ##  ##  ##  ##   ##   ##   ##  ##   ##   #");
    centrarTexto(
        "   ####   ##   ##  #### ##   #####   ##   ##   #####    #####   ##  ##    ######  ##  ##   ##   ##    ####    ######");

    cout << "\n";
    centrarTexto("1. Jugar");
    centrarTexto("2. Instrucciones");
    centrarTexto("3. Creditos");
    centrarTexto("4. Salir");
}

#endif //MENU_H
