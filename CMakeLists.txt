cmake_minimum_required(VERSION 3.28)
project(blackjack C)

# Définir le standard C
set(CMAKE_C_STANDARD 11)

# Ajouter les options de compilation
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g -O0")

# Ajouter les répertoires include
include_directories(include)

# Ajouter les fichiers source
set(SOURCES
        src/main.c
        src/carte.c
        src/jeu.c
        src/son.c
)

# Créer l'exécutable
add_executable(blackjack ${SOURCES})

# Ajouter la bibliothèque windows pour la fonction Beep
if(WIN32)
    target_link_libraries(blackjack winmm)
endif()

# Définir une cible pour nettoyer les fichiers objets (utiliser un nom différent)
add_custom_target(distclean
        COMMAND ${CMAKE_COMMAND} -E remove -f src/main.o src/carte.o src/jeu.o src/son.o
        COMMENT "Nettoyage des fichiers objets."
)
