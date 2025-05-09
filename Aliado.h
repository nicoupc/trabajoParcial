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
    bool visible = true; // Indica si el aliado está visible
    bool esAliadoDeVida; // Nuevo atributo para identificar el tipo de aliado

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
        if (esAliadoDeVida) // Verifica si es el aliado de vida
        {
            switch (valor)
            {
            case 0: return 0;
            case 1: return 4;
            case 2: return 14;
            case 3: return 12;
            default: return 7;
            }
        }
        else
        {
            switch (valor)
            {
            case 0: return 0;
            case 1: return 2;
            case 2: return 14;
            case 3: return 10;
            default: return 7;
            }
        }
    }

public:
    Aliado(int startX, int startY, bool esDeVida = false)
        : x(startX), y(startY), esAliadoDeVida(esDeVida)
    {
    }

    // Dibuja el aliado en la consola
    void dibujar() const
    {
        if (!visible) return; // No dibujar si está oculto
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
        color(7);
    }

    void ocultar()
    {
        borrar();
        visible = false;
    }

    bool estaVisible() const { return visible; }

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
