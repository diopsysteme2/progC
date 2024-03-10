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
        fflush(stdin);
        scanf("%d", &x);
        //scanf("%d", &x);
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
        fflush(stdin);
        val[strcspn(val, "\n")] = '\0';
        int estVide = 1;
        for (int i = 0; i < strlen(val); i++) {
            if (!isspace(val[i])) {
                estVide = 0;
                break;
            }
        }
        if (estVide) {
            puts(msgEr);
        } else {
            break;
        }
    } while (1);
    return val;
}
char* saisieMessage(char msg[],char msgEr[])
{
     static char val[200];
    do {
        fflush(stdin);
        getchar();
        printf("%s",msg);
        fgets(val, sizeof(val), stdin);
        fflush(stdin);
        val[strcspn(val, "\n")] = '\0';
        int estVide = 1;
        for (int i = 0; i < strlen(val); i++) {
            if (!isspace(val[i])) {
                estVide = 0;
                break;
            }
        }
        if (estVide) {
            puts(msgEr);
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

void menuEtudiant(int nbr) {
    printf("\nMenu Apprenant:\n");
    printf("1………..MARQUER MA PRÉSENCE\n");
    printf("2………..NOMBRE DE MINUTES D’ABSENCE\n");
    printf("3………..MES MESSAGES (%d)\n",nbr);
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

        char date[30],date1[30],ligneP[150],mat2[30],classe1[30];
        char heure[30],nom1[30],prenom1[30],heure1[30];
        int id1;
        strftime(date, sizeof(date), "%Y-%m-%d", &tm);
        strftime(heure, sizeof(heure), "%H:%M:%S", &tm);

        FILE *filePresence = fopen("presence.txt", "a");
        FILE *filePresencer = fopen("presence.txt", "r");
        if (filePresence == NULL) {
            printf("Erreur lors de l'ouverture du fichier de présence.");
            return 10;
        }
        while (fgets(ligneP,100,filePresencer)!=NULL)
        {
            // printf("look");
            sscanf(ligneP,"%d %s %s %s %s %s %s\n", &id1, nom1, prenom1, mat2, classe1,date1, heure1);
            if (strcmp(date,date1)==0 &&strcmp(mat2, matricule)==0)
            {
                fclose(filePresence);
                fclose(filePresencer);
                return -1;
            }
        }
        fprintf(filePresence, "%d %s %s %s %s %s %s\n", id, nom, prenom, mat, classe,date, heure);
        fclose(filePresence);
        fclose(filePresencer);
        FILE *fileDate = fopen("date.txt", "a");
        FILE *fileDate1 = fopen("date.txt", "ra");
        int adDate =1;
        while (fgets(ligneP,100,fileDate1)!=NULL)
        {
            printf("look");
            sscanf(ligneP,"%d %s %s %s %s %s %s\n", &id, nom, prenom, mat, classe,date1, heure);
            if (strcmp(date,date1)==0 )
            {
                adDate =0;
            }
        }
        if (adDate)
        {
            fprintf(fileDate, "%s\n",date);
        }
         fclose(fileDate1);
            fclose(fileDate);
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

        char date[30],date1[30],ligneP[150],mat2[30],classe1[30];
        char heure[30],nom1[30],prenom1[30],heure1[30];
        int id1;
        strftime(date, sizeof(date), "%Y-%m-%d", &tm);
        strftime(heure, sizeof(heure), "%H:%M:%S", &tm);

        FILE *filePresence = fopen("presence.txt", "a");
        FILE *filePresencer = fopen("presence.txt", "r");
        if (filePresence == NULL) {
            printf("Erreur lors de l'ouverture du fichier de présence.");
            return 10;
        }
        while (fgets(ligneP,100,filePresencer)!=NULL)
        {
            // printf("look");
            sscanf(ligneP,"%d %s %s %s %s %s %s\n", &id1, nom1, prenom1, mat2, classe1,date1, heure1);
            if (strcmp(date,date1)==0 &&strcmp(mat2, matricule)==0)
            {
                fclose(filePresence);
                fclose(filePresencer);
                return -1;
            }
        }

        fprintf(filePresence, "%d %s %s %s %s %s %s\n", id, nom, prenom, mat, classe,date, heure);
        fclose(filePresence);
        fclose(filePresencer);
        FILE *fileDate = fopen("date.txt", "a");
        FILE *fileDate1 = fopen("date.txt", "ra");
        int adDate =1;
        while (fgets(ligneP,100,fileDate1)!=NULL)
        {
           
            sscanf(ligneP,"%d %s %s %s %s %s %s\n", &id, nom, prenom, mat, classe,date1, heure);
            if (strcmp(date,date1)==0 )
            {
                adDate =0;
            }
        }
        if (adDate)
        {
            fprintf(fileDate, "%s\n",date);
        }
         fclose(fileDate1);
            fclose(fileDate);
        return 1;
    } else {
        printf("Matricule non trouvé dans le fichier des étudiants.");
        
        return 0;
    }
}
void genereFile(char dateSaisi[])
{
    char line[100];
    char date[30], nom[50], prenom[50], mat[20], classe[20], heure[20];
    int id;
    FILE *listeG = fopen(dateSaisi, "w");
    FILE *liste = fopen("presence.txt", "r");
    if (listeG == NULL) {
        printf("Erreur lors de l'ouverture du fichier de date.");
        return;
    }

    fprintf(listeG, "\nla liste de presence de la date du : %s\n", dateSaisi);
    fprintf(listeG, "\n+-------------------------------------------------------------------------------------------+\n");
    fprintf(listeG, "\n|   id     |      nom      |          prenom           | matricule | classe |     heure     |\n");
    fprintf(listeG, "\n+-------------------------------------------------------------------------------------------+\n");

    while (fgets(line, sizeof(line), liste)) {
        sscanf(line, "%d %s %s %s %s %s %s", &id, nom, prenom, mat, classe, date, heure);
        if (strcmp(dateSaisi, date) == 0) {
            fprintf(listeG, "\n|   %d   | %s    |        %s               |    %s   | %s |    %s   |\n", id, nom, prenom, mat, classe, heure);
            fprintf(listeG, "\n+-------------------------------------------------------------------------------------------+\n\n");
            usleep(90000);
        }
    }

    fclose(listeG);
    fclose(liste);
}
void genereFileA(char dateSaisi[])
{
    char line[100];
    char date[30], nom[50], prenom[50], mat[20], classe[20], heure[20];
    int id;
    FILE *listeG = fopen("presenceTotal.txt", "a");
    FILE *liste = fopen("presence.txt", "r");
    if (listeG == NULL) {
        printf("Erreur lors de l'ouverture du fichier de date.");
        return;
    }
    fprintf(listeG, "\nla liste de presence de la date du : %s\n", dateSaisi);
    fprintf(listeG, "\n+-------------------------------------------------------------------------------------------+\n");
    fprintf(listeG, "\n|   id     |      nom      |          prenom           | matricule | classe |     heure     |\n");
    fprintf(listeG, "\n+-------------------------------------------------------------------------------------------+\n");

    while (fgets(line, sizeof(line), liste)) {
        sscanf(line, "%d %s %s %s %s %s %s", &id, nom, prenom, mat, classe, date, heure);
        if (strcmp(dateSaisi, date) == 0) {
            fprintf(listeG, "\n|   %d   | %s    |        %s               |    %s   | %s |    %s   |\n", id, nom, prenom, mat, classe, heure);
            fprintf(listeG, "\n+-------------------------------------------------------------------------------------------+\n\n");
            usleep(90000);
        }
    }

    fclose(listeG);
    fclose(liste);
}
void genFileAll()
{
    char line[30],date2[30];
   FILE *file = fopen("date.txt", "r");
    while(fgets(line, 30, file))
    {
        sscanf(line, "%s", date2);
        genereFileA(date2);
        sleep(2);
    }
    fclose(file);
}

void videFile()
{
    FILE *file = fopen("presenceTotal.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de présence.");
        return;
    }
    fprintf(file,"\t\t\t\t\t\t\tVOICI LA LISTE DE PRESENCE DE TOUTE LES CLASSES\n\n\n");
    fclose(file);
}
void validDate(char date[]) {
    int year, month, day;
    
    do {
        fflush(stdin);
        strcpy(date, saisiChar("Entre une date valide format(annee-mois-jour) : ","Entrez klk chose au moins!!!"));
        if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
        {
            printf("format de date invalide!!!\n");
        }
    } while(sscanf(date, "%d-%d-%d", &year, &month, &day) != 3);
}
int isInFileDate(char date[])
{
    FILE *file = fopen("date.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de date.");
        return 10;
    }
    char line[100],dateInfile[10];
    while (fgets(line, 100, file))
    {
        sscanf(line, "%s", dateInfile);
        if (!strcmp(dateInfile,date))
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
return 0;

}
int valClass(char classe[])
{
    FILE *file = fopen("class.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de classe.");
        return 10;
    }
    char line[10],classF[10];
    while (fgets(line, 10, file))
    {
        sscanf(line, "%s", classF);
        if (!strcmp(classF,classe))
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
void prClass(char *class)
{
    printf("Voici la liste des apprenants du referenciel : %s\n",class);
    FILE *fileEtudiant = fopen("listeEtudiant.txt", "r");
    if (fileEtudiant == NULL) {
        printf("Erreur lors de l'ouverture du fichier de classe.");
        return;
    }
    char ligne[200], nom[50], prenom[50], matricule[50], classe[50];
    int id, exist = 0;

    while (fgets(ligne, sizeof(ligne), fileEtudiant)) {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, matricule, classe);
        if (strcmp(classe, class) == 0) {
            printf("%d %s %s %s %s\n", id, nom, prenom, matricule, classe);
        }
    }
    fclose(fileEtudiant);
}
int isInclasse(char mat[], char class[])
{
     FILE *fileEtudiant = fopen("listeEtudiant.txt", "r");
    if (fileEtudiant == NULL) {
        printf("Erreur lors de l'ouverture du fichier de classe.");
        return 10;
    }
    char ligne[200], nom[50], prenom[50], matricule[50], classe[50];
    int id, exist = 0;

    while (fgets(ligne, sizeof(ligne), fileEtudiant)) {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, matricule, classe);
        if (strcmp(classe, class) == 0 && strcmp(mat,matricule) == 0) {
            fclose(fileEtudiant);
            return 1;
        }
    }
    fclose(fileEtudiant);
    return 0;
}
void matMess(char mat[], char classe[], char destinataire[])
{
    int exist;
    do 
    {
        fflush(stdin);
        fflush(stdin);
            strcpy(mat, saisiChar("donnez son matricule : ", "le champs est requis!!!"));
            if (!isInclasse(mat, classe)) {
            printf("Matricule invalide !\n");
            continue;
            }
            if (strstr(destinataire, mat) != NULL) {
            printf("Vous avez déjà sélectionné ce matricule !\n");
            exist = 1;
            } else {
            exist = 0;
            strcat(destinataire, mat);
            strcat(destinataire, " ");
            }
            fflush(stdin);
            fflush(stdin);
    } while (exist);

    fflush(stdin);
    puts("l'eleve selection reussi");
    fflush(stdin);
    fflush(stdin);
    
}
int rep(char reponse[])
{
    getchar();
    fflush(stdin);
     do
    {
        strcpy(reponse,saisiChar("voulez vous envoyer à un autre etudiant : ","le champs est requis!!!"));
    } while (strncmp(reponse, "o", 1) != 0 && strncmp(reponse, "n", 1) != 0);
    if (!strncmp(reponse, "n", 1))
    return 0;
    return 1;
}
void send(char mat[],char message[])
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char date[30], heure[30];
        
        strftime(date, sizeof(date), "%Y-%m-%d", &tm);
        strftime(heure, sizeof(heure), "%H:%M:%S", &tm);
    FILE *fileMessage = fopen("message.txt", "a");
    if (fileMessage == NULL) {
        printf("Erreur lors de l'ouverture du fichier de message.");
        return;
    }
    fprintf(fileMessage,"'%s' '%s' '%s' '%s'\n",mat,message,heure,date);
    fclose(fileMessage);
}
void sendToAll(char message[])
{
    int id;
    char ligne[200], nom[50], prenom[50], matricule[50], classe[50];
    FILE *fileEtudiant = fopen("listeEtudiant.txt", "r");
    while (fgets(ligne,100,fileEtudiant))
    {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, matricule, classe);
        send(matricule,message);
    }
    fclose(fileEtudiant);
}
void sendToClass(char class[],char message[])
{
    int id;
    char ligne[200], nom[50], prenom[50], matricule[50], classe[50];
    FILE *fileEtudiant = fopen("listeEtudiant.txt", "r");
     while (fgets(ligne,100,fileEtudiant))
    {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, matricule, classe);
        if (strcmp(class,classe)==0)
        {
            send(matricule,message);
        }
        
        
    }
    fclose(fileEtudiant);
}

