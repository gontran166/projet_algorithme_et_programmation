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
    char nom[] = "NOMBO w Gontran";
    traiter_nom(nom,' ','-');
    printf("%s\n",nom);

    return 0;
}