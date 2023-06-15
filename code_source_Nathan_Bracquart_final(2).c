/**
 * @file Jeu_Puissance4_Code_Nathan_BRACQUART.c
 * @author Nathan BRACQUART
 * @brief 
 * @version final
 * @date 2022-11-20
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
const char PION_A = 'X';
const char PION_B= 'O';
const char VIDE= ' ';
const char INCONNU = ' ';

#define NBLIG 6
#define NBCOL 7
const int COLONNE_DEBUT = (NBCOL-1)/2;
typedef char t_grille [NBLIG] [NBCOL] ;
/**
 * \typedef t_tableau
 * \brief type tableau à 2 dimensions de NBLIG et NBCOL caractère
 */

void initGrille(t_grille g);
void afficher(t_grille g, char pion, int colonne);
bool grillepleine(t_grille g);
void jouer (t_grille g, char pion, int *ligne, int *colonne);
int choisirColonne(t_grille g, char pion, int colonne);
int trouverLigne(t_grille g, int colonne);
void finDePartie(char vainqueur);
bool estVainqueur(t_grille g, int col, int lig);

int main(){     
    char vainqueur;
    int ligne, colonne; 
    t_grille g;
 
    initGrille(g);
    vainqueur = INCONNU;
    afficher(g, PION_A, COLONNE_DEBUT); 
    while ((vainqueur==INCONNU) && !(grillepleine(g)))
    {
        jouer(g, PION_A, &ligne, &colonne);
        afficher (g, PION_B, COLONNE_DEBUT);
        if (estVainqueur (g, ligne, colonne))
        {
            vainqueur = PION_A;
        }
        else if (grillepleine(g)==0)
        {
            jouer(g, PION_B, &ligne, &colonne);
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
/**
 * \fn procédure initGrille pour initialiser la grille de caractère VIDE
 * \param  grille t_grille nommée dans la fonction en g
 */
void initGrille(t_grille g)
{
    int col, lgn;
    for (lgn=0; lgn<NBLIG; lgn++){
        for(col=0; col<NBCOL; col++){
            g[lgn][col] = VIDE;

        }
    }
}

/**
 * \fn procédure afficher pour afficher le tableau et le pion au dessus de la grille
 * \param g 
 * \param pion affiche le pion au dessus de la grille
 * \param colonne l'indice de la colonne ou afficher le pion
 */
void afficher(t_grille g, char pion, int colonne){
    int col, lgn;
    char tab[NBLIG];
    for (col = 0; col < NBCOL; col++)
    {
        tab[col]=VIDE;
    }
    tab[colonne]=pion;
    printf(" %c %c %c %c %c %c %c \n", tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6]);
    
    for(col=0; col<NBCOL; col++){
        for(lgn=0; lgn<NBLIG; lgn++){
            printf("[%c]", g[lgn][col]);
        }
        printf("\n");
    }
        printf("------------------\n");
        printf("[1][2][3][4][5][6]\n\n\n");
}

/**
 * \fn fonction booléenne grillepleine qui envoi si la grille est pleine ou non
 * 
 * \param g pour regarder chaque colonne et ligne de la grille
 * \return true si la grille est pleine
 * \return false si la grille n'est toujours pas pleine
 */
bool  grillepleine(t_grille g)
{
     /* Détermine si la grille de jeu est pleine.*/
    int col;
    int lgn;
    bool trouve;
	trouve = false;

    for (col = 0; col < NBCOL; ++col){
        for (lgn = 0; lgn < NBLIG; ++lgn){
            if (g[lgn][col] == VIDE){
                return trouve;
			}
			else{
                trouve=true;
				return trouve;
			}

		}
	}	
}

/**
 * \fn procédure jouer qui appel les fonction choisirColonne et trouverLigne et qui permet donc de jouer le pion
 * 
 * \param g 
 * \param pion pour utiliser le pion du joueur dans la fonction choisirColonne
 * \param ligne en sortie uniquement afin de la réutiliser dans la fonction estVainqueur
 * \param colonne en sortie uniquement afin de la réutiliser dans la fonction estVainqueur
 */
void jouer(t_grille g, char pion, int *ligne, int *colonne)
{
    int res;
    res=0;
    while (res!=1)
    {
        *colonne=0;
        *ligne=0;

        *colonne = choisirColonne(g, pion, COLONNE_DEBUT);
        *ligne = trouverLigne(g, *colonne);
        if (*ligne==-1)
        {
            printf("La colonne est pleine, recommencez");
        }
        else
        {
            res=1;
        }

        g[*ligne][*colonne]=pion;
    }
}
/**
 * \fn fonction entière choisirColonne qui permet à l'utilisateur de choisir quelle colonne il veut jouer son pion
 * 
 * \param g
 * \param caractere le pion du joueur soir A soit B
 * \param colonne permet de savoir quelle colonne l'utilisateur à choisi
 * \return int retourne l'indice de la colonne que l'utilisateur à choisi
 */
int choisirColonne (t_grille g, char pion, int colonne){
    char touche;
    touche = 'f';
    colonne=3;
    afficher(g, pion, colonne);

    while (touche != ' ')
    {
        printf("Tapez 'q' pour décaler votre pion vers la gauche, 'd' pour décaler votre pion vers la droite et espace pour valider\n");
        scanf("%c", &touche);  

        if (touche=='q')
        {
            colonne--;
            afficher(g, pion, colonne);
            if (colonne<0){
            colonne=0;
            afficher(g, pion, colonne);
        }
        }
        else if (touche=='d')
        {
            colonne++;
            if (colonne>=6){
            colonne=6;
            afficher(g, pion, colonne);
        }
        afficher(g, pion, colonne);
        }
    }
    return colonne;
}

/**
 * \fn fonction entière trouverLigne qui permet de jouer le pion au bon emplacement en partant toujours du bas de la grille
 * 
 * \param g
 * \param colonne afin de savoir quelle colonne l'utilisateur à choisi
 * \return int retourne l'indice de la ligne ou le pion doit être placé
 */
int trouverLigne (t_grille g, int colonne){
    //Prend en entrée la variable colonne et renvoie  s'il est
   //impossible de poser un jeton dans la colonne.   
    int ligne;
    ligne = NBLIG -1;
    while((g[ligne][colonne] != VIDE) && (ligne!=NBLIG))
    {
        ligne--;
    }
    if(g[ligne][colonne]!= VIDE)
    {
        ligne=-1;
        return ligne;
    }
    else
    {
        return ligne;
    }
}

/**
 * \fn fonction booléenne estVainqueur pour savoir si le pion fait un puissance 4, verticalement, horizontalement, et diagonalement
 * 
 * \param g
 * \param col l'indice de la colonne pour savoir si le pion à cette ligne fait un puissance 4
 * \param lig l'indice de la ligne pour savoir si le pion à cette ligne fait un puissance 4
 * \return true retourne vrai si le pion à colonne et à la ligne qui est rentrer fait un puissance 4
 * \return false retourne faux si le pion à colonne et à la ligne qui est rentrer ne fait pas un puissance 4
 */
bool estVainqueur (t_grille g, int j, int k){
bool trouve;
    trouve=false;
/*Verification s'il y a alignement*/
    for(j=0; j<NBLIG; j++){
        for(k=5; k>=0; k--){
/*Verification alignement vertical*/
        if(k>=3){
            if((g[j][k]==PION_A && g[j][k-1]==PION_A && g[j][k-2]==PION_A && g[j][k-3]==PION_A) || (g[j][k]==PION_B && g[j][k-1]==PION_B && g[j][k-2]==PION_B && g[j][k-3]==PION_B)){
                trouve=true;
                return trouve;
            }
        }
/*Verification alignement horizontal*/
        else if(j<=3){
            if((g[j][k]==PION_A && g[j+1][k]==PION_A && g[j+2][k]==PION_A && g[j+3][k]==PION_A) || (g[j][k]==PION_B && g[j+1][k]==PION_B && g[j+2][k]==PION_B && g[j+3][k]==PION_B)){
                trouve=true;
                return trouve;
            }
        }
/*Verification alignement diagonal*/
        else if((k<=2) && (j<=3)){
            if((g[j][k]==PION_A && g[j+1][k+1]==PION_A && g[j+2][k+2]==PION_A && g[j+3][k+3]==PION_A) || (g[j][k]==PION_B && g[j+1][k+1]==PION_B && g[j+2][k+2]==PION_B && g[j+3][k+3]==PION_B)){
                trouve=true;
                return trouve;
            }
        }
/*Verification alignement diagonal*/
        else if((k>=3) && (j<=3)){
            if((g[j][k]==PION_A && g[j+1][k-1]==PION_A && g[j+2][k-2]==PION_A && g[j+3][k-3]==PION_A) || (g[j][k]==PION_B && g[j+1][k-1]==PION_B && g[j+2][k-2]==PION_B && g[j+3][k-3]==PION_B)){
                trouve=true;
                return trouve;
            }
        }

        else{
            trouve=false;
            return trouve;
        }
        }
    }
}
/**
 * \fn procédure finDePartie permet d'afficher qui à gagner ou si il y a égalité du à la grille qui est pleine
 * 
 * \param vainqueur pour savoir quelle pion de joueur à gagner ou si le vainqueur est INCONNU alors cela veut dire qu'il y'a égalité
 */
void finDePartie (char vainqueur){
    if (vainqueur == PION_A)
    {
        printf("*********** Le gagnant est ‘X’ !**********\n");
        
    }
    else if (vainqueur == PION_B)
    {
        printf("*********** Le gagnant est ‘O’ !**********\n");
    }
    else if (vainqueur ==  INCONNU)
    {
        printf("********** Egalité, pas de gagnant!**********\n");
    }
    
}



