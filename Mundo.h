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
            cout << '#';
            gotoxy(WIDTH - 1, i);
            cout << '#';
        }
        for (int i = 0; i < WIDTH; ++i)
        {
            gotoxy(i, 0);
            cout << '#';
            gotoxy(i, HEIGHT - 1);
            cout << '#';
        }
    }

    // Dibuja los límites del mundo 2
    void dibujarLimitesMundo2() const
    {
        for (int i = 0; i < HEIGHT; ++i)
        {
            gotoxy(0, i);
            cout << '@';
            gotoxy(WIDTH - 1, i);
            cout << '@';
        }
        for (int i = 0; i < WIDTH; ++i)
        {
            gotoxy(i, 0);
            cout << '@';
            gotoxy(i, HEIGHT - 1);
            cout << '@';
        }
    }

    // Dibuja los límites del mundo 3
    void dibujarLimitesMundo3() const
    {
        for (int i = 0; i < HEIGHT; ++i)
        {
            gotoxy(0, i);
            cout << '*';
            gotoxy(WIDTH - 1, i);
            cout << '*';
        }
        for (int i = 0; i < WIDTH; ++i)
        {
            gotoxy(i, 0);
            cout << '*';
            gotoxy(i, HEIGHT - 1);
            cout << '*';
        }
    }

public:
    Mundo(int mundoInicial = 1) : mundoActual(mundoInicial)
    {
    }

    // Devuelve el mundo actual
    int getMundoActual() const
    {
        return mundoActual;
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
            return x > 2 && x < WIDTH - 5;
        case 2:
            return x > 2 && x < WIDTH - 5;
        case 3:
            return x > 2 && x < WIDTH - 5;
        default:
            return false;
        }
    }

    // Maneja la transición entre mundos
    int manejarTransicion(int x, int y) const
    {
        if (x <= 2) // Límite izquierdo
        {
            if (mundoActual == 1) return 2; // Del mundo 1 al 2
            if (mundoActual == 3) return 1; // Del mundo 3 al 1
        }
        else if (x >= WIDTH - 5) // Límite derecho
        {
            if (mundoActual == 1) return 3; // Del mundo 1 al 3
            if (mundoActual == 2) return 1; // Del mundo 2 al 1
        }
        return mundoActual; // No hay transición
    }
};

#endif // MUNDO_H
