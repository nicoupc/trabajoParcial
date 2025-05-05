//
// Created by c0d3r on 01/05/2025.
//

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
using namespace System; // Para usar el espacio de nombres de C++/CLI

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

// Espera a que el usuario presione la tecla ESCAPE
void esperarTecla()
{
    std::cout << "\nPresione <ESCAPE> para volver al menu principal\n";
    char tecla;
    do
    {
        tecla = _getch();
    } while (tecla != 27);
    system("cls");
}

#endif // FUNCIONES_H
