#ifndef ALIADO_H
#define ALIADO_H

#include "Funciones.h"
#include <iostream>

class Aliado
{
private:
    int x, y; // Coordenadas del aliado
    static constexpr int ANCHO = 4;
    static constexpr int ALTO = 4;

    // Matriz que representa al aliado
    const int aliado[4][4] = {
        {1, 1, 1, 1},
        {1, 2, 2, 1},
        {2, 3, 3, 2},
        {0, 1, 1, 0}
    };

    // Obtiene el color según el valor de la matriz
    int obtenerColor(int valor) const
    {
        switch (valor)
        {
        case 0: return 0; // Negro
        case 1: return 2; // Verde
        case 2: return 14; // Verde claro
        case 3: return 10; // Amarillo
        default: return 7; // Blanco
        }
    }

public:
    Aliado(int startX, int startY) : x(startX), y(startY)
    {
    }

    // Dibuja el aliado en la consola
    void dibujar() const
    {
        for (int i = 0; i < ALTO; ++i)
        {
            for (int j = 0; j < ANCHO; ++j)
            {
                gotoxy(x + j, y + i);
                int colorValor = obtenerColor(aliado[i][j]);
                color(colorValor);
                std::cout << CUBO;
            }
        }
        color(7); // Restablece el color
    }

    // Borra el aliado de la consola
    void borrar() const
    {
        for (int i = 0; i < ALTO; ++i)
        {
            for (int j = 0; j < ANCHO; ++j)
            {
                gotoxy(x + j, y + i);
                std::cout << ' ';
            }
        }
    }

    // Detecta colisión con el personaje
    bool colisionaCon(int personajeX, int personajeY, int personajeAncho, int personajeAlto) const
    {
        return x < personajeX + personajeAncho &&
            x + ANCHO > personajeX &&
            y < personajeY + personajeAlto &&
            y + ALTO > personajeY;
    }

    // Obtiene la posición X
    int getX() const { return x; }

    // Obtiene la posición Y
    int getY() const { return y; }

    // Obtiene el ancho
    int getAncho() const { return ANCHO; }

    // Obtiene el alto
    int getAlto() const { return ALTO; }
};

#endif // ALIADO_H
