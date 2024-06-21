cmake_minimum_required(VERSION 3.28)
project(blackjack C)

set(CMAKE_C_STANDARD 11)

add_executable(blackjack main.c
        carte.h
        carte.c
        main.h
        jeu.c)
