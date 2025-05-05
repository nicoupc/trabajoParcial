#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Funciones.h" // Para usar funciones auxiliares como color y gotoxy
#include <iostream>

#define WIDTH 80
#define HEIGHT 25
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

constexpr char CUBO = 219; // Caracter para el cubo
constexpr char VACIO = ' '; // Caracter para el espacio vacio

class Personaje
{
private:
    int x, y;
    const char vacio;
    static constexpr int LIMITE_X = WIDTH;
    static constexpr int LIMITE_Y = HEIGHT;

    // Matriz que representa el personaje
    const int personaje[4][4] = {
        {2, 2, 2, 2},
        {2, 1, 1, 2},
        {1, 3, 3, 1},
        {0, 2, 2, 0}
    };

    // Obtiene el color según el valor de la matriz
    int obtenerColor(int valor) const
    {
        switch (valor)
        {
        case 0: return 0; // Negro
        case 1: return 9; // Azul
        case 2: return 10; // Verde
        case 3: return 12; // Rojo
        default: return 7; // Blanco (por defecto)
        }
    }

    // Valida que las coordenadas estén dentro de los límites
    void validarLimites()
    {
        if (x <= 1) x = 1;
        if (x >= LIMITE_X - 5) x = LIMITE_X - 5;
        if (y < 1) y = 1;
        if (y >= LIMITE_Y - 5) y = LIMITE_Y - 5;
    }

public:
    Personaje(int startX, int startY, char simboloVacio = VACIO)
        : x(startX), y(startY), vacio(simboloVacio)
    {
        validarLimites();
    }

    // Obtiene la posición X del personaje
    int getX() const
    {
        return x;
    }

    // Obtiene la posición Y del personaje
    int getY() const
    {
        return y;
    }

    // Obtiene el ancho del personaje
    int getAncho() const
    {
        return 4; // Ancho de la matriz del personaje
    }

    // Obtiene el alto del personaje
    int getAlto() const
    {
        return 4; // Alto de la matriz del personaje
    }

    // Establece una nueva posición inicial para el personaje
    void setPosicionInicial(int nuevaX, int nuevaY)
    {
        borrar(); // Borra el personaje de la posición actual
        x = nuevaX;
        y = nuevaY;
        validarLimites(); // Asegura que las nuevas coordenadas estén dentro de los límites
        dibujar(); // Dibuja el personaje en la nueva posición
    }

    // Dibuja el personaje en la consola
    void dibujar() const
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                gotoxy(x + j, y + i); // Posiciona el cursor
                int colorValor = obtenerColor(personaje[i][j]);
                color(colorValor); // Cambia el color usando la función de Funciones.h
                std::cout << CUBO; // Dibuja el carácter CUBO
            }
        }
        color(7); // Restablece el color a blanco
    }

    // Borra el personaje de la consola
    void borrar() const
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                gotoxy(x + j, y + i);
                std::cout << vacio; // Borra con el carácter vacío
            }
        }
    }

    // Mueve el personaje en la dirección indicada
    void mover(int dx, int dy)
    {
        borrar();
        x += dx;
        y += dy;
        validarLimites();
        dibujar();
    }

    // Maneja el movimiento del personaje según la tecla presionada
    void manejarMovimiento(char tecla)
    {
        if (tecla == UP)
            mover(0, -1);
        else if (tecla == DOWN)
            mover(0, 1);
        else if (tecla == LEFT)
            mover(-2, 0);
        else if (tecla == RIGHT)
            mover(2, 0);
    }
};

#endif // PERSONAJE_H
