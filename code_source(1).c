#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const  char PION_A = 'X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
const int NBLIG = 6;
const int NBCOL = 7;
const int COLONNE_DEBUT = NBCOL/2;

typedef char t_grille [NBLIG] [NBCOL];

void initGrille (t_grille *);
void afficher (t_grille, char, int);
float grillePleine (t_grille);
void jouer(char * Grille, char * caractère, int * entier);
float choisirColonne (char Grille, char caractère, int entier);
float trouverLigne (char Grille, int entier);
float estVainqueur (int Grille, int entier);
void finDePartie (char caractère);

int main(){
    char vainqueur;
    int ligne, colonne; 
    char g;
 
    initGrille(&g);
    vainqueur = INCONNU;
    printf(&g, &PION_A, &COLONNE_DEBUT);

    while ((vainqueur==INCONNU) && (grillePleine(g)==0))
    {
        jouer(&g, &PION_A, &ligne, &colonne);
        afficher (g, PION_A, COLONNE_DEBUT);
        if (estVainqueur (g, ligne, colonne))
        {
            vainqueur = PION_A;
        }
        else if (grillePleine(g)==0)
        {
            jouer(&g, &PION_B, &ligne, &colonne);
            afficher (g, PION_A, COLONNE_DEBUT);
            }
            if (estVainqueur (g, ligne, colonne))
            {
                vainqueur = PION_B;
            }
    }
    finDePartie (vainqueur);
    return EXIT_SUCCESS;
}

