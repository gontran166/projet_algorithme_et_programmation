#include <stdio.h>
#include <string.h>

void saisie(char *msg, char* var, int taille){
    do
    {
        printf("%s: ",msg);
        fgets(var,taille,stdin);
        var[strcspn(var,"\r\n")] = '\0';
    }while(strlen(var)==0);
}

int est_vide(char* chaine){
    unsigned int i;
    for(i=0; chaine[i]!='\0'; i++){
        if((chaine[i] >= 'a' && chaine[i]<='z') || (chaine[i] >= 'A' && chaine[i]<='Z')){
            return 0;
        }
    }
    return 1;
}

void traiter_nom(char *nom, char c1, char c2){
    char *c;
    for(int i=1; i<=strlen(nom); i++){
        if(nom[i]==c1){
            nom[i] = c2;
        }
    }
}

int main()
{
    char nom[50];
    saisie("Nom",nom,50);
    int r = est_vide(nom);
    printf(" r = %d\n",r);

    return 0;
}