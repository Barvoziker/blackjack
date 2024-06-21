//
// Created by mathi on 14/06/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "carte.h"

void initialiserDeck(Carte *deck) {
    char *couleurs[] = {"Coeur", "Carreau", "Trefle", "Pique"};
    int index = 0;
    for (int c = 0; c < 4; c++) {
        for (int r = 1; r <= 13; r++) {
            deck[index].rang = r;
            deck[index].couleur = couleurs[c];
            index++;
        }
    }
}

void melangerDeck(Carte *deck) {
    srand(time(NULL));
    for (int i = 0; i < TAILLE_DECK; i++) {
        int j = rand() % TAILLE_DECK;
        Carte temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void initialiserMain(Main *main) {
    main->cartes = (Carte *)malloc(MAX_CARTES * sizeof(Carte));
    main->nbCartes = 0;
    main->score = 0;
}

void libererMain(Main *main) {
    free(main->cartes);
}

void ajouterCarte(Main *main, Carte carte) {
    if (main->nbCartes < MAX_CARTES) {
        main->cartes[main->nbCartes] = carte;
        main->nbCartes++;
        if (carte.rang > 10) {
            main->score += 10;
        } else {
            main->score += carte.rang;
        }
    }
}

void afficherMain(Main *main, const char *proprietaire) {
    printf("Main de %s: ", proprietaire);
    for (int i = 0; i < main->nbCartes; i++) {
        printf("%d de %s ", main->cartes[i].rang, main->cartes[i].couleur);
    }
    printf("Score: %d\n", main->score);
}

void afficherSeparation() {
    printf("\n----------------------------------------\n");
}
