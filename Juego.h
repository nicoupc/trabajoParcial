#ifndef JUEGO_H
#define JUEGO_H

#include "Personaje.h"
#include "Enemigo.h"
#include "Aliado.h"
#include "Mundo.h"
#include <vector> // Para usar std::vector
#include <map> // Para usar std::map
#include <string> // Para usar std::string
#include <utility> // Para usar std::pair
#include <algorithm> // Para usar std::all_of
#include <ctime> // Para usar std::time

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
    vector<bool> casillasUsadasRobot; // Para las casillas del robot
    vector<bool> casillasUsadasHospital; // Para las casillas del hospital
    vector<bool> casillasUsadasEstacion; // Para las casillas de la estación de energia sostenible
    vector<bool> casillasUsadasCentro; // Para las casillas del centro de investigacion
    Aliado aliado; // Objeto aliado
    Aliado aliado2; // Objeto aliado 2

    // Verifica si una posicion esta ocupada por otro recurso
    bool posicionOcupada(int x, int y, const vector<pair<int, int>>& posiciones, int ancho = 4, int alto = 4)
    {
        // Verificar si la posicion se superpone con otros recursos
        for (const auto& pos : posiciones)
        {
            if (x < pos.first + ancho && x + ancho > pos.first &&
                y < pos.second + alto && y + alto > pos.second)
            {
                return true; // La posicion esta ocupada
            }
        }

        // Verificar si la posicion se superpone con el aliado
        if (x < aliado.getX() + aliado.getAncho() && x + ancho > aliado.getX() &&
            y < aliado.getY() + aliado.getAlto() && y + alto > aliado.getY())
        {
            return true; // La posicion esta ocupada por el aliado
        }

        // Verificar si la posicion se superpone con el aliado2
        if (aliado2.estaVisible() && // Solo verificar si el aliado2 esta visible
            x < aliado2.getX() + aliado2.getAncho() && x + ancho > aliado2.getX() &&
            y < aliado2.getY() + aliado2.getAlto() && y + alto > aliado2.getY())
        {
            return true; // La posicion esta ocupada por el aliado2
        }

        return false; // La posicion esta libre
    }

    // Modificar la generacion de recursos
    void inicializarRecursosTech()
    {
        if (mundo.getMundoActual() == 2)
        {
            recursosPosiciones.clear();
            recursosTipos.clear();

            vector<string> tipos = {"IA", "ES", "RB", "BD"};
            for (int i = 0; i < 8; ++i)
            {
                int x, y;
                do
                {
                    x = generarAleatorio(5, WIDTH - 10); // Evitar bordes
                    y = generarAleatorio(5, HEIGHT - 5);
                }
                while (posicionOcupada(x, y, recursosPosiciones)); // Reintentar si esta ocupada

                recursosPosiciones.emplace_back(x, y); // Agregar posicion
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

                if (recursosTipos[i] == "RB")
                {
                    cout << " [] ";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "[==]";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << " [] ";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(RB)";
                }
                else if (recursosTipos[i] == "IA")
                {
                    cout << " /\\ ";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "<@@>";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << " \\/ ";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(IA)";
                }
                else if (recursosTipos[i] == "ES")
                {
                    cout << "(~~)";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "(~~)";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << " || ";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(ES)";
                }
                else if (recursosTipos[i] == "BD")
                {
                    cout << "+--+";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "|##|";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << "-__-";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(BD)";
                }
            }
        }
    }

    // Detecta colisiones con los recursos
    void detectarColisionesRecursos()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            // Verificar si el personaje colisiona con cualquier dimension del recurso
            if (personaje.getX() + personaje.getAncho() > recursosPosiciones[i].first &&
                personaje.getX() < recursosPosiciones[i].first + 4 && // Ancho del recurso
                personaje.getY() + personaje.getAlto() > recursosPosiciones[i].second &&
                personaje.getY() < recursosPosiciones[i].second + 4) // Alto del recurso
            {
                // Borrar visualmente el recurso del mapa
                for (int y = 0; y < 4; ++y)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        gotoxy(recursosPosiciones[i].first + x, recursosPosiciones[i].second + y);
                        cout << ' ';
                    }
                }

                // Incrementar el recurso en el inventario
                inventario[recursosTipos[i]]++;

                // Eliminar el recurso de las listas
                recursosPosiciones.erase(recursosPosiciones.begin() + i);
                recursosTipos.erase(recursosTipos.begin() + i);

                break; // Salir del bucle despues de recoger un recurso
            }
        }
    }

    // Detecta colisiones entre los enemigos y los recursos
    void detectarColisionesEnemigosRecursos()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            bool recursoEliminado = false;

            for (const auto& enemigo : enemigos)
            {
                // Verificar si el enemigo esta dentro del area del recurso
                if (enemigo.getX() < recursosPosiciones[i].first + 4 && // Ancho del recurso
                    enemigo.getX() + enemigo.getAncho() > recursosPosiciones[i].first &&
                    enemigo.getY() < recursosPosiciones[i].second + 4 && // Alto del recurso
                    enemigo.getY() + enemigo.getAlto() > recursosPosiciones[i].second)
                {
                    // Borrar visualmente el recurso del mapa
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second);
                    for (int y = 0; y < 4; ++y) // Borra el area del recurso
                    {
                        for (int x = 0; x < 4; ++x)
                        {
                            gotoxy(recursosPosiciones[i].first + x, recursosPosiciones[i].second + y);
                            cout << ' ';
                        }
                    }

                    // Eliminar el recurso de las listas
                    recursosPosiciones.erase(recursosPosiciones.begin() + i);
                    recursosTipos.erase(recursosTipos.begin() + i);

                    recursoEliminado = true;
                    break; // Salir del bucle interno
                }
            }

            if (recursoEliminado)
            {
                i--; // Ajustar el indice despues de eliminar un recurso
            }
        }
    }

    // Muestra el inventario debajo de las vidas
    void mostrarInventario() const
    {
        int yOffset = 2; // Desplazamiento debajo de las vidas
        gotoxy(WIDTH + 5, yOffset); // Mostrar titulo
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
                    personaje.activarInvulnerabilidad(20); // Activa invulnerabilidad por 30 ciclos

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
            enemigo.moverAleatorio(enemigos, aliado, aliado2);
        }
    }


    void inicializarRecursosMundo3()
    {
        if (mundo.getMundoActual() == 3)
        {
            recursosPosiciones.clear();
            recursosTipos.clear();

            vector<string> tipos = {"e", "c", "t", "h"};
            for (int i = 0; i < 8; ++i)
            {
                int x, y;
                do
                {
                    x = generarAleatorio(10, WIDTH - 5); // Evitar bordes
                    y = generarAleatorio(5, HEIGHT - 5);
                }
                while (posicionOcupada(x, y, recursosPosiciones)); // Reintentar si esta ocupada

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

                if (recursosTipos[i] == "e") // Empatia
                {
                    cout << "+--+";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "|<3|";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << "|__|";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(e )";
                }
                else if (recursosTipos[i] == "t") // Trabajo en equipo
                {
                    cout << "()()";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "||||";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << "||||";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(t )";
                }
                else if (recursosTipos[i] == "h") // etica
                {
                    cout << "(^^)";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "(- )";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << "(h )";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "    ";
                }
                else if (recursosTipos[i] == "c") // Creatividad
                {
                    cout << " /\\ ";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 1);
                    cout << "/~~\\";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 2);
                    cout << "|  |";
                    gotoxy(recursosPosiciones[i].first, recursosPosiciones[i].second + 3);
                    cout << "(c )";
                }
            }
        }
    }

    void detectarColisionesRecursosMundo3()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            // Verificar si el personaje colisiona con cualquier dimension del recurso humano
            if (personaje.getX() + personaje.getAncho() > recursosPosiciones[i].first &&
                personaje.getX() < recursosPosiciones[i].first + 4 && // Ancho del recurso
                personaje.getY() + personaje.getAlto() > recursosPosiciones[i].second &&
                personaje.getY() < recursosPosiciones[i].second + 4) // Alto del recurso
            {
                // Borrar visualmente el recurso del mapa
                for (int y = 0; y < 4; ++y)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        gotoxy(recursosPosiciones[i].first + x, recursosPosiciones[i].second + y);
                        cout << ' ';
                    }
                }

                // Incrementar el recurso en el inventario
                inventario[recursosTipos[i]]++;

                // Eliminar el recurso de las listas
                recursosPosiciones.erase(recursosPosiciones.begin() + i);
                recursosTipos.erase(recursosTipos.begin() + i);

                break; // Salir del bucle despues de recoger un recurso
            }
        }
    }

    void mostrarInventarioMundo3() const
    {
        int yOffset = 9; // Desplazamiento debajo del inventario tecnologico
        gotoxy(WIDTH + 5, yOffset); // Mostrar titulo
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

    void dibujarCuadradoYCasillasRobot() const
    {
        int xInicio = 10, yInicio = 3;
        int ancho = 23, alto = 8;

        // Dibujar las casillas con recursos iniciales o [*] si ya fueron usadas
        int casillasX = xInicio + 5, casillasY = yInicio + alto + 1;
        vector<string> recursosIniciales = {"[RB]", "[IA]", "[e ]"};
        for (int i = 0; i < 3; ++i)
        {
            gotoxy(casillasX + i * 5, casillasY);
            if (casillasUsadasRobot[i])
            {
                cout << "[* ]"; // Dibujar casilla usada
            }
            else
            {
                cout << recursosIniciales[i]; // Dibujar recurso inicial
            }
        }

        // Verificar si todas las casillas estan usadas
        bool todasUsadas = all_of(casillasUsadasRobot.begin(), casillasUsadasRobot.end(),
                                  [](bool usada) { return usada; });

        if (todasUsadas)
        {
            gotoxy(11, 2);
            cout << "\"ROBOT  HUMANITARIO\"";
            // Dibujar el personaje ASCII
            color(8); // Cambiar color a gris
            gotoxy(xInicio, yInicio);
            cout << " _(\\    |@@|           ";
            gotoxy(xInicio, yInicio + 1);
            cout << "(__/\\__ \\--/ __        ";
            gotoxy(xInicio, yInicio + 2);
            cout << "   \\___|----|  |   __  ";
            gotoxy(xInicio, yInicio + 3);
            cout << "       \\ }{ /\\ )_ / _\\ ";
            gotoxy(xInicio, yInicio + 4);
            cout << "       /\\__/\\ \\__O (__ ";
            gotoxy(xInicio, yInicio + 5);
            cout << "      (--/\\--)    \\__/ ";
            gotoxy(xInicio, yInicio + 6);
            cout << "      _)(  )(_         ";
            gotoxy(xInicio, yInicio + 7);
            cout << "     `---''---`        ";
            color(7); // Cambiar color a blanco
        }
        else
        {
            // Dibujar el cuadrado vacio
            for (int x = xInicio; x < xInicio + ancho; ++x)
            {
                gotoxy(x, yInicio);
                cout << "-";
                gotoxy(x, yInicio + alto - 1);
                cout << "-";
            }
            for (int y = yInicio + 1; y < yInicio + alto - 1; ++y)
            {
                gotoxy(xInicio, y);
                cout << "|";
                gotoxy(xInicio + ancho - 1, y);
                cout << "|";
            }
        }
    }

    void manejarDepositoRecursosRobot()
    {
        int casillasX = 15, casillasY = 12; // Coordenadas iniciales de las casillas
        vector<string> recursosCasillas = {"RB", "IA", "e"}; // Recursos iniciales en las casillas

        for (int i = 0; i < 3; ++i)
        {
            // Detectar si el personaje esta cerca de una casilla
            if (abs(personaje.getX() - (casillasX + i * 5)) <= 1 &&
                abs(personaje.getY() - casillasY) <= 1)
            {
                string recurso = recursosCasillas[i];
                if (recurso != "*" && inventario[recurso] > 0 && !casillasUsadasRobot[i])
                {
                    // Descontar el recurso del inventario
                    inventario[recurso]--;

                    // Marcar la casilla como usada
                    casillasUsadasRobot[i] = true;
                }
            }
        }
    }

    void detectarColisionesCuadradoYCasillasRobot()
    {
        int xInicio = 10, yInicio = 3;
        int ancho = 25, alto = 8;
        int casillasX = 15, casillasY = 12;

        // Bloquear el paso sobre el cuadrado
        if (personaje.getX() + personaje.getAncho() > xInicio &&
            personaje.getX() < xInicio + ancho &&
            personaje.getY() + personaje.getAlto() > yInicio &&
            personaje.getY() < yInicio + alto)
        {
            personaje.mover(-1, 0); // Evitar que atraviese el cuadrado
        }

        // Bloquear el paso sobre las casillas
        for (int i = 0; i < 3; ++i)
        {
            if (personaje.getX() + personaje.getAncho() > casillasX + i * 5 &&
                personaje.getX() < casillasX + i * 5 + 3 &&
                personaje.getY() + personaje.getAlto() > casillasY &&
                personaje.getY() < casillasY + 1)
            {
                personaje.mover(-1, 0); // Evitar que atraviese las casillas
            }
        }
    }

    void dibujarCuadroYCasillasHospital() const
    {
        int xInicio = 60, yInicio = 3;
        int ancho = 23, alto = 8;

        // Dibujar las casillas con recursos iniciales o [*] si ya fueron usadas
        int casillasX = xInicio + 5, casillasY = yInicio + alto + 1;
        vector<string> recursosIniciales = {"[IA]", "[e ]", "[t ]"};
        for (int i = 0; i < 3; ++i)
        {
            gotoxy(casillasX + i * 5, casillasY);
            if (casillasUsadasHospital[i])
            {
                cout << "[* ]"; // Dibujar casilla usada
            }
            else
            {
                cout << recursosIniciales[i]; // Dibujar recurso inicial
            }
        }

        // Verificar si todas las casillas estan usadas
        bool todasUsadas = all_of(casillasUsadasHospital.begin(), casillasUsadasHospital.end(),
                                  [](bool usada) { return usada; });

        if (todasUsadas)
        {
            gotoxy(65, 2);
            cout << "\"HOSPITAL TECNOLOGICO\"";
            // Dibujar el arte ASCII del hospital
            gotoxy(xInicio, yInicio);
            cout << "      ___________________";
            gotoxy(xInicio, yInicio + 1);
            cout << "     |        _| |_     |";
            gotoxy(xInicio, yInicio + 2);
            cout << "     |       |_   _|    |";
            gotoxy(xInicio, yInicio + 3);
            cout << " ____|_________|_|______|";
            gotoxy(xInicio, yInicio + 4);
            cout << "|               ________|";
            gotoxy(xInicio, yInicio + 5);
            cout << "|   __          |-------|";
            gotoxy(xInicio, yInicio + 6);
            cout << "|  |  |         |       |";
            gotoxy(xInicio, yInicio + 7);
            cout << "|__|  |_________|_______|";
        }
        else
        {
            // Dibujar el cuadrado vacio
            for (int x = xInicio; x < xInicio + ancho; ++x)
            {
                gotoxy(x, yInicio);
                cout << "-";
                gotoxy(x, yInicio + alto - 1);
                cout << "-";
            }
            for (int y = yInicio + 1; y < yInicio + alto - 1; ++y)
            {
                gotoxy(xInicio, y);
                cout << "|";
                gotoxy(xInicio + ancho - 1, y);
                cout << "|";
            }
        }
    }

    void manejarDepositoRecursosHospital()
    {
        int casillasX = 72, casillasY = 12; // Coordenadas iniciales de las casillas
        vector<string> recursosCasillas = {"IA", "e", "t"}; // Recursos iniciales en las casillas

        for (int i = 0; i < 3; ++i)
        {
            // Detectar si el personaje esta cerca de una casilla
            if (abs(personaje.getX() - (casillasX + i * 5)) <= 1 &&
                abs(personaje.getY() - casillasY) <= 1)
            {
                string recurso = recursosCasillas[i];
                if (recurso != "*" && inventario[recurso] > 0 && !casillasUsadasHospital[i])
                {
                    // Descontar el recurso del inventario
                    inventario[recurso]--;

                    // Marcar la casilla como usada
                    casillasUsadasHospital[i] = true;
                }
            }
        }
    }

    void detectarColisionesCuadroYCasillasHospital()
    {
        int xInicio = 60, yInicio = 3;
        int ancho = 25, alto = 8;
        int casillasX = 65, casillasY = 12;

        // Bloquear el paso sobre el cuadrado
        if (personaje.getX() + personaje.getAncho() > xInicio &&
            personaje.getX() < xInicio + ancho &&
            personaje.getY() + personaje.getAlto() > yInicio &&
            personaje.getY() < yInicio + alto)
        {
            personaje.mover(-1, 0); // Evitar que atraviese el cuadrado
        }

        // Bloquear el paso sobre las casillas
        for (int i = 0; i < 3; ++i)
        {
            if (personaje.getX() + personaje.getAncho() > casillasX + i * 5 &&
                personaje.getX() < casillasX + i * 5 + 3 &&
                personaje.getY() + personaje.getAlto() > casillasY &&
                personaje.getY() < casillasY + 1)
            {
                personaje.mover(-1, 0); // Evitar que atraviese las casillas
            }
        }
    }

    void dibujarCuadroYCasillasEstacion() const
    {
        int xInicio = 10, yInicio = HEIGHT - 12; // Coordenadas iniciales
        int ancho = 23, alto = 8;

        // Dibujar las casillas con recursos iniciales o [*] si ya fueron usadas
        int casillasX = xInicio + 5, casillasY = yInicio - 2; // Casillas arriba del cuadro
        vector<string> recursosIniciales = {"[ES]", "[t ]", "[e ]"};
        for (int i = 0; i < 3; ++i)
        {
            gotoxy(casillasX + i * 5, casillasY);
            if (casillasUsadasEstacion[i])
            {
                cout << "[* ]"; // Dibujar casilla usada
            }
            else
            {
                cout << recursosIniciales[i]; // Dibujar recurso inicial
            }
        }

        // Verificar si todas las casillas están usadas
        bool todasUsadas = all_of(casillasUsadasEstacion.begin(), casillasUsadasEstacion.end(),
                                  [](bool usada) { return usada; });

        if (todasUsadas)
        {
            gotoxy(10, yInicio);
            cout << "\"ESTACION DE ENERGIA SOSTENIBLE\"";
            // Dibujar el arte ASCII de la estación
            color(2); // Cambiar color a verde
            gotoxy(xInicio, yInicio + 1);
            cout << "      ____|     |____    ";
            gotoxy(xInicio, yInicio + 2);
            cout << "     |____|_____|____|   ";
            gotoxy(xInicio, yInicio + 3);
            cout << "  ___/ /  |     |  \\ \\__ ";
            gotoxy(xInicio, yInicio + 4);
            cout << " |    ____|_____|____   |";
            gotoxy(xInicio, yInicio + 5);
            cout << " |  []      ___      [] |";
            gotoxy(xInicio, yInicio + 6);
            cout << " |  []     |   |     [] |";
            gotoxy(xInicio, yInicio + 7);
            cout << " |  []     |   |     [] |";
            gotoxy(xInicio, yInicio + 8);
            cout << " |_________|   |________|";
            color(7); // Cambiar color a blanco
        }
        else
        {
            // Dibujar el cuadro vacío
            for (int x = xInicio; x < xInicio + ancho; ++x)
            {
                gotoxy(x, yInicio);
                cout << "-";
                gotoxy(x, yInicio + alto - 1);
                cout << "-";
            }
            for (int y = yInicio + 1; y < yInicio + alto - 1; ++y)
            {
                gotoxy(xInicio, y);
                cout << "|";
                gotoxy(xInicio + ancho - 1, y);
                cout << "|";
            }
        }
    }

    void manejarDepositoRecursosEstacion()
    {
        int casillasX = 15, casillasY = HEIGHT - 14; // Coordenadas iniciales de las casillas
        vector<string> recursosCasillas = {"ES", "t", "e"}; // Recursos iniciales en las casillas

        for (int i = 0; i < 3; ++i)
        {
            // Detectar si la parte inferior del personaje está cerca de una casilla
            if (abs((personaje.getY() + personaje.getAlto()) - casillasY) <= 1 &&
                abs(personaje.getX() - (casillasX + i * 5)) <= 1)
            {
                string recurso = recursosCasillas[i];
                if (recurso != "*" && inventario[recurso] > 0 && !casillasUsadasEstacion[i])
                {
                    // Descontar el recurso del inventario
                    inventario[recurso]--;

                    // Marcar la casilla como usada
                    casillasUsadasEstacion[i] = true;
                }
            }
        }
    }

    void detectarColisionesCuadroYCasillasEstacion()
    {
        int xInicio = 10, yInicio = HEIGHT - 12;
        int ancho = 25, alto = 8;
        int casillasX = 15, casillasY = HEIGHT - 14;

        // Bloquear el paso sobre el cuadro
        if (personaje.getX() + personaje.getAncho() > xInicio &&
            personaje.getX() < xInicio + ancho &&
            personaje.getY() + personaje.getAlto() > yInicio &&
            personaje.getY() < yInicio + alto)
        {
            personaje.mover(-1, 0); // Evitar que atraviese el cuadro
        }

        // Bloquear el paso sobre las casillas
        for (int i = 0; i < 3; ++i)
        {
            if (personaje.getX() + personaje.getAncho() > casillasX + i * 5 &&
                personaje.getX() < casillasX + i * 5 + 3 &&
                personaje.getY() + personaje.getAlto() > casillasY &&
                personaje.getY() < casillasY + 1)
            {
                personaje.mover(-1, 0); // Evitar que atraviese las casillas
            }
        }
    }

    void detectarColisionesAliado()
    {
        static int contadorVelocidad = 0; // Contador para la duracion del aumento de velocidad

        // Detectar colision entre el personaje y el aliado
        if (personaje.getX() < aliado.getX() + 5 &&
            personaje.getX() + personaje.getAncho() > aliado.getX() &&
            personaje.getY() < aliado.getY() + 5 &&
            personaje.getY() + personaje.getAlto() > aliado.getY())
        {
            if (contadorVelocidad == 0) // Solo incrementar si no esta activo
            {
                personaje.setVelocidad(2); // Incrementar velocidad (dx y dy en 2 caracteres)
                contadorVelocidad = 100;
            }
            // Evitar que el personaje atraviese al aliado
            personaje.mover(-1, 0); // Evitar que atraviese el aliado
        }

        // Reducir el contador y restablecer la velocidad si se agota
        if (contadorVelocidad > 0)
        {
            contadorVelocidad--;
            if (contadorVelocidad == 0)
            {
                personaje.setVelocidad(1); // Restablecer velocidad normal
            }
        }
        aliado.dibujar(); // Dibujar el aliado
    }

    void detectarColisionesAliado2()
    {
        if (aliado2.estaVisible() &&
            personaje.getX() < aliado2.getX() + aliado2.getAncho() &&
            personaje.getX() + personaje.getAncho() > aliado2.getX() &&
            personaje.getY() < aliado2.getY() + aliado2.getAlto() &&
            personaje.getY() + personaje.getAlto() > aliado2.getY())
        {
            personaje.sumarVida(); // Incrementar una vida
            aliado2.ocultar(); // Ocultar el aliado
        }
    }

    void detectarColisionesEnemigosRecursosHumanos()
    {
        for (size_t i = 0; i < recursosPosiciones.size(); ++i)
        {
            bool recursoEliminado = false;

            for (const auto& enemigo : enemigos)
            {
                // Verificar si el enemigo colisiona con el recurso humano
                if (enemigo.getX() < recursosPosiciones[i].first + 4 && // Ancho del recurso
                    enemigo.getX() + enemigo.getAncho() > recursosPosiciones[i].first &&
                    enemigo.getY() < recursosPosiciones[i].second + 4 && // Alto del recurso
                    enemigo.getY() + enemigo.getAlto() > recursosPosiciones[i].second)
                {
                    // Borrar visualmente el recurso del mapa
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int x = 0; x < 4; ++x)
                        {
                            gotoxy(recursosPosiciones[i].first + x, recursosPosiciones[i].second + y);
                            cout << ' ';
                        }
                    }

                    // Eliminar el recurso de las listas
                    recursosPosiciones.erase(recursosPosiciones.begin() + i);
                    recursosTipos.erase(recursosTipos.begin() + i);

                    recursoEliminado = true;
                    break; // Salir del bucle interno
                }
            }

            if (recursoEliminado)
            {
                i--; // Ajustar el indice despues de eliminar un recurso
            }
        }
    }

