#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Funciones.h"
#include <iostream>

class Enemigo
{
private:
    int x, y;
    static constexpr int LIMITE_X = WIDTH;
    static constexpr int LIMITE_Y = HEIGHT;

    // Matriz que representa el enemigo
    const int enemigo[4][4] = {
        {3, 3, 3, 3},
        {3, 2, 2, 3},
        {2, 1, 1, 2},
        {0, 3, 3, 0}
    };

    // Obtiene el color según el valor de la matriz
    int obtenerColor(int valor) const
    {
        switch (valor)
        {
        case 0: return 0; // Negro
        case 1: return 4; // Rojo
        case 2: return 6; // Amarillo
        case 3: return 5; // Magenta
        default: return 7; // Blanco (por defecto)
        }
    }

    // Valida que las coordenadas estén dentro de los límites
    void validarLimites()
    {
        if (x < 0) x = 0;
        if (x >= LIMITE_X) x = LIMITE_X - 1;
        if (y < 0) y = 0;
        if (y >= LIMITE_Y) y = LIMITE_Y - 1;
    }

public:
    Enemigo(int startX, int startY)
        : x(startX), y(startY)
    {
        validarLimites();
    }

    // Dibuja el enemigo en la consola
    void dibujar() const
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                gotoxy(x + j, y + i); // Posiciona el cursor
                int colorValor = obtenerColor(enemigo[i][j]);
                color(colorValor); // Cambia el color usando la función de Funciones.h
                std::cout << CUBO; // Dibuja el carácter CUBO
            }
        }
        color(7); // Restablece el color a blanco
    }

    // Borra el enemigo de la consola
    void borrar() const
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                gotoxy(x + j, y + i);
                std::cout << ' '; // Borra con un espacio vacío
            }
        }
    }

    // Mueve el enemigo aleatoriamente
    void moverAleatorio()
    {
        borrar();
        int dx = generarAleatorio(-1, 1);
        int dy = generarAleatorio(-1, 1);
        x += dx;
        y += dy;
        validarLimites();
        dibujar();
    }

    // Detecta si colisiona con el personaje
    bool colisionaCon(int personajeX, int personajeY) const
    {
        return x == personajeX && y == personajeY;
    }

    // Obtiene el ancho del enemigo
    int getAncho() const
    {
        return 4; // Ancho de la matriz del enemigo
    }

    // Obtiene el alto del enemigo
    int getAlto() const
    {
        return 4; // Alto de la matriz del enemigo
    }

    // Obtiene la posición X del enemigo
    int getX() const
    {
        return x;
    }

    // Obtiene la posición Y del enemigo
    int getY() const
    {
        return y;
    }
};

#endif // ENEMIGO_H
