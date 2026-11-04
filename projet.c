#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure de stockage de contact */
typedef struct Contact
{
    char nom[50];
    char telephone[20];
    char email[50];
}Contact;

/* Liste chainée des contacts */
typedef struct liste
{
    Contact contact;
    struct liste *suivant;
}ListeContact;

/* Rôle : permet de remplacer un caractère donnée par un autre dans une chaine.
    Dans notre contexte, cette fonction permet de remplacer les espaces dans 
    le nom(nom et prenom ou plusieurs prenom)par un autre caractère pour facilité
    la lecture dans le fichier.
   Paramètre :
    -char *nom : la chaine dont on souhaite remplacer un caratère donnée par un autre
    -char c1 : le caractère à remplacer
    -char c2 : le caratère à inserer.
   Retour : pas de valeur de retour;
*/
void traiter_nom(char *nom,char c1, char c2);

/* Rôle : Stockage des contacts en mémoire(dans un fichier)
   Paramètres:
    -ListeContact* contact : la liste de contacts
    -char* file_name : le nom du fichier dans lequel sauvegarder.
   Retour :
    -retourne 1 en cas succès
    -retourne 0 en d'échec
*/
int save_contact(ListeContact* contact, char* file_name);

/* Rôle : Création d'un neoud de la liste des contacts
   Paramètres :
    -Contact contact : Un type Contact (avec les champs nom,telephone,email)
   Retour : retour le neoud créer(l'adresse) ou NULL en cas d'échec
*/
ListeContact* creer_neoud_contact(Contact contact);

/* Rôle : Ajout d'un contact à la liste de contact
   Paramètre :
    -ListeContact **tete : la liste de contacts
    -Contact contact : le contact à ajouter
   Retour : retourne 1 en cas de succès et 0 en cas d'échec
*/
int ajouter_contact(ListeContact **tete, Contact contact);

/* Rôle : Chargement des contacts stocker en memoire et reconstitution 
    de la liste chaînée des contacts
   Paramètres :
    -char *file_name : le nombre du fichier dans lequel se trouve les contacts enregistrés
   Retour : retourne la liste de contact en cas de succès, NULL en cas de fichier vide ou d'échec
*/
ListeContact* charger_liste(char *file_name);

/* Rôle : Affichage de la lister de contacts
   Paramètre :
    -ListeContact *tete : liste de contact
   Retour:
*/
void lister_contact(ListeContact *tete);

/* Rôle : Rechercher un contact par son nom (recherche séquentielle,premier occurence trouvée)
   Paramètre :
    -ListeContact *tete : la liste de contacts
    -char *nom : le nom du contact à rechercher
   Retour : retourne le contact en cas de succès, NULL en cas d'échec
*/
ListeContact* recherche_contact(ListeContact *tete, char *nom);

/* Rôle : Suppression d'un contact de la liste
   Paramètres :
    -ListeContact **tete : la liste de contacts
    -char *telephone : le telephone du contact à supprimer
   Retour : retour 1 en cas de succès, 0 en cas d'échec
*/
int supprimer_contact(ListeContact **tete, char *telephone);

/* Rôle : Libération de la mémoire en fin du programme
   Paramètres:
    -ListeContact **tete : liste de contacts
   Retour: 
*/
void liberer(ListeContact **tete);

/* Rôle : Validation de saisie: cette fonction empêche la saisie de champ vide
   Paramètres :
    -const char *msg : message à afficher à l'écran pour l'utilisateur
    -char* var : variable pour stocker la valeur saisie
    -int taille : taille maximum de caractère voulu.
   Retour : 
*/
void validation_saisie(const char *msg, char* var, int taille);


int main()
{
    /* Gestionnaire de contact */
    unsigned int choix;
    ListeContact* liste = NULL;

    /* Chargement des contacts*/
    liste = charger_liste("contacts.txt");

    printf("================================ Gestionnaire de contacts =====================================\n");
    
    // Validation du choix
    do{
        printf("----------------------- Menu --------------------------------\n");
        printf("\t1-Ajouter un contact\n\t2-Supprimer un contact\n\t3-Lister les contacts\n");
        printf("\t4-Rechercher un contact\n\t5-Quitter le programme\n\nVôtre choix: ");
        if(scanf("%d",&choix) != 1){
            printf("Saisie invalide(la saisie doit être un nombre)\n");
            break;
        }
        while(getchar() != '\n');       // netoyage du tampon (consomme le \n laissé par scanf)
        printf("\n");

        switch (choix)
        {
            case 1 :{
                Contact contact;
                char nom[50];
                char tel[20];
                char email[50];
                printf("\tInformations du contact\n");
                
                // appel de la fonction validation_saisie pour valider les champs
                validation_saisie("NOM",nom,50);
                traiter_nom(nom,' ','-');
                
                validation_saisie("TELEPHONE",tel,20);
                validation_saisie("EMAIL",email,50);

                // contruction du contact: utilisation de snprintf pour éviter les débordements
                snprintf(contact.nom,sizeof(contact.nom),"%s",nom);
                snprintf(contact.telephone,sizeof(contact.telephone),"%s",tel);
                snprintf(contact.email,sizeof(contact.email),"%s",email);
                

                // appel de la fonction d'ajout
                int result = ajouter_contact(&liste,contact);
                if(result == 1){
                    printf("\tContact ajouté avec succès\n");
                }else{
                    printf("\tEchec de l'ajout du contact\n");
                }
                break;
            }
            
            case 2:{
                char tel[20];
                printf("\tSuppression de contact\n");
                validation_saisie("Telephone",tel,20);

                // appel de fonction supprimer_contact
                int result = supprimer_contact(&liste,tel);
                if(result == 1){
                    printf("\tContact supprimé avec succès\n");
                }else{
                    printf("\tEchec de la suppression du contact: contact non trouvé\n");
                }
                break;
            }
            
            case 3:{
                lister_contact(liste);
                break;
            }
            
            case 4:{
                char nom[50] ,tel[20], email[50];
                printf("\tRecherche de contact\n");
                validation_saisie("Nom",nom,50);
                traiter_nom(nom,' ','-');       // traiter le nom en remplacant les espaces par des -

                // appel de fonction supprimer_contact
                ListeContact *result = recherche_contact(liste,nom);
                if(result != NULL){
                    strcpy(nom , result->contact.nom);
                    strcpy(tel , result->contact.telephone);
                    strcpy(email , result->contact.email);
                    traiter_nom(nom,'-',' ');

                    printf("\tContact trouvé avec succès\n");
                    printf("Nom: %s\nTelephone: %s\nEmail: %s\n",nom,tel,email);
                }else{
                    traiter_nom(nom,'-',' ');
                    printf("\t Aucun contact trouvé avec le nom : %s\n",nom);
                }
                break;
            }

            case 5:{
                int s = save_contact(liste,"contacts.txt");
                if(s==1){
                    printf("\tContacts enregistrés avec succès dans le fichier\n");
                }else{
                    printf("\tEcher d'enregistrement dans le fichier\n");
                }

                printf("=============================== Fin du programme ==============================\n");
                
                // libération de la memoire
                liberer(&liste);
                break;
            }
            default:
                break;
        }
        printf("\n");
    }while(choix!=5);

    return 0;
}

