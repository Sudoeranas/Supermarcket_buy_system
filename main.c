////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

int lireProchaineCommande() // pour lire l'int contenu dans nextFact
{
	FILE *f;
	int N;
	f = fopen("nextFact", "r");
	fread(&N, sizeof(int), 1, f);

	fclose(f);
	// printf("\n--->lu N=%d",N);
	return N;
}
// test
void convertirNenChaine4(int N, char *N4) // convertit l'int N en une chaine de 4 caracteres
{										  // si N=1234 alors N4 sera égal à "1234"
	int m, c, d, u;
	char cm, cc, cd, cu;
	m = N / 1000;
	cm = 48 + m;
	N %= 1000;
	c = N / 100;
	cc = 48 + c;
	N %= 100;
	d = N / 10;
	cd = 48 + d;
	u = N % 10;
	cu = 48 + u;
	N4[0] = cm;
	N4[1] = cc;
	N4[2] = cd;
	N4[3] = cu;
	N4[4] = '\0';
}

void lireLesCommandes() // cette fonction ouvre tous les fichiers commandeXXXX.txt avec XXXX démarrant à N
{
	FILE *ficCommande = NULL;
	int FINI = 0;
	int N = lireProchaineCommande(); // numero de la premiere commande qui sera lue et traitee
	char NNNN[5];
	char nomCommande[29];

	do // ce do while prend fin dès que fichier commandeXXXX.txt est absent
	{
		strcpy(nomCommande, "./commandes/commande");
		convertirNenChaine4(N, NNNN);
		// printf("\n==>%s<==",NNNN);
		ficCommande = NULL;
		strcat(nomCommande, NNNN);
		strcat(nomCommande, ".txt");

		// printf("\n traitement de  %s",nomCommande);

		ficCommande = fopen(nomCommande, "rt");
		if (ficCommande != NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present", nomCommande);
			lireCommande(nomCommande); // à vous de coder cette fonction lors de ce TP10
			fclose(ficCommande);
		}
		else
		{
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f = fopen("nextFact", "w"); // on va ecrire la valeur de N dans enxtFact
			// pour
			fwrite(&N, 1, sizeof(int), f);
			fclose(f);
			FINI = 1;
		}

		N++;
	} while (FINI == 0);
}

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
            printf("%s", donnee);
            fprintf(facture,"%s",tab_commandes[cpt]);
            cpt++;
        } while (fgets(donnee, 400, commande));
    }
}

int main()
{
	// creation d'un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP

	FILE *f;
	int N = 1;
	f = fopen("nextFact", "w");
	fwrite(&N, 1, sizeof(int), f);
	fclose(f);

	// PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); // lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)

	// PARTIE 2 du TP : avec Gestion de stock
	// copiez coller votre travail précédent puis modifiez le
	// lireLesCommandes2();

	return 0;
}