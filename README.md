Voici le README avec les deux configurations, CMakeLists.txt et Makefile :

---

# Projet Blackjack en C

## Présentation du Projet

Ce projet est une implémentation du jeu de Blackjack en langage C. Il a été développé pour permettre aux joueurs de miser et de jouer contre la banque selon les règles classiques du Blackjack.

## Fichiers du Projet

- `src/main.c`
- `src/carte.c`
- `src/jeu.c`
- `src/son.c`
- `include/carte.h`
- `include/jeu.h`
- `include/main.h`
- `include/son.h`

## Compilation du Projet

### Utilisation de CMake

Nous avons utilisé CMake pour la gestion de la compilation du projet. Voici le fichier CMakeLists.txt utilisé :

#### CMakeLists.txt

```cmake
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
```

#### Instructions de Compilation avec CMake

1. **Générer les fichiers de build** :
   ```sh
   cmake -S . -B build
   ```

2. **Compiler le projet** :
   ```sh
   cmake --build build
   ```

### Utilisation de Make

Pour ceux qui préfèrent utiliser un Makefile traditionnel, voici le fichier Makefile utilisé :

#### Makefile

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -O0 -Iinclude

all: blackjack

blackjack: src/main.o src/carte.o src/jeu.o src/son.o
	$(CC) $(CFLAGS) -o blackjack src/main.o src/carte.o src/jeu.o src/son.o -lwinmm

src/main.o: src/main.c include/main.h include/jeu.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/carte.o: src/carte.c include/carte.h
	$(CC) $(CFLAGS) -c src/carte.c -o src/carte.o

src/jeu.o: src/jeu.c include/jeu.h include/carte.h include/son.h
	$(CC) $(CFLAGS) -c src/jeu.c -o src/jeu.o

src/son.o: src/son.c include/son.h
	$(CC) $(CFLAGS) -c src/son.c -o src/son.o

clean:
	del src\*.o blackjack
```

#### Instructions de Compilation avec Make

1. **Compiler le projet** :
   ```sh
   make
   ```

2. **Nettoyer les fichiers objets et l'exécutable** :
   ```sh
   make clean
   ```

## Analyse de la Mémoire

### Pourquoi nous n'avons pas utilisé Valgrind

Initialement, nous avons prévu d'utiliser Valgrind pour analyser les fuites de mémoire de notre application. Cependant, après avoir passé beaucoup de temps à essayer de faire fonctionner Valgrind, nous avons découvert que Valgrind n'est pas supporté sous Windows.

### Utilisation de Dr. Memory

En remplacement de Valgrind, nous avons utilisé Dr. Memory, un outil de détection de fuites de mémoire et d'erreurs similaire à Valgrind, mais conçu pour fonctionner sous Windows.

#### Commande pour exécuter Dr. Memory

Pour analyser notre application avec Dr. Memory, nous avons utilisé la commande suivante :

```sh
drmemory -- ./blackjack
```

### Résultats de l'Analyse

Lors de l'analyse avec Dr. Memory, nous avons détecté une fuite de mémoire :

```
~~Dr.M~~ Error #1: UNADDRESSABLE ACCESS beyond top of stack: reading 0x00000076fbdff740-0x00000076fbdff748 8 byte(s)
~~Dr.M~~ # 0 .text
~~Dr.M~~ # 1 _pei386_runtime_relocator
~~Dr.M~~ # 2 __tmainCRTStartup
~~Dr.M~~ # 3 .l_start
~~Dr.M~~ # 4 ntdll.dll!RtlUserThreadStart
~~Dr.M~~ Note: @0:00:00.250 in thread 28968
~~Dr.M~~ Note: 0x00000076fbdff740 refers to 776 byte(s) beyond the top of the stack 0x00000076fbdffa48
~~Dr.M~~ Note: instruction: or     $0x0000000000000000 (%rcx) -> (%rcx)
```

Nous avons identifié une erreur d'accès mémoire ("UNADDRESSABLE ACCESS beyond top of stack"), mais faute de temps, nous n'avons pas pu approfondir pour identifier précisément l'origine de cette fuite.

## Environnements de Développement

- **Gaël** a utilisé VSCode avec les configurations de compilation CMake.
- **Mathis** a utilisé CLion avec les configurations CMake.