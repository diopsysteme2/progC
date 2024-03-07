#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif


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
    char matricule[20];
    int etat;
}Login;

char getch() {
#ifdef _WIN32
    return _getch();
#else
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
#endif
}
void getHiddenInput(char *password, int maxLength) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\n' || ch == '\r') {
            password[i] = '\0';
            break;
        } else if (ch == 127 && i > 0) {  
            printf("\b \b");
            i--;
        } else if (isprint(ch) && i < maxLength - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
}
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
char* saisiPass(char msg[],char msgEr[]) {
    static char val[20];
    do {
        printf("%s", msg);
        fflush(stdout);
        char password[20];
        getHiddenInput(password, sizeof(password));
        printf("\n");
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
            printf("%s", msgEr);
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
int login(char mat[], char password[]) {
    FILE *file = fopen("login.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    Login user;
    char ligne[100];
    char mdp[100];
    char login[100];
    int session = 0;
    strcpy(login, saisiChar("donnez le login : ", "\nle login est requis:"));
    strcpy(mdp, saisiPass("donnez le mdp : ", "le mdp est requis\n"));
    while (fgets(ligne, sizeof(ligne), file)) {
        sscanf(ligne, "%s %s %d %d %s", user.login, password, &user.type, &user.etat, mat);
        if (strcmp(login, user.login) == 0 && strcmp(mdp, password) == 0) {
            fclose(file);
            if (!user.etat)
                return -1;
            if (user.type == 1)
                return 2;
            else
                return 1;
        }
    }
    fclose(file);
    return 0;
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


int mPresence(char mat[])
{
    FILE *fileEtudiant = fopen("listeEtudiant.txt", "r");
    if (fileEtudiant == NULL) {
        printf("Erreur lors de l'ouverture du fichier listeEtudiant.txt.");
    }

    char ligne[200], nom[50], prenom[50], matricule[50], classe[50];
    int id, exist = 0;

    while (fgets(ligne, sizeof(ligne), fileEtudiant)) {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, matricule, classe);
        if (strcmp(mat, matricule) == 0) {
            break;
        }
    }

    fclose(fileEtudiant);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char filename[30],ligneP[150],mat2[30];
        char heure[30],nom1[30],prenom1[30];
        int id1;
        strftime(filename, sizeof(filename), "%Y-%m-%d.txt", &tm);
        strftime(heure, sizeof(heure), "%H:%M:%S", &tm);

        FILE *filePresence = fopen(filename, "a");
        FILE *filePresencer = fopen(filename, "ra");
        // if (filePresence == NULL) {
        //     printf("Erreur lors de l'ouverture du fichier de présence.");
        //     return 10;
        // }
        while (fgets(ligneP,100,filePresencer)!=NULL)
        {
            //printf("look");
            sscanf(ligneP,"%d %s %s %s",&id1, nom1, prenom1, mat2);
            if (strcmp(mat,mat2)==0)
            {
                fclose(filePresencer);
                fclose(filePresence);
                return -1;
            }
        }
        

        fprintf(filePresence, "%d %s %s %s %s %s\n", id, nom, prenom, mat, classe, heure);
        fclose(filePresence);
        fclose(filePresencer);
        return 1;
    
}
int mPresenceA(char mat[])
{
    
    // char mat[20];
    // strcpy(mat,saisiChar("entrez le matricule:","le matricule est requis:"));
    FILE *fileEtudiant = fopen("listeEtudiant.txt", "r");
    if (fileEtudiant == NULL) {
        printf("Erreur lors de l'ouverture du fichier listeEtudiant.txt.");
        
    }

    char ligne[200], nom[50], prenom[50], matricule[50], classe[50];
    int id, exist = 0;

    while (fgets(ligne, sizeof(ligne), fileEtudiant)) {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, matricule, classe);
        if (strcmp(mat, matricule) == 0) {
            exist = 1;
            break;
        }
    }

    fclose(fileEtudiant);

    if (exist) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char filename[30],ligneP[150],mat2[30];
        char heure[30],nom1[30],prenom1[30];
        int id1;
        strftime(filename, sizeof(filename), "%Y-%m-%d.txt", &tm);
        strftime(heure, sizeof(heure), "%H:%M:%S", &tm);

        FILE *filePresence = fopen(filename, "a");
        FILE *filePresencer = fopen(filename, "ra");
        if (filePresence == NULL) {
            printf("Erreur lors de l'ouverture du fichier de présence.");
            return 10;
        }
        while (fgets(ligneP,100,filePresencer)!=NULL)
        {
            printf("look");
            sscanf(ligneP,"%d %s %s %s",&id1, nom1, prenom1, mat2);
            if (strcmp(mat,mat2)==0)
            {
                return -1;
            }
        }
        

        fprintf(filePresence, "%d %s %s %s %s %s\n", id, nom, prenom, mat, classe, heure);
        fclose(filePresence);
        return 1;
    } else {
        printf("Matricule non trouvé dans le fichier des étudiants.");
        return 0;
    }
}


