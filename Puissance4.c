#include <stdio.h>
#include <stdlib.h> 

#define MAX_LIG 6
#define MAX_COL 7

typedef char grille[MAX_LIG][MAX_COL];

void initGrille(grille G){
    int i, j;
    for (i=0; i<MAX_LIG; i++){
        for (j=0; j<MAX_COL; j++)
            G[i][j]='.';
    }
}

void afficheGrille(grille G){
    int i, j, c;
    printf("   ");
    for (c=1; c<MAX_COL+1; c++){
        printf(" %i  ",c);
    }
    printf("\n");
    for (i=0; i<MAX_LIG; i++){
        printf("%i |",i+1);
        for (j=0; j<MAX_COL; j++)
            printf(" %c |",G[i][j]);
        printf("\n");
    }
}


void sauvergarde_partie(int joueur, grille G, char nomfic[]){
    FILE *f;
    int i,j; 
    int ecrasement; 
    char choix;

    ecrasement=1;
    if ((f=fopen(nomfic,"r"))!=NULL)
    {
        fclose(f);
        do
        {
            printf("Le fichier %s existe, voulez-vous l'ecraser ? (o/n) ",nomfic);
            scanf(" %c",&choix);
        }
        while (choix!='o' && choix!='n');
        if (choix=='n')
        {
            ecrasement=0;
        }
    }
    if (ecrasement)
    {
        if ((f=fopen(nomfic,"w"))==NULL)
            printf("Erreur lors de la creation du fichier %s\n",nomfic);
        else 
        {
            fprintf(f,"%i\n",joueur);
            for(i=0;i<MAX_LIG;i++){
                for(j=0;j<MAX_COL;j++){
                    fprintf(f,"%c ",G[i][j]);
                }
                fprintf(f,"\n");
            }
            fclose(f);
        }
    }
}

int charger_partie(char nomfic[],grille G,int *joueur)
{
    FILE *f; 
    int i,j;

    if ((f=fopen(nomfic,"r"))==NULL)
    {
        return(0);
    }
    else
    {
        printf("Ouverture du fichier %s reussie.\n",nomfic);
        fscanf(f,"%i",joueur);
        printf("%i", joueur);
        for (i=0; i<MAX_LIG; i++){
            for (j=0; j<MAX_COL; j++)
                fscanf(f," %c ",&G[i][j]);
        }
        fclose(f);
        printf("Lecture des donnees terminee.\n\n");
        return(1);
    }
}


int grillePleine(grille G){
    int rempli = 0;
    int i, j;
    for (i=0; i<MAX_LIG; i++){
        for (j=0; j<MAX_COL; j++)
            if(G[i][j] != '.'){
                rempli+=1;
            }
    }
    if(rempli==(MAX_COL*MAX_LIG)){
        return 1;
    }
    else{
        return 0;
    }
}

int ajoutejeton(grille G, int j) {
    int colonne,ok;
    int i = 5;
    ok = 0;

    printf("Dans quelle colonne voulez-vous jouer ? ( entre 1 et 7 / 100 pour sauvegarder)\n--> ");
    scanf("%d", &colonne);
    if(colonne==100){
        sauvergarde_partie(j,G,"sauvegarde_partie");
        return 1;
    } else
    {
        colonne -= 1;
        while  (ok == 0) {
            if (G[0][colonne] == '.') {
                do {
                    if ( G[i][colonne] == '.'){
                        if (j == 1) {
                            G[i][colonne] = 'X';
                            ok = 1;
                        }
                        if (j == 0) {
                            G[i][colonne] = 'O';
                            ok = 1;
                        }
                    }
                    else {
                        i = i-1;
                    }
                } while (i < 0 || ok == 0);
            }
            else {
                printf("\nLa colonne est pleine\n");
                printf("Dans quelle colonne voulez-vous jouer ? ( entre 1 et 7 )\n--> ");
                scanf("%d\n", &colonne);
                colonne -= 1;
            }
        }
        return 0;
    }
    
    
}

int verifLigne(grille G, int joueur){
    int i, j;
    int compeur = 0;
    if (joueur == 1){
        for (i=0; i<=MAX_LIG;i++){
            for (j=0; j<=MAX_COL;j++){
                if(G[i][j]=='X'){
                    compeur++;
                }
                if(G[i][j]!='X'){
                    compeur=0;
                }
                if(compeur==4){
                    return 1;
                }
            }
            compeur=0;
        }
        return 0;
    }
    if (joueur == 0){
        for (i=0; i<=MAX_LIG;i++){
            for (j=0; j<=MAX_COL;j++){
                if(G[i][j]=='O'){
                    compeur++;
                }
                if(G[i][j]!='O'){
                    compeur=0;
                }
                if(compeur==4){
                    return 1;
                }
            }
            compeur=0;
        }
        return 0;
    }
}

