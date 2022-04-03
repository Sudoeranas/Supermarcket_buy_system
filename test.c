#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

void lireCommande(char nomcommande[20])
{
    FILE *commande;
    FILE *facture;
    FILE *produits;
    int x, y, cpt = 0;
    char NNNN[20], nomfic[25], nomfac[25], nomclient[25], donnee[400], tab_commandes[50][50];
    int j = strlen(nomcommande);
    for (int i = 0; i < j; i++)
    {
        if ((nomcommande[i] >= '0') && (nomcommande[i] <= '9'))
            NNNN[i] = nomcommande[i];
    }

    strcpy(nomfic, "commandes/");
    strcpy(nomfac, "factures/facture");
    // printf("le fichier nomfic est : %s", nomfic);
    strcat(nomfic, nomcommande);
    strcat(nomfac, NNNN);
    strcat(nomfac, ".txt");
    // printf("la commande qui va être traitée est : %s \n", nomfic);
    commande = fopen(nomfic, "r");
    facture = fopen(nomfac, "w+");
    produits = fopen("produits.txt", "r");
    if (commande != NULL)
    {
        do
        {
            strcpy(tab_commandes[cpt], donnee);
            //printf("%s", donnee);
            fprintf(facture,"%s",tab_commandes[cpt]);
            cpt++;
        } while (fgets(donnee, 400, commande));
    }
}
int main()
{
    char *commande;
    commande = "commande0002.txt";
    lireCommande(commande);
}