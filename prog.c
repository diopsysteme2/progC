#include "prog2.h"
int mai()
{
   sendToClass("devweb","demain pas cours");
   
}

int main()
{
    

int  session=-2,quit=0;

    while (quit==0)
    {
        char password[20],matricule[20];
        fflush(stdin);
        fflush(stdin);
            session =login(matricule,password);
       int nbr=0;
       nbr=nbrmessage(matricule);
        
        if (session==1)
        {
         printf("Bienvenue dans la page Etudiant\n");
            while (1)
            {
                        
               
               
               menuEtudiant(nbr);
                int choix= saisirInt(1,5,"faites votre choix","!! Faties un choix correct !!\n");
                if (choix==1)
                {       system("clear");
                        int etat =mPresence(matricule);
                        if (etat==1)
                        {
                            printf("Marquage reussi\n");
                        }else{
                            printf("Vous etes deja marqué present\n");
                        
                             }
                
                }else if (choix==4)
                {
                        system("clear");
                        printf("vous vous etes deconnecte on espere vous revoir bientot\n");
                       break;
                }else if (choix==5)
                {
                        system("clear");
                        printf("Bye On espère vous revoir bientot\n");

                        quit=1;
                        break;
                }else if (choix==3)
                {
                  system("clear");
                  puts("vos messages !!!");
                  readMess(matricule);
                  printf("!!!appuyer sur une touche pour revenir au menu!!\n");
                  getchar();
                  getchar();
                  system("clear");
                  nbr=0;
                }
            }
            
        }else if (session==2)
        {
         system("clear");
         printf("Bienvenue dans la page Admin\n");
            while (1)
            {
               // puts(password);
               // puts(matricule);
               menuAdmin();
               int choix=saisirInt(1,6,"faites votre choix","!! Faties un choix correct !!");
               fflush(stdin);
               if (choix==3)
               {
                       system("clear");
                        char mat[30];
                        while (1)
                        {
                           
                           fflush(stdin);

                            strcpy(mat,saisiChar("donnez le matricule (q pour quitter) : ","!!le matricule est requis!!"));
                            if (strcmp(mat,"q")==0)
                            {
                                char passv[20];
                                strcpy(passv,saisiPass("confirmer votre identité d'admin","password required!!!"));
                                if (strcmp(passv,password)!=0)
                                {
                                    printf("mot de passe incorrect!!!\n" );
                                    continue;
                                }else
                                {
                                    break;
                                }
                            }
                            fflush(stdin);
                            int presence= mPresenceA(mat);
                            if (presence==-1)
                            {
                                printf("l'etudiant est deja present !!\n");
                            }else if (presence==1)
                            {
                                printf("Marquage presence reussi!!\n");
                            }else if(presence==0)
                            {
                                printf("student not found!!\n");
                            }
                        }
               }else if (choix==2)
               {
                   while (1)
                   {
                        system("clear");
                        int chox=saisirInt(1,3,"GENERER PAR DATE GENERER TOUS\n1 ----> Par date\n2 ----> genere TOUS\n3 ---> retour\nfaites votre choix : ","choix invalide!!\n") ;
                        if (chox==3)
                           break;
                        if (chox==1)
                        {
                           system("clear");
                              fflush(stdin);
                              char datev[10];
                              validDate(datev);
                              int valDate=isInFileDate(datev);
                              printf("'%d' '%s'\n",valDate,datev);
                              if (valDate)
                              {
                                 genereFile(datev);
                                 printf("le fichier de presence de la date : '%s' a bien été créé\n",datev);
                              }
                              else
                              printf("aucune date correspondante à : '%s' in our files\n",datev);
                        }else
                        {
                           system("clear");
                            videFile();
                            genFileAll();
                            printf("Le fichier contenant toutes les presences a bien eté generer\n");

                        }
                   }
                }else if (choix ==4)
                {
                  system("clear");
                  char message[200];
                  fflush(stdin);
                  fflush(stdin);
                  strcpy(message,saisieMessage("saisissez le message : ","!!!comment pouvez vous envoyer un message sans contenu\nbindal dara wayy ahh!!!")) ;
                  int chox=saisirInt(1,4,"Envoyez le message  \n1 --- à tous les etudiant\n2 --- à tous les etudiant d'une classe\n3 --- à un  des etudiants specifique(s) \n4 --- retour\nvotre choix : ","choix invalide");
                  if (chox ==1)
                  {
                     fflush(stdin);
                     sendToAll(message);
                     puts("message envoyé à toute la promo");
                  }else if(chox ==2)
                  {
                     fflush(stdin);
                     chox=saisirInt(1,4,"1 --- devWeb\n2 --- devData\n3 --- refDig\n4 --- retour\nvotre choix : ","choix invalide");
                     if (chox ==1)
                     {
                        fflush(stdin);
                        sendToClass("devweb",message);
                        printf("message envoyé aux apprenants en dev web\n"); 
                     }
                     else if(chox ==2)
                     {
                        sendToClass("devdata",message);
                        printf("message envoyé aux apprenants en dev data\n");
                     }else if(chox ==3)
                     {
                        sendToClass("refdig",message);
                        printf("message envoyé aux apprenants en refDig\n");
                     }else
                     {
                        printf("retour\n");
                     }

                  }else if (chox==3)
                  {
                     fflush(stdin);
                     char destinataire[100];
                     while (1)
                     {
                        fflush(stdin);
                     fflush(stdin);
                        chox=saisirInt(1,4,"l'eleve est dans  kel ref??\n1 --- devWeb\n2 --- devData\n3 --- refDig\n4 --- retour\nvotre choix : ","choix invalide");
                        if (chox==1)
                        {
                           char mat[10];
                           char reponse[10];
                           char *classe="devweb";
                           fflush(stdin);
                           prClass(classe);
                           fflush(stdin);
                           matMess(mat,classe,destinataire);
                           fflush(stdin);
                          if (!rep(reponse))
                          {
                           saisiSpecific(destinataire,message);
                           puts("message envoyé!!");
                           break;
                          }
                        }else if (chox==2)
                        {
                           char reponse[10];
                           char *classe="devdata";
                           char mat[10];
                           prClass(classe);
                           fflush(stdin);
                           fflush(stdin);
                           matMess(mat,classe,destinataire);
                           fflush(stdin);
                          if (!rep(reponse))
                          {
                           saisiSpecific(destinataire,message);

                           puts("message envoyé!!");
                           break;
                          }
                        }else if (chox==3)
                        {
                           char reponse[10];
                           char classe[20];
                           strcpy(classe,"refdig");
                           prClass(classe);
                           char mat[10];
                           prClass(classe);
                           fflush(stdin);
                           fflush(stdin);
                           matMess(mat,classe,destinataire);
                           fflush(stdin);
                          if (!rep(reponse))
                          {
                           saisiSpecific(destinataire,message);

                           puts("message envoyé!!");
                           break;
                          }
                        }else
                        {
                           printf("retour\n");
                        }
                     }
                  }
                }
                else if(choix==5)
                {
                   system("clear");
                   printf("vous vous etes deconnecte on espere vous revoir bientot\n");
                   break;
                }
            }
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

return 0;
}
//     // // printf("Entrez le login : ");
//     // // scanf("%s", user.login);
//     // // printf("Entrez le mot de passe : ");
//     // // scanf("%s", user.password);
//     // // printf("Entrez le type : ");
//     // // scanf("%d", &user.type   );
//     // // printf("Entrez l'identifiant du logger : ");
//     // // scanf("%d", &user.idLogger);
//     // // printf("Entrez l'état : ");
//     // // scanf("%d", &user.etat);

//     // // fprintf(file, "%s %s %d %d %d\n", user.login, user.password, user.type, user.idLogger, user.etat);

//     // // fclose(file);
//     // fgets(ligne, sizeof(ligne), file);
//     // sscanf(ligne, "%s %s %d", user.login, user.password,&user.type);
//     // fclose(file);

//     // printf("Login : %s\n", user.login);
//     // printf("Mot de passe : %s\n", user.password) ;
//     // printf("User TYPE : %d\n", user.type);
//     // scanf("%s", login);
//     // scanf("%s", mdp);
//     // if (strcmp(login,user.login) == 0 && strcmp(mdp,user.password) == 0)
//     // {
//     //     printf("Password matches") ;
//     // }else
//     // {
//     //     printf("Password doesn't match") ;
//     // }
    
    
//     // return 0;
//     // char champ1[20], champ2[20];
//     // sscanf(ligne, "%s %s", champ1, champ2) ;
//         // Afficher les champs récupérés
// // int tentative=5;