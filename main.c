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
	// printf("\n--->lu N=%d", N);
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
		printf("\n==>%s<==", NNNN);
		ficCommande = NULL;
		strcat(nomCommande, NNNN);
		strcat(nomCommande, ".txt");

		printf("\n traitement de  %s", nomCommande);

		ficCommande = fopen(nomCommande, "rt");
		if (ficCommande != NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present", nomCommande);
			lireCommande(nomCommande, NNNN); // à vous de coder cette fonction lors de ce TP10
			fclose(ficCommande);
		}
		else
		{
			printf("\n toutes les commandes presentes ont ete traitees. \n");
			FILE *f = fopen("nextFact", "w"); // on va ecrire la valeur de N dans enxtFact
			// pour
			fwrite(&N, 1, sizeof(int), f);
			fclose(f);
			FINI = 1;
		}

		N++;
	} while (FINI == 0);
}

T_Produit recherchereference(int ref)
{
	FILE *produits;
	T_Produit result;
	produits = fopen("produits.txt", "r");
	do
	{
		fscanf(produits, "%d %s %f", &result.reference, result.libelle, &result.prixU);
		if (ref == result.reference)
		{
			return result;
		}
	} while (!feof(produits));
}

void lireCommande(char nomcommande[20], char NNNN[5])
{
	FILE *commande;
	char fichier[TAILLE];
	FILE *facture;
	FILE *produits;
	FILE *stock;
	T_Produit bababoi;
	int N = lireProchaineCommande();
	char NOM[TAILLE] = "";
	char libelle[TAILLE] = "";
	int i = 0, ref = 0, qt = 0;
	float prix, somme = 0, resultat = 0;
	strcpy(fichier, "./factures/facture");
	strcat(fichier, NNNN);
	strcat(fichier, ".txt");
	//printf("\t\nvoila notre nom de fac %s \t\n", fichier);//DEBUG
	facture = fopen(fichier, "w");
	commande = fopen(nomcommande, "r");
	stock=fopen("stocks.txt", "w");
	if (commande != NULL)
	{
		printf("---------------%s---------------\n", nomcommande);
		fscanf(commande, "%s", NOM);
		i++;
		printf("%s\n", NOM);

		printf("Client : %s \n", NOM);
		fprintf(facture, "Client : %s \n", NOM);

		do
		{
			fscanf(commande, "%d %d", &ref, &qt);
			bababoi = recherchereference(ref);
			resultat = qt * bababoi.prixU;
			printf("%d %s  :  %f \n", qt, bababoi.libelle, resultat);
			fprintf(facture, "%d %s  (PU=%.2f€)  :: %.2f€\n", qt, bababoi.libelle, bababoi.prixU, resultat);

			somme += resultat;
		} while (!feof(commande));
		printf("TOTAL de Votre commande : %f \n\n", somme);
		fprintf(facture,"\n\t\tTOTAL: %f", somme);
	}
	else
	{
		printf("Erreur ouverture fichier \n");
	}
	fclose(commande);
	fclose(facture);
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