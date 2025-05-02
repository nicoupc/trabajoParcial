#ifndef MUNDO_H
#define MUNDO_H

#include "Funciones.h"

class Mundo
{
private:
    int mundoActual; // Identifica el mundo actual (1, 2 o 3)

    // Dibuja los límites del mundo 1
    void dibujarLimitesMundo1() const
    {
        for (int i = 0; i < HEIGHT; ++i)
        {
            gotoxy(0, i);
            std::cout << '|';
            gotoxy(WIDTH - 1, i);
            std::cout << '|';
        }
        for (int i = 0; i < WIDTH; ++i)
        {
            gotoxy(i, 0);
            std::cout << '-';
            gotoxy(i, HEIGHT - 1);
            std::cout << '-';
        }
    }

    // Dibuja los límites del mundo 2
    void dibujarLimitesMundo2() const
    {
        for (int i = 0; i < HEIGHT; ++i)
        {
            gotoxy(5, i);
            std::cout << '|';
            gotoxy(WIDTH - 6, i);
            std::cout << '|';
        }
        for (int i = 5; i < WIDTH - 5; ++i)
        {
            gotoxy(i, 2);
            std::cout << '-';
            gotoxy(i, HEIGHT - 3);
            std::cout << '-';
        }
    }

    // Dibuja los límites del mundo 3
    void dibujarLimitesMundo3() const
    {
        for (int i = 2; i < HEIGHT - 2; ++i)
        {
            gotoxy(10, i);
            std::cout << '|';
            gotoxy(WIDTH - 11, i);
            std::cout << '|';
        }
        for (int i = 10; i < WIDTH - 10; ++i)
        {
            gotoxy(i, 4);
            std::cout << '-';
            gotoxy(i, HEIGHT - 5);
            std::cout << '-';
        }
    }

public:
    Mundo(int mundoInicial = 1) : mundoActual(mundoInicial)
    {
    }

    // Cambia al mundo especificado
    void cambiarMundo(int nuevoMundo)
    {
        if (nuevoMundo >= 1 && nuevoMundo <= 3)
        {
            mundoActual = nuevoMundo;
            system("cls");
            dibujar();
        }
    }

    // Dibuja los límites del mundo actual
    void dibujar() const
    {
        switch (mundoActual)
        {
        case 1:
            dibujarLimitesMundo1();
            break;
        case 2:
            dibujarLimitesMundo2();
            break;
        case 3:
            dibujarLimitesMundo3();
            break;
        default:
            break;
        }
    }

    // Verifica si el personaje está dentro de los límites del mundo actual
    bool estaDentroDemundo(int x, int y) const
    {
        switch (mundoActual)
        {
        case 1:
            return x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1;
        case 2:
            return x > 5 && x < WIDTH - 6 && y > 2 && y < HEIGHT - 3;
        case 3:
            return x > 10 && x < WIDTH - 11 && y > 4 && y < HEIGHT - 5;
        default:
            return false;
        }
    }

    // Maneja la transición entre mundos
    int manejarTransicion(int x, int y) const
    {
        if (mundoActual == 1 && x >= WIDTH - 1) return 2; // Transición al mundo 2
        if (mundoActual == 2 && x <= 5) return 1; // Transición al mundo 1
        if (mundoActual == 2 && x >= WIDTH - 6) return 3; // Transición al mundo 3
        if (mundoActual == 3 && x <= 10) return 2; // Transición al mundo 2
        return mundoActual; // No hay transición
    }
};

#endif // MUNDO_H
