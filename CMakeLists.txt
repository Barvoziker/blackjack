cmake_minimum_required(VERSION 3.28)
project(blackjack C)

set(CMAKE_C_STANDARD 11)

# Ajouter les répertoires include
include_directories(include)

# Ajouter les fichiers source
set(SOURCES
    src/main.c
    src/carte.c
    src/jeu.c
)

# Créer l'exécutable
add_executable(blackjack ${SOURCES})

# Ajouter la bibliothèque windows pour la fonction Beep
if(WIN32)
    target_link_libraries(blackjack winmm)
endif()
