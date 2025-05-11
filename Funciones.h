#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream> // Para usar las funciones de entrada y salida
#include <windows.h> // Para usar las funciones de la consola
#include <conio.h> // Para usar la función _kbhit()
#include <ctime> // Para usar la función time()
#include <cstdlib> // Para usar la función exit()
#include <chrono> // Para medir el tiempo de ejecución
#include <vector> // Para usar el contenedor vector
#include <string> // Para usar la clase string

using namespace std; // Para usar el espacio de nombres estondar

// Oculta el cursor de la consola
void ocultarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Muestra el cursor de la consola
void mostrarCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Cambia el color del texto en la consola
void color(int color)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

// Mueve el cursor a la posición (x, y) en la consola
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Genera un número aleatorio entre min y max
int generarAleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

#define ANCHO_CONSOLA 160

//centrar texto diferente al usado en menu
void centrarTexto1(const string& texto)
{
    int espacios = (ANCHO_CONSOLA - texto.length()) / 2;
    cout << string(espacios, ' ') << texto << endl;
}

void mostrarPerdiste(bool gameOver)
{
    if (!gameOver) return;

    system("CLS");
    Sleep(500);

    string gameOverArte[] = {
        "________  ________  _____ ______   _______      ",
        "|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     ",
        "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    ",
        " \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  ",
        "  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ ",
        "   \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\",
        "    \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|",
        "                                                 ",
        " ________  ___      ___ _______   ________       ",
        "|\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\      ",
        "\\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\     ",
        " \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\    ",
        "  \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\|   ",
        "   \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\   ",
        "    \\|_______|\\|__|/       \\|_______|\\|__|\\|__|   "
    };

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    for (const auto& linea : gameOverArte)
    {
        centrarTexto1(linea);
    }

    Sleep(1000);
    centrarTexto1("Has perdido... Intenta de nuevo.");

    Sleep(2000);
    centrarTexto1("Presiona cualquier tecla para volver al menu...");
    Sleep(2000);
    _getch();
}


void centrarTexto2(const string& texto)
{
    int espacios = (ANCHO_CONSOLA - texto.length()) / 2;
    cout << string(espacios, ' ') << texto << endl;
}

void mostrarGanaste(bool gameOver)
{
    if (!gameOver) return;

    system("CLS");
    Sleep(500);

    string nuevoGameOverArte[] = {
        " ________      ________      ________       ________      ________       _________    _______       ___        ",
        "|\\   ____\\    |\\   __  \\    |\\   ___  \\    |\\   __  \\    |\\   ____\\     |\\___   ___\\ |\\  ___ \\     |\\  \\       ",
        "\\ \\  \\___|    \\ \\  \\|\\  \\   \\ \\  \\\\ \\  \\   \\ \\  \\|\\  \\   \\ \\  \\___|_    \\|___ \\  \\_| \\ \\   __/|    \\ \\  \\      ",
        " \\ \\  \\  ___   \\ \\   __  \\   \\ \\  \\\\ \\  \\   \\ \\   __  \\   \\ \\_____  \\        \\ \\  \\   \\ \\  \\_|/__   \\ \\  \\     ",
        "  \\ \\  \\|\\  \\   \\ \\  \\ \\  \\   \\ \\  \\\\ \\  \\   \\ \\  \\ \\  \\   \\|____|\\  \\        \\ \\  \\   \\ \\  \\_|\\ \   \\ \\__\\    ",
        "   \\ \\_______\\   \\ \\__\\ \\__\\   \\ \\__\\\\ \\__\\   \\ \\__\\ \\__\\    ____\\_\\  \\        \\ \\__\\   \\ \\_______\\   \\|__|    ",
        "    \\|_______|    \\|__|\\|__|    \\|__| \\|__|    \\|__|\\|__|   |\\_________\\        \\|__|    \\|_______|       ___  ",
        "                                                            \\|_________|                                 |\\__\\ ",
        "                                                                                                         \\|__| "
    };

    for (int i = 0; i < 7; ++i) cout << endl;

    for (const auto& linea : nuevoGameOverArte)
    {
        centrarTexto2(linea);
    }

    Sleep(1000);

    centrarTexto2("Has ganado... Felicitaciones!");
    Sleep(2000);
    centrarTexto2("Presiona cualquier tecla para volver al menú...");
    Sleep(2000);
    _getch();
}

#endif // FUNCIONES_H
