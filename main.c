#include <stdio.h>
#include <stdlib.h>
typedef int Matrice[100][100], Vecteur[100];
/* Fonction qui permet de saisir un tableau */
void lireTab(Vecteur T, int n){
    for(int i = 0; i < n; i++){
        printf("T[%d] = ",i);
        scanf("%d",&T[i]);
    }
}
/* Fonction qui permet d'afficher un tableau */
void afficherTab(Vecteur T, int n){
    for(int i = 0; i < n; i++){
        printf("\t%d",T[i]);
    }
    printf("\n");
}
/* Fonction qui permet de saisir une matrice */
void lireMatrice(Matrice M, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("M[%d][%d] = ",i,j);
            scanf("%d",&M[i][j]);
        }
        printf("\n");
    }
}
/* Fonction qui permet d'afficher une matrice */
void afficherMatrice(Matrice M, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("\t%d",M[i][j]);
        printf("\n");
    }
    printf("\n");
}
/* Fonction qui permet de calculer le produit d'une matrice et un vecteur */
void produitMatriceVecteur(Matrice M, Vecteur T1, Vecteur T2, int n){
    int som;
    for(int i = 0; i < n; i++){
        som = 0;
        for(int k = 0; k < n; k++)
            som+=M[i][k]*T1[k];
        T2[i]=som;
    }
}
/*Fonction qui permet de resourdre un system lineaire d'une matrice triangulaire inf */
void Descente(Matrice A, Vecteur B, Vecteur X,  int n){
    int som;
    X[0] = B[0]/A[0][0];
    for(int i = 1; i <= n-1; i++){
        som = 0;
        for(int j = i-1; j>=0; j--){
            som+=A[i][j]*X[j];
        }
        X[i] = (B[i]-som)/A[i][i];
    }
}
/*Fonction qui permet de resourdre un system lineaire d'une matrice triangulaire sup */
void Remonte(Matrice A, Vecteur B, Vecteur X, int n){
    int som;
    X[n-1] = B[n-1]/A[n-1][n-1];
    for(int i = n-2; i>= 0; i--){
        som = 0;
        for(int k = i+1; k <= n-1; k++){
            som+=A[i][k]*X[k];
        }
        X[i] = (B[i]-som)/A[i][i];
    }
}
/* Fonction qui permet de tester si une matrice est triangulaire sup */
int MatriceTriangulaireSuperieur(Matrice M, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(M[i][j] != 0 && i!=j)
            return 0;
        }
    }
    return 1;
}
/* Fonction qui permet de tester si une matrice est triangulaire inf */
int MatriceTriangulaireInferieur(Matrice M, int n){
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(M[i][j] != 0 && i!=j)
            return 0;
        }
    }
    return 1;
}
void menu(){
    printf("\n  ================================== MENU ==================================   ");
    printf("\n|\t1.  Resourdre un system lineaire triangulaire superieur (REMONTEE)          ");
    printf("\n|\t2.  Resourdre un system lineaire triangulaire inferieur (DESCENTE)          ");
    printf("\n|\t3.  Tester la matrice.                                                      ");
    printf("\n|\t -----------------------------------------------------------------          ");
    printf("\n|\t0. Quitter.                                                                 ");
    printf("\n ==========================================================================    ");
    printf("\n\tDonnez vote choix : ");
}
int main()
{
    Matrice A;
    Vecteur B;
    Vecteur X;
    Vecteur Produit;
    int n;
    int choix;
    int estVerifie = 0;
    int testVerifie = 1;
    do{
            menu();
            scanf("%d",&choix);
            switch(choix){
                case 1:{ /* saisir et afficher les elements d'une matrice puis resourdre le system si la matrice est traingulaire sup */
                    printf("\n\tVeuillez entrer la taille de la matrice <n> : ");
                    scanf("%d",&n);
                    lireMatrice(A,n,n);
                    if(MatriceTriangulaireSuperieur(A,n) != 1){
                        printf("\n\tLa matrice n'est pas triangulaire superieure.\n");
                        estVerifie = 0;
                    }
                    else{
                        printf("\n\tLes elements de la matrice <A> sont : \n");
                        afficherMatrice(A,n,n);
                        printf("\n\t Veuillez entrer les elements du vecteur <B> : \n");
                        lireTab(B,n);
                        printf("\n\tLes elements du vecteur <B> sont : \n");
                        afficherTab(B,n);
                        Remonte(A,B,X,n);
                        printf("\n\tLa solution est le vecteur <X> : \n");
                        afficherTab(X,n);
                        estVerifie = 1;
                    }
                }
                break;
                case 2:{ /* saisir et afficher les elements d'une matrice puis resourdre le system si la matrice est traingulaire inf */
                    printf("\n\tVeuillez entrer la taille de la matrice <n> : ");
                    scanf("%d",&n);
                    lireMatrice(A,n,n);
                    if(MatriceTriangulaireInferieur(A,n) != 1){
                        printf("\n\tLa matrice n'est pas triangulaire inferieure.\n");
                        estVerifie = 0;
                    }
                    else{
                        printf("\n\tLes elements de la matrice <A> sont : \n");
                        afficherMatrice(A,n,n);
                        printf("\n\t Veuillez entrer les elements du vecteur <B> : \n");
                        lireTab(B,n);
                        printf("\n\tLes elements du vecteur <B> sont : \n");
                        afficherTab(B,n);
                        Descente(A,B,X,n);
                        printf("\n\tLa solution est le vecteur <X> : \n");
                        afficherTab(X,n);
                        estVerifie = 1;
                    }
                }
                break;
                case 3:{ /* Tester si le system A * X = B */
                    if(estVerifie != 1){ // afficher un message d'erreur quand l'utilisateur n'a pas entrer un system
                        printf("\n\tErreur! entrez une matrice et un vecteur d'abord\n");
                        estVerifie = 0;
                    }
                    else{
                        produitMatriceVecteur(A,X,Produit,n);
                        for(int i = 0; i < n; i++){ // verification du system
                            if(Produit[i] != B[i]){
                                testVerifie = 0;
                                break;
                            }
                        }
                        if(testVerifie != 1)
                            printf("\n\tLe system A * X = B n'est pas verifie !\n");
                        else{
                            printf("\n\tLe system A * X = B est verifie et le produit de la matrice A et le vecteur X : \n");
                            afficherTab(Produit,n);
                        }
                    }
                }
                break;
                case 0:{}

            }

    }while(choix !=0);
    return 0;
}
