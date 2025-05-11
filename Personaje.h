#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Funciones.h" // Para usar funciones auxiliares como color y gotoxy
#include <iostream>

#define WIDTH 100
#define HEIGHT 35
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
    int vidas = 3; // Atributo para las vidas del personaje
    const char vacio;
    static constexpr int LIMITE_X = WIDTH;
    static constexpr int LIMITE_Y = HEIGHT;
    bool invulnerable = false; // Estado de invulnerabilidad
    int tiempoInvulnerable = 0; // Contador para invulnerabilidad
    int velocidad = 1; // Velocidad del personaje


    // Matriz que representa el personaje
    const int personaje[4][4] = {
        {2, 2, 2, 2},
        {2, 1, 1, 2},
        {1, 3, 3, 1},
        {0, 2, 2, 0}
    };

    // Obtiene el color segun el valor de la matriz
    int obtenerColor(int valor) const
    {
        switch (valor)
        {
        case 0: return 0; // Negro
        case 1: return 14; // Crema
        case 2: return 8; // Gris
        case 3: return 1; // Azul
        default: return 7; // Blanco (por defecto)
        }
    }

    // Valida que las coordenadas esten dentro de los limites
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

    // Obtiene la posicion X del personaje
    int getX() const
    {
        return x;
    }

    // Obtiene la posicion Y del personaje
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

    // Metodo para restar una vida
    void restarVida()
    {
        if (vidas > 0)
        {
            vidas--;
        }
    }

    void sumarVida()
    {
        vidas++;
    }

    int getVidas() const
    {
        return vidas;
    }

    // Activa la invulnerabilidad del personaje por un tiempo determinado
    void activarInvulnerabilidad(int duracion)
    {
        invulnerable = true;
        tiempoInvulnerable = duracion;
    }

    // Actualiza el estado de invulnerabilidad
    void actualizarInvulnerabilidad()
    {
        if (invulnerable && tiempoInvulnerable > 0)
        {
            tiempoInvulnerable--;
            if (tiempoInvulnerable == 0)
            {
                invulnerable = false;
            }
        }
    }

    bool estaInvulnerable() const
    {
        return invulnerable;
    }

    // Establece una nueva posicion inicial para el personaje
    void setPosicionInicial(int nuevaX, int nuevaY)
    {
        borrar(); // Borra el personaje de la posicion actual
        x = nuevaX;
        y = nuevaY;
        validarLimites(); // Asegura que las nuevas coordenadas esten dentro de los limites
        dibujar(); // Dibuja el personaje en la nueva posicion
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
                color(colorValor); // Cambia el color usando la funcion de Funciones.h
                cout << CUBO; // Dibuja el caracter CUBO
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
                cout << vacio; // Borra con el caracter vacio
            }
        }
    }

    // Mueve el personaje en la direccion indicada
    void mover(int dx, int dy)
    {
        borrar();
        x += dx * velocidad; // Multiplica el desplazamiento horizontal por la velocidad
        y += dy * velocidad; // Multiplica el desplazamiento vertical por la velocidad
        validarLimites();
        dibujar();
    }

    // Maneja el movimiento del personaje segun la tecla presionada
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

    // Establece la velocidad del personaje
    void setVelocidad(int nuevaVelocidad)
    {
        velocidad = nuevaVelocidad;
    }
};

#endif // PERSONAJE_H
