#define TAILLE 50

#define  NB_MAX_PRODUITS 1000


typedef struct 
{
unsigned int reference;
char libelle[TAILLE];
float prixU;
} T_Produit;

typedef T_Produit T_TableauDeProduits[ NB_MAX_PRODUITS];

int lireProchaineCommande();
void convertirNenChaine4(int N, char *N4);
void lireLesCommandes();
void lireCommande(char *nomcommande, char NNNN[5]);
