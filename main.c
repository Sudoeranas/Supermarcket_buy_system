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

void stockage(int refe,int qte)//nous fonctionnons avec un sytème de fichier_bis afin de ne pas avoir de problèmes lors de la modufication de valeur (ex: un 90 qui devient 900 car avant 90 on était dans un nombre à 3 chiffres), ainsi nous faisons un "copié" "collé" et modifions la valeur quand il s'agit du produit concerné
{
	int ref2, qte2, ref3;
	FILE *commande;
	FILE *stock;
	FILE *stock_bis;
	stock = fopen("stock.txt", "r+");
	stock_bis = fopen("stock_bis.txt", "w");
	if (stock != NULL)
	{
		do
		{
			fscanf(stock, "%d %d", &ref2, &qte2);
			if (ref3 == ref2) break;//utilisé pour régler le problème d'une boucle en trop
			ref3 = ref2;//utilisé pour régler le problème d'une boucle en trop
			if (ref2 == refe) {
				qte2 = qte2 - qte;
				if (qte2 < 0){ //si rupture de stock
					alerte(ref2, qte2);//pour alerter d'une rupture de stock dans alerte.txt
				}				
					fprintf(stock_bis,"%d %d \n", ref2, qte2);	
			}
			else{
				fprintf(stock_bis,"%d %d \n", ref2, qte2);
			}
		} while (!feof(stock));
	fclose (stock_bis);
	fclose (stock);
	system("mv stock_bis.txt stock.txt"); //pour écraser stock_bis.txt dans stock.txt, avec le nouveau nom stock.txt
	}
}

void alerte(int ref, int qte){
		FILE *alerte;
		FILE *alerte_bis;
		int ref2, qte2, ref3, flag=0;

	alerte = fopen("alerte.txt", "r"); //on ouvre en "r" car nous allons tester s'il existe déjà, s'il n'existe pas alors il va valoir NULL

	if (alerte == NULL) {//si alerte.txt n'existe pas
		alerte = fopen("alerte.txt", "w");
		fprintf(alerte, "%d %d \n", ref, -qte);
		fclose (alerte);
	}
	else{
		fclose(alerte);
		alerte = fopen("alerte.txt", "r+");
		alerte_bis = fopen("alerte_bis.txt","w");
		flag=0;//pour savoir si nous avons trouvé une correspondance
		do //parcour de alerte.txt
		{
			fscanf(alerte, "%d %d", &ref2, &qte2);
				if (ref2 == ref3) break; //utilisé pour régler le problème d'une boucle en trop
				ref3 = ref2 ;//utilisé pour régler le problème d'une boucle en trop
				if (ref2 == ref){//le cas où nous avons la référence correspondante
				fprintf(alerte_bis, "%d %d \n", ref, -qte);
				flag=1;
				}
				else{//le cas où nous avons pas la référence correspondante
					fprintf(alerte_bis, "%d %d \n", ref2, qte2);
				}
		} while (!feof(alerte));
		if (flag == 0) fprintf(alerte_bis, "%d %d", ref, -qte); //si aucune correspondance nous ajoutons alors la nouvelle alerte d'où utilité du flag
		fclose (alerte_bis);
		fclose (alerte);
		system("mv alerte_bis.txt alerte.txt"); //pour écraser alerte_bis.txt dans alerte.txt, avec le nouveau nom alerte.txt
	}
}


void lireCommande(char nomcommande[20], char NNNN[5])
{
	FILE *commande;
	char fichier[TAILLE];
	FILE *facture;
	FILE *produits;
	T_Produit bababoi;
	int N = lireProchaineCommande();
	char NOM[TAILLE] = "";
	char libelle[TAILLE] = "";
	int i = 0, ref = 0, qt = 0;
	float prix, somme = 0, resultat = 0;
	strcpy(fichier, "./factures/facture");
	strcat(fichier, NNNN);
	strcat(fichier, ".txt");
	// printf("\t\nvoila notre nom de fac %s \t\n", fichier);//DEBUG
	facture = fopen(fichier, "w");
	commande = fopen(nomcommande, "r");
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
			// fprintf(facture, "%d %s  :  %f \n", qt, bababoi.libelle, resultat);
			fprintf(facture, "%d %s  (PU=%.2f€)  :: %.2f€\n", qt, bababoi.libelle, bababoi.prixU, resultat);
			stockage (ref, qt);
			somme += resultat;
		} while (!feof(commande));
		printf("TOTAL de Votre commande : %f \n\n", somme);
		fprintf(facture, "\n\t\tTOTAL: %f", somme);
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