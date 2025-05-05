#ifndef JUEGO_H
#define JUEGO_H

#include "Personaje.h"
#include "Enemigo.h"
#include "Mundo.h"
#include <vector>
#include <map>
#include <string>

class Juego
{
private:
    Personaje personaje;
    Mundo mundo;
    vector<Enemigo> enemigos;
    bool gameOver;
    map<string, int> inventario; // Inventario de recursos
    vector<pair<int, int>> recursosPosiciones; // Posiciones de los recursos
    vector<string> recursosTipos; // Tipos de recursos

    void inicializarRecursosTech()
    {
        if (mundo.getMundoActual() == 2)
        {
            recursosPosiciones.clear();
            recursosTipos.clear();

            // Generar 10 recursos en posiciones aleatorias
            vector<string> tipos = {"IA", "ES", "RB", "BD"};
            for (int i = 0; i < 8; ++i)
            {
                int x = generarAleatorio(5, WIDTH - 10); // Evitar bordes
                int y = generarAleatorio(5, HEIGHT - 5);
                recursosPosiciones.emplace_back(x, y);
                recursosTipos.push_back(tipos[i % tipos.size()]); // Ciclar entre los tipos
            }
        }
    }

    // Dibuja los recursos en el mundo 2
    void dibujarRecursos()
    {
        if (mundo.getMundoActual() == 2)
        {
            for (size_t i = 0; i < recursosPosiciones.size(); ++i)
            {
                gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second);
                cout << recursosTipos[i];
            }
        }
    }

    // Detecta colisiones con los recursos
    void detectarColisionesRecursos()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            // Verificar si el recurso está dentro del área del personaje
            if (personaje.getX() < recursosPosiciones[i].first + 1 &&
                personaje.getX() + personaje.getAncho() > recursosPosiciones[i].first &&
                personaje.getY() < recursosPosiciones[i].second + 1 &&
                personaje.getY() + personaje.getAlto() > recursosPosiciones[i].second)
            {
                // Borrar visualmente el recurso del mapa
                gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second);
                cout << ' ';

                // Incrementar el recurso en el inventario
                inventario[recursosTipos[i]]++;

                // Eliminar el recurso de las listas
                recursosPosiciones.erase(recursosPosiciones.begin() + i);
                recursosTipos.erase(recursosTipos.begin() + i);

                break; // Salir del bucle después de recoger un recurso
            }
        }
    }

    // Detecta colisiones entre los enemigos y los recursos
    void detectarColisionesEnemigosRecursos()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            for (const auto& enemigo : enemigos)
            {
                // Verificar si el enemigo está dentro del área del recurso
                if (enemigo.getX() < recursosPosiciones[i].first + 1 &&
                    enemigo.getX() + enemigo.getAncho() > recursosPosiciones[i].first &&
                    enemigo.getY() < recursosPosiciones[i].second + 1 &&
                    enemigo.getY() + enemigo.getAlto() > recursosPosiciones[i].second)
                {
                    // Borrar visualmente el recurso del mapa
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second);
                    cout << ' ';

                    // Eliminar el recurso de las listas
                    recursosPosiciones.erase(recursosPosiciones.begin() + i);
                    recursosTipos.erase(recursosTipos.begin() + i);

                    i--; // Ajustar el índice después de eliminar un recurso
                    break; // Salir del bucle interno
                }
            }
        }
    }

    // Muestra el inventario debajo de las vidas
    void mostrarInventario() const
    {
        int yOffset = 2; // Desplazamiento debajo de las vidas
        gotoxy(WIDTH + 5, yOffset); // Mostrar título
        cout << "RECURSOS TECNOLOGICOS:";
        gotoxy(WIDTH + 5, yOffset + 2);
        cout << "Inteligencia Artificial (IA): " << inventario.at("IA");
        gotoxy(WIDTH + 5, yOffset + 3);
        cout << "Energias Sostenibles (ES): " << inventario.at("ES");
        gotoxy(WIDTH + 5, yOffset + 4);
        cout << "Robotica (RB): " << inventario.at("RB");
        gotoxy(WIDTH + 5, yOffset + 5);
        cout << "Big Data (BD): " << inventario.at("BD");
    }

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

    void inicializarRecursosMundo3()
    {
        if (mundo.getMundoActual() == 3)
        {
            recursosPosiciones.clear();
            recursosTipos.clear();

            // Generar 8 recursos en posiciones aleatorias
            vector<string> tipos = {"e", "c", "t", "h"};
            for (int i = 0; i < 8; ++i)
            {
                int x = generarAleatorio(10, WIDTH - 5); // Evitar bordes
                int y = generarAleatorio(5, HEIGHT - 5);
                recursosPosiciones.emplace_back(x, y);
                recursosTipos.push_back(tipos[i % tipos.size()]); // Ciclar entre los tipos
            }
        }
    }

    void dibujarRecursosMundo3()
    {
        if (mundo.getMundoActual() == 3)
        {
            for (size_t i = 0; i < recursosPosiciones.size(); ++i)
            {
                gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second);
                cout << recursosTipos[i];
            }
        }
    }

    void detectarColisionesRecursosMundo3()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            // Verificar si el recurso está dentro del área del personaje
            if (personaje.getX() < recursosPosiciones[i].first + 1 &&
                personaje.getX() + personaje.getAncho() > recursosPosiciones[i].first &&
                personaje.getY() < recursosPosiciones[i].second + 1 &&
                personaje.getY() + personaje.getAlto() > recursosPosiciones[i].second)
            {
                // Borrar visualmente el recurso del mapa
                gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second);
                cout << ' ';

                // Incrementar el recurso en el inventario
                inventario[recursosTipos[i]]++;

                // Eliminar el recurso de las listas
                recursosPosiciones.erase(recursosPosiciones.begin() + i);
                recursosTipos.erase(recursosTipos.begin() + i);

                break; // Salir del bucle después de recoger un recurso
            }
        }
    }

    void mostrarInventarioMundo3() const
    {
        int yOffset = 9; // Desplazamiento debajo del inventario tecnológico
        gotoxy(WIDTH + 5, yOffset); // Mostrar título
        cout << "RECURSOS HUMANOS:";
        gotoxy(WIDTH + 5, yOffset + 2);
        cout << "empatia (e): " << inventario.at("e");
        gotoxy(WIDTH + 5, yOffset + 3);
        cout << "creatividad (c): " << inventario.at("c");
        gotoxy(WIDTH + 5, yOffset + 4);
        cout << "trabajo en equipo (t): " << inventario.at("t");
        gotoxy(WIDTH + 5, yOffset + 5);
        cout << "etica (h): " << inventario.at("h");
    }

