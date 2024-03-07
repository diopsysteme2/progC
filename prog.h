#include <stdio.h>
#include<string.h>

int idEtu = 0;
int idMat = 0;
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
} ETUDIANT;

typedef struct
{
    int id;
    char libelle[50];
    int coef;

}MATIERE;

typedef struct
{
    char libelle[50];
    MATIERE matieres[10];
    ETUDIANT etudiants[100];
    int nbrEtudiant;
    int nbrMatiere;
    enum niveau
    {
        L1 = 1,
        L2,
        L3,
        M1,
        M2,
        M3
    };

} CLASSE;

typedef struct
{
    ETUDIANT etudiant;
    MATIERE matiere;
    float note;
    enum type
    {
        DEVOIR,
        EXAMEN
    };

} EVALUATION;
// prototype
void afficherDate(DATE);
DATE saisieDate(void);
int saisirInt(int, int, char[]);
ETUDIANT saisirEtudiant();

int main()
{
    enum jour{LUNDI = 1,MARDI, MERCREDI, JEUDI,VENDREDI,SAMEDI,DIMANCHE};
    enum jour j;
    j = LUNDI;
    //afficherDate(saisieDate());
    saisirEtudiant();

    return 0;
}
// void affficher()
DATE saisieDate(void)
{
    DATE d;
    puts("Entrez une date [j,m,a]");
   // scanf("%d%d%d", &d.j, &d.m, &d.a);
   d.j = saisirInt(1, 31, "entrez le jour");
   d.m = saisirInt(1, 12, "entrez le mois");
   d.a = saisirInt(1, 2024, "entrez l'année");
    return d;
}
void afficherDate(DATE a)
{
    printf("la date est %d-%d-%d", a.j, a.m, a.a);
}
int saisirInt(int min, int max, char msg[])
{
    int x;
    do
    {
        puts(msg);
        scanf("%d", &x);
    } while (x<min || x>max);

    return x;
}
ETUDIANT saisirEtudiant(){
    ETUDIANT e;
    e.id = ++idEtu;
    puts("Donnez le nom :");
    fgets(e.nom, sizeof(e.nom), stdin);
    puts("Donnez le prénom :");
    fgets(e.prenom, sizeof(e.prenom), stdin);
    e.dn = saisieDate();
    stpcpy(e.matricule,makmMat(e));
    return e;

}
void afficherEtudiant(ETUDIANT e)
{

    printf("%s\t",e.matricule);
    printf("%s\t",e.nom);
    printf("%s\t",e.prenom);
    printf("%d-",e.dn.j);
    printf("%d-",e.dn.m);
    printf("%d",e.dn.a);
    printf("\n");
}
char* makmMat(ETUDIANT e)
{
    strcpy(e.matricule,"MAT-"+e.nom[0]+e.prenom[0]+e.id);
    return e.matricule;
}
MATIERE saisiMatier()
{
    MATIERE m;

    m.id = ++idMat;
    puts("Donnez le libelle :");
    fgets(m.libelle, sizeof(m.libelle), stdin);
    puts("Donnez le prénom :");
    m.coef=saisirInt(1,4,"le coef doit etre compris entre 1 et 4!!\n");
    return m;
}
void affficherMatier(MATIERE m)
{
    printf("\n  id = %d");
    printf("le libelle est %s\n", m.libelle);
    printf("le coef est %d\n", m.coef);
}
int saisiTabM(MATIERE m[])
{
    int n;
    do {
        printf("Donnez le nombre de etudiants : ");
        scanf("%d", &n);
    } while (n < 0);
    for (int i = 0; i < n; i++)
    {
        m[i] = saisiMatier();
    }
    return  n;
}
void afficherMatier(MATIERE m[],int n)
{
    for (int i = 0; i < n; i++)
    {
        affficherMatier(m[i]);
    }
    
    
}
int saisitabE(ETUDIANT e[])
{
    int n;
    do {
        printf("Donnez le nombre de etudiants : ");
        scanf("%d", &n);
    } while (n < 0);
    for (int i = 0; i < n; i++)
    {
        e[i] = saisirEtudiant();
    }
    return n;
}
EVALUATION saisiEval()
{
    EVALUATION e;
    e.etudiant = saisirEtudiant();
    e.matiere = saisiMatier();
    e.note = saisirInt(0,20,"la note doit etre compris entre 0 et 100!!\n");
    return e;
}
void affficherEval(EVALUATION e)
{
    afficherEtudiant(e.etudiant);
    affficherMatier(e.matiere);
    printf("la note est %d\n", e.note);
    printf("\n");
}
CLASSE saisiClasse(ETUDIANT e[],)
{
    CLASSE c;
    c.nbrEtudiant = saisitabE(c.etudiants);
    c.nbrMatiere = saisiTabM(c.matieres);
    c.libelle=
    return c;
}
