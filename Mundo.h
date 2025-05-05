#ifndef MUNDO_H
#define MUNDO_H

#include "Funciones.h"

class Mundo
{
private:
    int mundoActual; // Identifica el mundo actual (1, 2 o 3)

    // Dibuja los límites del mundo con un carácter específico
    void dibujarLimites(char caracter) const
    {
        for (int i = 0; i < HEIGHT; ++i)
        {
            gotoxy(0, i);
            cout << caracter;
            gotoxy(WIDTH - 1, i);
            cout << caracter;
        }
        for (int i = 0; i < WIDTH; ++i)
        {
            gotoxy(i, 0);
            cout << caracter;
            gotoxy(i, HEIGHT - 1);
            cout << caracter;
        }
    }

public:
    Mundo(int mundoInicial = 1) : mundoActual(mundoInicial) {}

    int getMundoActual() const { return mundoActual; }

    void cambiarMundo(int nuevoMundo)
    {
        if (nuevoMundo >= 1 && nuevoMundo <= 3)
        {
            mundoActual = nuevoMundo;
            system("cls");
            dibujar();
        }
    }

    void dibujar() const
    {
        switch (mundoActual)
        {
        case 1:
            dibujarLimites('#');
            break;
        case 2:
            dibujarLimites('@');
            break;
        case 3:
            dibujarLimites('*');
            break;
        default:
            break;
        }
    }

    bool estaDentroDemundo(int x, int y) const
    {
        return x > 2 && x < WIDTH - 5;
    }

    int manejarTransicion(int x, int y) const
    {
        if (x <= 2)
        {
            if (mundoActual == 1) return 2;
            if (mundoActual == 3) return 1;
        }
        else if (x >= WIDTH - 5)
        {
            if (mundoActual == 1) return 3;
            if (mundoActual == 2) return 1;
        }
        return mundoActual;
    }
};

#endif // MUNDO_H