public:
    Juego()
        : personaje(WIDTH / 2, HEIGHT / 2), gameOver(false), aliado(50, 1), aliado2(50, 30, true)
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

        // Inicializar estados de las casillas
        // casillasUsadasRobot = {false, false, false};
        casillasUsadasRobot = {true, true, true}; // Para pruebas
        // casillasUsadasHospital = {false, false, false};
        casillasUsadasHospital = {true, true, true}; // Para pruebas
        casillasUsadasEstacion = {false, false, false};
        // casillasUsadasEstacion = {true, true, true}; // Para pruebas
        casillasUsadasCentro = {false, false, false};

        // Agregar enemigos iniciales
        enemigos.emplace_back(25, 5);
        enemigos.emplace_back(25, 20);
        enemigos.emplace_back(70, 5);
        enemigos.emplace_back(70, 20);
        enemigos.emplace_back(WIDTH / 2, HEIGHT / 2);
    }

    // Inicializa el juego
    void inicializar()
    {
        ocultarCursor();
        system("cls");
        mundo.dibujar();
        personaje.dibujar();
    }

    // Muestra el numero de vidas en la parte derecha de la pantalla
    void mostrarVidas() const
    {
        gotoxy(WIDTH + 5, 0); // Posiciona el texto en el borde derecho
        cout << "VIDAS: " << personaje.getVidas();
    }

    void mostrarMensajeGameOver(const string& mensaje)
    {
        system("cls");
        gotoxy(WIDTH / 2 - 5, HEIGHT / 2 - 1);
        cout << "GAME OVER";
        gotoxy(WIDTH / 2 - mensaje.size() / 2, HEIGHT / 2);
        cout << mensaje;
        Sleep(3000); // Esperar 2 segundos
        system("cls");
    }

    // Ejecuta el bucle principal del juego
    void buclePrincipal()
    {
        int mundoActual = mundo.getMundoActual();

        time_t tiempoInicio = time(0); // Registrar el tiempo de inicio
        int tiempoNivel = 120; // Tiempo total del nivel en segundos

        while (!gameOver)
        {
            // Calcular el tiempo restante
            time_t tiempoActual = time(0);
            int tiempoRestante = tiempoNivel - difftime(tiempoActual, tiempoInicio);

            if (tiempoRestante <= 0)
            {
                gameOver = true; // Terminar el juego si el tiempo se agota
                mostrarMensajeGameOver("Se acabo el tiempo!");
                break;
            }

            // Mostrar el tiempo restante
            mostrarTiempo(tiempoRestante);

            // Manejar entrada del usuario
            if (_kbhit())
            {
                char tecla = _getch();
                manejarEntrada(tecla);
            }

            // Manejar transicion entre mundos
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
                        aliado.dibujar();
                        aliado2.dibujar();
                    }

                    if (mundoActual == 3)
                    {
                        inicializarRecursosMundo3();
                        dibujarRecursosMundo3();
                        aliado.dibujar();
                        aliado2.dibujar();
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
                detectarColisionesEnemigosRecursos();
                aliado.dibujar();
                aliado2.dibujar();
                detectarColisionesAliado(); // Detectar colisiones con el aliado
                detectarColisionesAliado2(); // Detectar colisiones con el aliado 2
                detectarColisionesEnemigosRecursosHumanos(); // Detectar colisiones con recursos humanos
            }

            if (mundoActual == 2)
            {
                detectarColisionesRecursos();
            }

            if (mundoActual == 3)
            {
                detectarColisionesRecursosMundo3();
            }

            // Mostrar y manejar el cuadrado y casillas solo en el mundo 1
            if (mundoActual == 1)
            {
                dibujarCuadradoYCasillasRobot();
                manejarDepositoRecursosRobot();
                detectarColisionesCuadradoYCasillasRobot();
                dibujarCuadroYCasillasHospital();
                manejarDepositoRecursosHospital();
                detectarColisionesCuadroYCasillasHospital();
                dibujarCuadroYCasillasEstacion();
                manejarDepositoRecursosEstacion();
                detectarColisionesCuadroYCasillasEstacion();
            }

            if (personaje.getVidas() == 0)
            {
                mostrarMensajeGameOver("Te quedaste sin vidas!");
            }

            // Actualizar estado del personaje
            personaje.actualizarInvulnerabilidad();
            mostrarVidas();
            mostrarInventario();
            mostrarInventarioMundo3();
            Sleep(50);
        }
    }

    // Actualiza la posicion del personaje al cambiar de mundo
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

    void mostrarTiempo(int tiempoRestante)
    {
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        gotoxy(WIDTH + 5, 17); // Posicionar el texto en la consola
        cout << "TIEMPO: " << minutos << ":" << (segundos < 10 ? "0" : "") << segundos;
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
