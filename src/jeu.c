#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "carte.h"
#include "son.h"

void jouerBlackjack()
{
    Carte deck[TAILLE_DECK];
    Main joueur, croupier, splitMain;
    int indexDeck = 0;
    int banque = 1000; // La banque initiale du joueur
    int mise;
    int insurance = 0;

    initialiserDeck(deck);
    melangerDeck(deck);
    initialiserMain(&joueur);
    initialiserMain(&croupier);
    initialiserMain(&splitMain);

    while (banque > 0)
    {
        afficherSeparation(banque);
        printf("Vous avez %d$ dans votre banque.\n", banque);
        printf("Combien voulez-vous miser? ");
        scanf("%d", &mise);

        // Nettoyer l'input du joueur
        while (getchar() != '\n')
            ;

        if (mise <= 0)
        {
            printf("Mise invalide. Veuillez miser un montant positif.\n");
            continue;
        }

        if (mise > banque)
        {
            printf("Mise invalide. Vous n'avez pas assez d'argent.\n");
            continue;
        }

        // Réinitialiser les mains pour la prochaine partie
        joueur.nbCartes = 0;
        joueur.score = 0;
        croupier.nbCartes = 0;
        croupier.score = 0;
        splitMain.nbCartes = 0;
        splitMain.score = 0;

        // Distribution initiale
        ajouterCarte(&joueur, deck[indexDeck++]);
        ajouterCarte(&croupier, deck[indexDeck++]);
        ajouterCarte(&joueur, deck[indexDeck++]);
        ajouterCarte(&croupier, deck[indexDeck++]);

        // Vérifier pour l'assurance
        if (croupier.cartes[0].rang == 1)
        {
            printf("Le croupier montre un As. Voulez-vous prendre une assurance (y/n)? ");
            char choixAssurance;
            scanf(" %c", &choixAssurance);
            if (choixAssurance == 'y' || choixAssurance == 'Y')
            {
                insurance = mise / 2;
                banque -= insurance;
            }
        }

        // Vérifier pour le split
        if (joueur.cartes[0].rang == joueur.cartes[1].rang)
        {
            printf("Vous avez une paire. Voulez-vous faire un split (y/n)? ");
            char choixSplit;
            scanf(" %c", &choixSplit);
            if (choixSplit == 'y' || choixSplit == 'Y')
            {
                splitMain.cartes[0] = joueur.cartes[1];
                splitMain.nbCartes = 1;
                splitMain.score = joueur.cartes[1].rang > 10 ? 10 : joueur.cartes[1].rang;
                joueur.nbCartes = 1;
                joueur.score = joueur.cartes[0].rang > 10 ? 10 : joueur.cartes[0].rang;
                banque -= mise;
            }
        }

        // Jouer la main principale
        char choix;
        int joueurDepasse = 0;
        while (1)
        {
            afficherSeparation(banque);
            afficherMain(&joueur, "Moi");
            afficherMain(&croupier, "Croupier");

            if (joueur.score > 21)
            {
                printf("Le joueur depasse 21! Le croupier gagne.\n");
                banque -= mise;
                jouerSonDefaite(); // Son de défaite
                joueurDepasse = 1;
                break;
            }

            printf("Voulez-vous Tirer (t) ou Rester (r)? ");
            scanf(" %c", &choix);

            if (choix == 't' || choix == 'T')
            {
                ajouterCarte(&joueur, deck[indexDeck++]);
            }
            else
            {
                break;
            }
        }

        // Jouer la main splitee si applicable
        if (splitMain.nbCartes > 0 && !joueurDepasse)
        {
            int splitDepasse = 0;
            while (1)
            {
                afficherSeparation(banque);
                afficherMain(&splitMain, "Main splitee");
                afficherMain(&croupier, "Croupier");

                if (splitMain.score > 21)
                {
                    printf("La main splitee depasse 21! Le croupier gagne.\n");
                    banque -= mise;
                    jouerSonDefaite();
                    splitDepasse = 1;
                    break;
                }

                printf("Voulez-vous Tirer (t) ou Rester (r) pour la main splitee? ");
                scanf(" %c", &choix);

                if (choix == 't' || choix == 'T')
                {
                    ajouterCarte(&splitMain, deck[indexDeck++]);
                }
                else
                {
                    break;
                }
            }

            if (!splitDepasse)
            {
                while (croupier.score < 17)
                {
                    ajouterCarte(&croupier, deck[indexDeck++]);
                }

                afficherSeparation(banque);
                afficherMain(&splitMain, "Main splitee");
                afficherMain(&croupier, "Croupier");

                if (croupier.score > 21)
                {
                    printf("Le croupier depasse 21! La main splitee gagne.\n");
                    banque += mise * 2;
                    jouerSonVictoire();
                }
                else if (splitMain.score > croupier.score)
                {
                    printf("La main splitee gagne!\n");
                    banque += mise * 2;
                    jouerSonVictoire();
                }
                else if (splitMain.score < croupier.score)
                {
                    printf("Le croupier gagne contre la main splitee.\n");
                    banque -= mise;
                    jouerSonDefaite();
                }
                else
                {
                    printf("Egalité avec la main splitee!\n");
                    banque += mise;
                }
            }
        }

        if (!joueurDepasse)
        {
            while (croupier.score < 17)
            {
                ajouterCarte(&croupier, deck[indexDeck++]);
            }

            afficherSeparation(banque);
            afficherMain(&joueur, "Joueur");
            afficherMain(&croupier, "Croupier");

            if (croupier.score > 21)
            {
                printf("Le croupier depasse 21! Le joueur gagne.\n");
                banque += mise;
                jouerSonVictoire();
            }
            else if (joueur.score > croupier.score)
            {
                printf("Le joueur gagne!\n");
                banque += mise;
                jouerSonVictoire();
            }
            else if (joueur.score < croupier.score)
            {
                printf("Le croupier gagne!\n");
                banque -= mise;
                jouerSonDefaite();
            }
            else
            {
                printf("Egalité!\n");
            }
        }

        if (banque <= 0)
        {
            printf("Vous avez perdu tout votre argent. Fin du jeu.\n");
            break;
        }
    }

    libererMain(&joueur);
    libererMain(&croupier);
    libererMain(&splitMain);
}