void traiter_nom(char *nom, char c1, char c2){
    for(size_t i=1; i<=strlen(nom); i++){
        if(nom[i]==c1){
            nom[i] = c2;
        }
    }
}

int save_contact(ListeContact* contact, char* file_name){
    ListeContact *p;
    int re;

    FILE *fichier = fopen(file_name,"w");
    if(fichier != NULL){
        for(p=contact; p != NULL; p = p->suivant){
            re = fprintf(fichier,"Nom : %s | Telephone : %s | Email : %s\n",p->contact.nom,p->contact.telephone,p->contact.email);
            if(re < 0){
                fclose(fichier);
                return 0;
            }
        }
        fclose(fichier);        // fermeture du fichier
        return 1;
    }
    return 0;
}

ListeContact* creer_neoud_contact(Contact contact){
    ListeContact *noeud_contact = (ListeContact*)malloc(sizeof(ListeContact));
    if(noeud_contact != NULL){
        noeud_contact->contact = contact;
        noeud_contact->suivant = NULL;
        return noeud_contact;
    }
    return NULL;
}

int ajouter_contact(ListeContact **tete, Contact contact){
    ListeContact* new_contact = creer_neoud_contact(contact);
    if(new_contact != NULL)
    {
        new_contact->suivant = *tete;
        *tete = new_contact;
        return 1;
    }
    return 0;
}

ListeContact* charger_liste(char *file_name){

    ListeContact* liste = NULL;
    Contact contact;
    char nom[50];
    char tel[20];
    char email[50];

    FILE* fichier = fopen(file_name,"r");
    if(fichier != NULL){
        while(fscanf(fichier,"Nom : %s | Telephone : %s | Email : %s\n",nom,tel,email) != EOF){
            strncpy(contact.nom,nom,sizeof(nom));
            strncpy(contact.telephone,tel,sizeof(tel));
            strncpy(contact.email,email,sizeof(email));
            

            ajouter_contact(&liste,contact);
        }
        fclose(fichier);
        return liste;
    }
    return NULL;
}

void lister_contact(ListeContact *tete){
    printf("------------------------- Liste de contacts ----------------------------\n");
    if(tete != NULL){
        int i = 1;
        ListeContact *p;
        char nom[50] ,tel[20], email[50];

        for(p=tete; p!=NULL; p = p->suivant){
            strcpy(nom , p->contact.nom);
            strcpy(tel , p->contact.telephone);
            strcpy(email , p->contact.email);
            traiter_nom(nom,'-',' ');
            printf("\tContact %d\n",i);
            printf("Nom: %s\nTEL: %s\nEmail: %s\n",nom, tel,email);
            i++;
        }
    }else{
        printf("Aucun contact enregistré\n");
    }
    printf("------------------------ Fin liste ----------------------------------\n");
}

ListeContact* recherche_contact(ListeContact *tete, char *nom){
    ListeContact *p;
    for(p=tete; p!=NULL; p=p->suivant){
        if(strcmp(nom,p->contact.nom) == 0){
            return p;
        }
    }
    return NULL;
}

int supprimer_contact(ListeContact **tete, char *telephone){
    ListeContact *p;
    ListeContact *c;
    
    if(*tete!=NULL){
        // l'élément à supprimer est le premier contact de la liste
        if(strcmp(telephone,(*tete)->contact.telephone)==0){
            c = *tete;
            *tete = (*tete)->suivant;
            free(c);
            return 1;
        }else{
            for(p=*tete; p->suivant!=NULL; p=p->suivant){
                if(strcmp(telephone,p->suivant->contact.telephone)==0){
                    c = p->suivant;
                    p->suivant = p->suivant->suivant;
                    free(c);
                    return 1;
                }
            }
        }
    }

    return 0;
}

void liberer(ListeContact **tete){
    ListeContact *p, *c;
    p = *tete;
    while(p != NULL){
        c = p;
        p = p->suivant;
        free(c);
    }
    *tete = NULL;
}

void validation_saisie(const char *msg, char* var, int taille){
    do
    {
        printf("%s: ",msg);
        fgets(var,taille,stdin);
        var[strcspn(var,"\r\n")] = '\0';        // netoyage de la chaine entré (supprimé le retour à la ligne)
    }while(strlen(var)==0);
}
