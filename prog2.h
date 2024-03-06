#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#include<unistd.h>
#define login_size 20


typedef struct
{
    int j, m, a;

} DATE;

typedef struct
{
    int id;
    char nom[50];
    char prenom[50];
    DATE dn;
    char matricule[11];
}Etudiant;
typedef struct{
    int id;
    char nom[50];
    char prenom[50];
}Admin;
typedef struct
{
    char login[20];
    char password[20];
    int type;
    int idLogger;
    int etat;
}Login;
int saisirInt(int min, int max, char msg[],char msgEr[])
{
    int x;
    do
    {
        printf("%s : ",msg);
        scanf("%d", &x);
        if (x<min || x>max)
        {
           puts(msgEr);
        }
    } while (x<min || x>max);

    return x;
}
char* saisiPass(char msg[],char msgEr[])
{
     static char val[20];
    do {
        fflush(stdin);
        printf("%s",msg);
        char *password = getpass("Entrez votre mot de passe : ");
        strcpy(val, password);
        val[strcspn(val, "\n")] = '\0';
        int estVide = 1;
        for (int i = 0; i < strlen(val); i++) {
            if (!isspace(val[i])) {
                estVide = 0;
                break;
            }
        }
        if (estVide) {
            printf("%s",msgEr);
        } else {
            break;
        }
    } while (1);
    return val;
}
char* saisiChar(char msg[],char msgEr[])
{
     static char val[20];
    do {
        fflush(stdin);
        printf("%s",msg);
        fgets(val, sizeof(val), stdin);
        val[strcspn(val, "\n")] = '\0';
        int estVide = 1;
        for (int i = 0; i < strlen(val); i++) {
            if (!isspace(val[i])) {
                estVide = 0;
                break;
            }
        }
        if (estVide) {
            printf("%s",msgEr);
        } else {
            break;
        }
    } while (1);
    return val;
}
int login()
{
    FILE *file = fopen("login.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    Login user;
    char ligne[100];
    char mdp[100];
    char login[100];
    int session=0;
    strcpy(login, saisiChar("donnez le login : ", "\nle login est requis:"));
    strcpy(mdp,saisiPass("donnez le mdp : ","le mdp est requis\n"));
        while (fgets(ligne, sizeof(ligne),file))
        {
            sscanf(ligne, "%s %s %d %d", user.login, user.password,&user.type,&user.etat) ;
            if (strcmp(login,user.login) == 0 && strcmp(mdp,user.password) == 0)
            {
                if (!user.etat)
                    return -1;
                if (user.type==1)
                    return 2;
                else
                    return 1;
            }

        }
        return 0;

        fclose(file);
        

}
void menuEtudiant() {
    printf("\nMenu Apprenant:\n");
    printf("1………..MARQUER MA PRÉSENCE\n");
    printf("2………..NOMBRE DE MINUTES D’ABSENCE\n");
    printf("3………..MES MESSAGES (0)\n");
    printf("4………..DECONNEXION\n");
    printf("5………..QUITTER\n");
}

void menuAdmin() {
    printf("\nMenu Admin:\n");
    printf("1………..GESTION DES ÉTUDIANTS\n");
    printf("2………..GÉNÉRATION DE FICHIERS\n");
    printf("3………..MARQUER LES PRÉSENCES\n");
    printf("4………..ENVOYER UN MESSAGE\n");
    printf("5………..DECONNEXION\n");
    printf("6………..QUITTER\n");
}
void deconect()
{
    return;
}
void mPresence()
{
    
}

