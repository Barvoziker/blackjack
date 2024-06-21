//
// Created by mathi on 14/06/2024.
//

#ifndef BLACKJACK_CARTE_H
#define BLACKJACK_CARTE_H

#define TAILLE_DECK 52
#define MAX_CARTES 11

typedef struct {
    int rang;
    char *couleur;
} Carte;

typedef struct {
    Carte *cartes;
    int nbCartes;
    int score;
} Main;

void initialiserDeck(Carte *deck);
void melangerDeck(Carte *deck);
void initialiserMain(Main *main);
void libererMain(Main *main);
void ajouterCarte(Main *main, Carte carte);
void afficherMain(Main *main, const char *proprietaire);
void afficherSeparation();

#endif //BLACKJACK_CARTE_H
