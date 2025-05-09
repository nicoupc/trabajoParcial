cmake_minimum_required(VERSION 3.31)
project(trabajoParcial)

set(CMAKE_CXX_STANDARD 20)

add_executable(trabajoParcial main.cpp
        Funciones.h
        Juego.h
        Personaje.h
        Enemigo.h
        Mundo.h
        Aliado.h)