public:
    Juego()
        : personaje(WIDTH / 2, HEIGHT / 2), gameOver(false)
    {
        // Inicializar inventario
        inventario["IA"] = 0;
        inventario["ES"] = 0;
        inventario["RB"] = 0;
        inventario["BD"] = 0;

        // Inicializar inventario para el mundo 3
        inventario["e"] = 0;
        inventario["h"] = 0;
        inventario["t"] = 0;
        inventario["c"] = 0;

        // Agregar enemigos iniciales
        enemigos.emplace_back(25, 5);
        enemigos.emplace_back(25, 20);
        enemigos.emplace_back(70, 5);
        enemigos.emplace_back(70, 20);
    }

    // Inicializa el juego
    void inicializar()
    {
        ocultarCursor();
        system("cls");
        mundo.dibujar();
        personaje.dibujar();

        if (mundo.getMundoActual() == 2)
        {
            inicializarRecursosTech();
            dibujarRecursos();
        }

        if (mundo.getMundoActual() == 3)
        {
            inicializarRecursosMundo3();
            dibujarRecursosMundo3();
        }

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
        cout << "VIDAS: " << personaje.getVidas();
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

                    if (mundoActual == 2)
                    {
                        inicializarRecursosTech();
                        dibujarRecursos();
                    }

                    if (mundoActual == 3)
                    {
                        inicializarRecursosMundo3();
                        dibujarRecursosMundo3();
                    }

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
                detectarColisionesEnemigosRecursos(); // Llamar a la nueva función
            }

            if (mundoActual == 2)
            {
                detectarColisionesRecursos();
            }

            if (mundoActual == 3)
            {
                detectarColisionesRecursosMundo3();
            }

            // Actualizar estado del personaje
            personaje.actualizarInvulnerabilidad();
            mostrarVidas();
            mostrarInventario();
            mostrarInventarioMundo3();
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
