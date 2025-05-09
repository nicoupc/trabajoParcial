#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Funciones.h"
#include "Aliado.h"
#include <iostream>

class Enemigo
{
private:
    int x, y; // Coordenadas del enemigo
    static constexpr int LIMITE_X = WIDTH; // Límite horizontal
    static constexpr int LIMITE_Y = HEIGHT; // Límite vertical

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
        case 2: return 14; // Amarillo
        case 3: return 13; // Magenta
        default: return 7; // Blanco (por defecto)
        }
    }

    // Valida que las coordenadas estén dentro de los límites
    void validarLimites()
    {
        if (x < 1) x = 1;
        if (x >= LIMITE_X - 5) x = LIMITE_X - 5;
        if (y < 1) y = 1;
        if (y >= LIMITE_Y - 5) y = LIMITE_Y - 5;
    }

public:
    // Constructor que inicializa las coordenadas del enemigo
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
                int colorValor = obtenerColor(enemigo[i][j]); // Obtiene el color correspondiente
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
                gotoxy(x + j, y + i); // Posiciona el cursor
                std::cout << ' '; // Borra con un espacio vacío
            }
        }
    }

    // Mueve el enemigo aleatoriamente
    void moverAleatorio(const vector<Enemigo>& enemigos, const Aliado& aliado)
    {
        borrar();
        int nuevoX, nuevoY;

        do
        {
            int dx = generarAleatorio(-1, 1);
            int dy = generarAleatorio(-1, 1);
            nuevoX = x + dx;
            nuevoY = y + dy;

            // Verificar colisión con el aliado
            if (nuevoX + getAncho() > aliado.getX() &&
                nuevoX < aliado.getX() + aliado.getAncho() &&
                nuevoY + getAlto() > aliado.getY() &&
                nuevoY < aliado.getY() + aliado.getAlto())
            {
                continue; // Reintentar si colisiona con el aliado
            }
        } while (posicionOcupada(nuevoX, nuevoY, enemigos));

        x = nuevoX;
        y = nuevoY;
        validarLimites();
        dibujar();
    }

    // Verifica si una posición está ocupada por otro enemigo
    bool posicionOcupada(int nuevoX, int nuevoY, const vector<Enemigo>& enemigos) const
    {
        for (const auto& enemigo : enemigos)
        {
            if (&enemigo != this && // Evita comparar con sí mismo
                nuevoX < enemigo.getX() + enemigo.getAncho() &&
                nuevoX + getAncho() > enemigo.getX() &&
                nuevoY < enemigo.getY() + enemigo.getAlto() &&
                nuevoY + getAlto() > enemigo.getY())
            {
                return true; // La posición está ocupada
            }
        }
        return false; // La posición está libre
    }

    // Detecta si colisiona con el personaje
    bool colisionaCon(int personajeX, int personajeY) const
    {
        return x == personajeX && y == personajeY; // Verifica si las coordenadas coinciden
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
        return x; // Coordenada X
    }

    // Obtiene la posición Y del enemigo
    int getY() const
    {
        return y; // Coordenada Y
    }
};

#endif // ENEMIGO_H
