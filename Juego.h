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
            // Verifica si las áreas del personaje y el enemigo se superponen
            if (personaje.getX() < enemigo.getX() + enemigo.getAncho() &&
                personaje.getX() + personaje.getAncho() > enemigo.getX() &&
                personaje.getY() < enemigo.getY() + enemigo.getAlto() &&
                personaje.getY() + personaje.getAlto() > enemigo.getY())
            {
                gameOver = true; // Termina el juego si hay colisión
                std::cout << "\n¡Colisión detectada! Fin del juego." << std::endl;
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
        enemigos.emplace_back(30, 10);
        enemigos.emplace_back(50, 15);
    }

    // Inicializa el juego
    void inicializar()
    {
        ocultarCursor();
        system("cls");
        mundo.dibujar();
        personaje.dibujar();
        for (const auto& enemigo : enemigos)
        {
            enemigo.dibujar();
        }
    }

    // Ejecuta el bucle principal del juego
    void buclePrincipal()
    {
        while (!gameOver)
        {
            if (_kbhit())
            {
                char tecla = _getch();
                manejarEntrada(tecla);
            }

            // Verificar si el personaje está fuera de los límites
            if (!mundo.estaDentroDemundo(personaje.getX(), personaje.getY()))
            {
                int nuevoMundo = mundo.manejarTransicion(personaje.getX(), personaje.getY());
                if (nuevoMundo != mundo.manejarTransicion(personaje.getX(), personaje.getY()))
                {
                    mundo.cambiarMundo(nuevoMundo);
                    personaje.setPosicionInicial(WIDTH / 2, HEIGHT / 2); // Reubica al personaje
                }
            }

            actualizarEnemigos();
            detectarColisiones();
            Sleep(50); // Controla la velocidad del juego
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
