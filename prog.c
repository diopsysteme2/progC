#include "prog2.h"


int main()
{
    
    // // printf("Entrez le login : ");
    // // scanf("%s", user.login);
    // // printf("Entrez le mot de passe : ");
    // // scanf("%s", user.password);
    // // printf("Entrez le type : ");
    // // scanf("%d", &user.type   );
    // // printf("Entrez l'identifiant du logger : ");
    // // scanf("%d", &user.idLogger);
    // // printf("Entrez l'état : ");
    // // scanf("%d", &user.etat);

    // // fprintf(file, "%s %s %d %d %d\n", user.login, user.password, user.type, user.idLogger, user.etat);

    // // fclose(file);
    // fgets(ligne, sizeof(ligne), file);
    // sscanf(ligne, "%s %s %d", user.login, user.password,&user.type);
    // fclose(file);

    // printf("Login : %s\n", user.login);
    // printf("Mot de passe : %s\n", user.password) ;
    // printf("User TYPE : %d\n", user.type);
    // scanf("%s", login);
    // scanf("%s", mdp);
    // if (strcmp(login,user.login) == 0 && strcmp(mdp,user.password) == 0)
    // {
    //     printf("Password matches") ;
    // }else
    // {
    //     printf("Password doesn't match") ;
    // }
    
    
    // return 0;
    // char champ1[20], champ2[20];
    // sscanf(ligne, "%s %s", champ1, champ2) ;
        // Afficher les champs récupérés
// int tentative=5;
int  session,quit=0;

    while (quit==0)
    {
       
        session =login();
        if (session==1)
        {
            system("clear");
            printf("Bienvenue dans la page Etudiant\n");
            menuEtudiant();
           int choix= saisirInt(1,5,"faites votre choix","!! Faties un choix correct !!\n");
            if (choix==4)
            {system("clear");
                printf("vous vous etes deconnecte on espere vous revoir bientot\n");
                deconect();
            }else if (choix==5)
            {
                system("clear");
                printf("Bye On espère vous revoir bientot\n");
                quit=1;
            }
            
            
        }else if (session==2)
        {
            system("clear");
            printf("Bienvenue dans la page Admin\n");
            menuAdmin();
            saisirInt(1,6,"faites votre choix","!! Faties un choix correct !!");
            
        }else
        {
            //tentative--;
            if (session==0)
            {
                system("clear");
                printf("login ou mdp incorrect\n");
            }else
            {
                printf("!!!!Votre compte est bloqué!!!!\n" );
            }
            // if (tentative==0)
            // {
            //     printf("vous avez atteint le nombre de tentative autorisé!!!\n");
            //     break;
            // }
            //printf("!!!Tentatives restantes = %d!!! \n",tentative);
            
        }
    }
    
        
        
        
         

        
        
        // printf("Champ 1 : %s\n", champ1);
        // printf("Champ 2 : %s\n", champ2);
   
return 0;
}