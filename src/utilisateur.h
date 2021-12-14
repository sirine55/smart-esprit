#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
typedef struct date
{
    int j;
    int m;
    int a;
}date;

typedef struct utilisateur
{
    int id;
    int role;
    char prenom[50];
    char nom[50];
    char password[50];
    int sexe;
    date d ;
    int nv;

}utilisateur;

void ajouter_utilisateur(utilisateur u, char *fname);
void supprimer_utilisateur(utilisateur u, char *fname);
void modifier_utilisateur(utilisateur u, char *fname);
void afficher_utilisateur(GtkWidget *liste, char *fname);
utilisateur chercher_utilisateur(int id, char *fname);
char* nombre_etudiant(char *fname);