int verifCol(grille G, int joueur){
    int i, j;
    int compeur = 0;
    if (joueur == 1){
        for (i=0; i<=MAX_COL;i++){
            for (j=0; j<=MAX_LIG;j++){
                if(G[j][i]=='X'){
                    compeur++;
                }
                if(G[j][i]!='X'){
                    compeur=0;
                }
                if(compeur==4){
                    return 1;
                }
            }
            compeur=0;
        }
        return 0;
    }
    if (joueur == 0){
        for (i=0; i<=MAX_COL;i++){
            for (j=0; j<=MAX_LIG;j++){
                if(G[j][i]=='O'){
                    compeur++;
                }
                if(G[j][i]!='O'){
                    compeur=0;
                }
                if(compeur==4){
                    return 1;
                }
            }
            compeur=0;
        }
        return 0;
    }
}

int verifDiag(grille G, int joueur){
    int i,j;
    if(joueur==1){
        for (i=0; i<=MAX_LIG;i++){
            for (j=0; j<=MAX_COL;j++){
                if(G[i][j]=='X' && G[i+1][j+1]=='X' && G[i+2][j+2]=='X' && G[i+3][j+3]=='X'){
                    return 1;
                } if(G[i][j]=='X' && G[i-1][j-1]=='X' && G[i-2][j-2]=='X' && G[i-3][j-3]=='X'){
                    return 1;
                } if(G[i][j]=='X' && G[i+1][j-1]=='X' && G[i+2][j-2]=='X'&& G[i+3][j-3]=='X'){
                    return 1;
                } if(G[i][j]=='X' && G[i-1][j+1]=='X' && G[i-2][j+2]=='X'&& G[i-3][j+3]=='X'){
                    return 1;
                }
            }
        }
        return 0;
    }
    if(joueur==0){
        for (i=0; i<=MAX_LIG;i++){
            for (j=0; j<=MAX_COL;j++){
                if(G[i][j]=='O' && G[i+1][j+1]=='O' && G[i+2][j+2]=='O' && G[i+3][j+3]=='O'){
                    return 1;
                } if(G[i][j]=='O' && G[i-1][j-1]=='O' && G[i-2][j-2]=='O' && G[i-3][j-3]=='O'){
                    return 1;
                } if(G[i][j]=='O' && G[i+1][j-1]=='O' && G[i+2][j-2]=='O'&& G[i+3][j-3]=='O'){
                    return 1;
                } if(G[i][j]=='O' && G[i-1][j+1]=='O' && G[i-2][j+2]=='O'&& G[i-3][j+3]=='O'){
                    return 1;
                }
            }
        }
        return 0;
    }
}

int jeuFini(grille G, int joueur){
    if (verifCol(G,joueur)==1 || verifLigne(G,joueur)==1 || verifDiag(G,joueur)==1){
        return 1;
    } if (grillePleine(G)==1){
        return 2;
    } return 0;
}


int affiche_menu(){
    int choix;
    printf("\nPUISSANCE 4 PAR Clement BERDIN\n");
    printf("\n 1 - Nouvelle partie\n");
    printf(" 2 - Continuer une partie sauvegardee\n");
    printf(" 3 - Quitter\n\n --> ");
    scanf("%i",&choix);
    if (choix!=1 && choix!=2 && choix!=3){
        printf("********************\n   CHOIX INVALIDE  \n********************\n");
        affiche_menu();
    } else {
        return choix;
    }
}

void jeu(grille G){
    int i, j;
    int ok = 0;
    afficheGrille(G);
    do {
        i = i%2;
        i += ajoutejeton(G,i);
        afficheGrille(G);
        ok = jeuFini(G,i);
        i++;
    } while (ok == 0);
    if (ok==1){
        printf("Le joueur %i est le gagnant de la partie ! ", i);
    } if (ok==2){
        printf("Il n'y a pas de gagnant, c'est une egalite");
    }
}

int demarrage(grille G){
    int i;
    int chemin = affiche_menu();
    if(chemin==1){
        jeu(G);
        return 0;
    } if (chemin==2){
        charger_partie("sauvegarde_partie",G,&i);
        jeu(G);
        return 0;
    } if (chemin==3){
        return 1;
    }
}

int main(){
    grille G;
    initGrille(G);
    int i = 0;
    if (demarrage(G)==1)
    {
        return 1;
    }
}