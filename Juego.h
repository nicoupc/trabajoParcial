#ifndef JUEGO_H
#define JUEGO_H

#include "Personaje.h"
#include "Enemigo.h"
#include "Mundo.h"
#include <vector>

class Juego
{
private:
    Personaje personaje;
    Mundo mundo;
    std::vector<Enemigo> enemigos;
    bool gameOver;

    // Detecta colisiones entre el personaje y los enemigos
    void detectarColisiones()
    {
        for (const auto& enemigo : enemigos)
        {
            if (personaje.getX() < enemigo.getX() + enemigo.getAncho() &&
                personaje.getX() + personaje.getAncho() > enemigo.getX() &&
                personaje.getY() < enemigo.getY() + enemigo.getAlto() &&
                personaje.getY() + personaje.getAlto() > enemigo.getY())
            {
                if (!personaje.estaInvulnerable()) // Verifica si no es invulnerable
                {
                    personaje.restarVida();
                    personaje.activarInvulnerabilidad(30); // Activa invulnerabilidad por 30 ciclos

                    if (personaje.getVidas() == 0)
                    {
                        gameOver = true;
                    }
                }
                break;
            }
        }
    }

    // Actualiza el estado de los enemigos
    void actualizarEnemigos()
    {
        for (auto& enemigo : enemigos)
        {
            enemigo.moverAleatorio(); // Mueve al enemigo de forma aleatoria
        }
    }

public:
    Juego()
        : personaje(WIDTH / 2, HEIGHT / 2), gameOver(false)
    {
        // Agregar enemigos iniciales
        enemigos.emplace_back(10, 5);
        // enemigos.emplace_back(30, 10);
        // enemigos.emplace_back(50, 15);
    }

    // Inicializa el juego
    void inicializar()
    {
        ocultarCursor();
        system("cls");
        mundo.dibujar();
        personaje.dibujar();

        // Dibujar enemigos si el mundo actual es el 2 o el 3
        if (mundo.getMundoActual() == 2 || mundo.getMundoActual() == 3)
        {
            for (const auto& enemigo : enemigos)
            {
                enemigo.dibujar();
            }
        }
    }

    // Muestra el número de vidas en la parte derecha de la pantalla
    void mostrarVidas() const
    {
        gotoxy(WIDTH + 5, 0); // Posiciona el texto en el borde derecho
        std::cout << "VIDAS: " << personaje.getVidas();
    }

    // Ejecuta el bucle principal del juego
    void buclePrincipal()
    {
        int mundoActual = mundo.getMundoActual();

        while (!gameOver)
        {
            // Manejar entrada del usuario
            if (_kbhit())
            {
                char tecla = _getch();
                manejarEntrada(tecla);
            }

            // Manejar transición entre mundos
            if (!mundo.estaDentroDemundo(personaje.getX(), personaje.getY()))
            {
                int nuevoMundo = mundo.manejarTransicion(personaje.getX(), personaje.getY());
                if (nuevoMundo != mundoActual)
                {
                    mundo.cambiarMundo(nuevoMundo);
                    actualizarPosicionPersonaje(mundoActual, nuevoMundo);
                    mundoActual = nuevoMundo;

                    // Dibujar enemigos si el nuevo mundo es el 2 o el 3
                    if (mundoActual == 2 || mundoActual == 3)
                    {
                        for (const auto& enemigo : enemigos)
                        {
                            enemigo.dibujar();
                        }
                    }
                }
            }

            // Actualizar enemigos y detectar colisiones si el mundo es el 2 o el 3
            if (mundoActual == 2 || mundoActual == 3)
            {
                actualizarEnemigos();
                detectarColisiones();
            }

            // Actualizar estado del personaje
            personaje.actualizarInvulnerabilidad();
            mostrarVidas();
            Sleep(50);
        }
    }

    // Actualiza la posición del personaje al cambiar de mundo
    void actualizarPosicionPersonaje(int mundoAnterior, int nuevoMundo)
    {
        if (mundoAnterior == 1 && nuevoMundo == 2)
        {
            personaje.setPosicionInicial(WIDTH - 7, personaje.getY());
        }
        else if (mundoAnterior == 2 && nuevoMundo == 1)
        {
            personaje.setPosicionInicial(4, personaje.getY());
        }
        else if (mundoAnterior == 1 && nuevoMundo == 3)
        {
            personaje.setPosicionInicial(4, personaje.getY());
        }
        else if (mundoAnterior == 3 && nuevoMundo == 1)
        {
            personaje.setPosicionInicial(WIDTH - 7, personaje.getY());
        }
    }

    // Maneja la entrada del usuario
    void manejarEntrada(char tecla)
    {
        if (tecla == ESC)
        {
            gameOver = true;
        }
        else
        {
            personaje.manejarMovimiento(tecla);
        }
    }
};

#endif // JUEGO_H