void readMess(char mat[])
{
      FILE *fichier;
    char ligne[100];
    
    fichier = fopen("message.txt", "r");
    while (fgets(ligne, 100, fichier) != NULL) {
        char matricule[10],heure[10],date[10];
        char message[90];
        
        sscanf(ligne, " '%9[^']' '%[^']' '%[^']' '%[^']'", matricule, message,heure,date);
         if (strcmp(matricule, mat)==0)
         {
            printf("Message : %s : heure %s : date %s:\n", message,heure,date);
         }
         
       
    }

    fclose(fichier);
}
void saisiSpecific(char tabMat[],char message[])
{
     char *token = strtok(tabMat, " ");
    while (token != NULL) {
        send(token,message);
        token = strtok(NULL, " ");
    }

}
int nbrmessage(char mat[])
{
    int nbr = 0;
    FILE *fileMessage = fopen("message.txt", "r");
    if (fileMessage == NULL) {
        printf("Erreur lors de l'ouverture du fichier de message.");
        return 10;
    }
 char ligne[200],matricule[50];
    // int id, exist = 0;

    while (fgets(ligne, sizeof(ligne), fileMessage)) {
        sscanf(ligne, "'%9[^']' ",  matricule);
        if (strcmp(matricule, mat) == 0) {
            nbr++;
        }
    }
    fclose(fileMessage);
    return nbr;
}