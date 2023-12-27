#include <stdlib.h>
#include <stdio.h>

double ** transpose(double ** copy,int row,int col, double **done){

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            done[i][j] = copy[j][i];
        }
    }
    
    return done;
}

double** multiply(double** copy1, double** copy2, int col, int row, int col1, double** done1) {  // Algorithm to Multiply
    
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col1; j++) {
            done1[i][j] = 0;
        }
    }

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col1; j++) {
            for (int k = 0; k < row; k++) {
                done1[i][j] += copy1[i][k] * copy2[k][j];
            }
        }
    }

    return done1;
}


double ** inverse(double ** M, double** N, int n) {   

    //translated psuedocode 
    double f;
    for(int i = 0; i < n; i++){
        for(int j = 0; j<n; j++){
            if(i==j){
                N[i][j]= 1;
            }
            else{
                N[i][j]=0;
            }
        }
    }   

    for(int p = 0; p<n; p++){
        f = M[p][p];

        for(int j =0; j<n; j++){
            M[p][j] = M[p][j]/f;
            N[p][j] = N[p][j]/f;
        }

        for(int i =p+1; i<n; i++){
            f = M[i][p];

            for(int j =0; j<n; j++){
                M[i][j] = M[i][j] - (M[p][j]*f);
                N[i][j] = N[i][j] - (N[p][j]*f);
            }
            
        }
    }

    for(int p = n-1; p >= 0; p--){
        for(int i = p-1; i >= 0; i--){
            f = M[i][p];
            for(int j =0; j<n; j++){
                M[i][j] = M[i][j] - (M[p][j]*f);
                N[i][j] = N[i][j] - (N[p][j]*f);
            }
            
        }
    }

    return N;
} 


double * vectormult(double ** copy,double * vectcopy,int row,int col, double* done3) {

    for (int i = 0; i < row; i++) {
        done3[i] = 0;
    }
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            done3[i] += copy[i][j] * vectcopy[j];
        }
    }

    return done3;
}

int main(int argc,char ** argv) {
  
    char filename[20] = {}; 

    FILE * train = fopen(argv[1],"r");
    FILE * data = fopen(argv[2],"r");

    fscanf(train,"%s\n",filename);

    int col;
    int row;
    
    fscanf(train,"%d\n",&col);
    fscanf(train,"%d\n",&row);
    col++; 

    double ** myMatrix;
    double ** X;
    double *Y;
    double * W;
    double ** Xtranspose; 
    double ** multin;
    double ** transpose_mult;
    double ** inverse_mult;
    double * price_mult;
    
    myMatrix = (double **) malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++) {
        myMatrix[i] = (double *) malloc(col * sizeof(double));
    }

    X = (double **) malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++) {
        X[i] = (double *) malloc(col * sizeof(double));
    }

    Y = (double *) malloc(row * sizeof(double *)); 

    W = (double *) malloc(col * sizeof(double));

    Xtranspose = (double **) malloc(col * sizeof(double *));
    for (int i = 0; i < col; i++) {
        Xtranspose[i] = (double *) malloc(row * sizeof(double));
    }
    
    multin = (double **) malloc(col * sizeof(double *));; 
    for (int i = 0; i < col; i++) {
        multin[i] = (double *) malloc(col * sizeof(double));
    }

    transpose_mult = (double **) malloc(col * sizeof(double *)); 
    for (int i = 0; i < col; i++) {
        transpose_mult[i] = (double *) malloc(col * sizeof(double));
    }

    inverse_mult = (double **) malloc(col * sizeof(double *)); 
    for (int i = 0; i < col; i++) {
        inverse_mult[i] = (double *) malloc(row * sizeof(double));
    }

    price_mult = (double *) malloc(row * sizeof(double *)); 

    //X first column is all 1's
    for (int i = 0; i < row; i++) {
        X[i][0] = 1;
    }

    //input train data into temp matrix    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fscanf(train,"%lf ",&myMatrix[i][j]);  
        }
        fscanf(train,"\n");
    }
    
   for (int i = 0; i < row; i++) { 
        for (int j = 1; j < col; j++) {
            X[i][j] = myMatrix[i][j-1];
        }
    }

    for (int i = 0; i < row; i++) {
        Y[i] = myMatrix[i][col-1];
    }

    Xtranspose = transpose(X,row,col, Xtranspose);
    transpose_mult = multiply(Xtranspose,X,col,row,col,transpose_mult);     
    multin = inverse(transpose_mult,multin,col);
    inverse_mult = multiply(multin,Xtranspose,col,col,row,inverse_mult); 
    W = vectormult(inverse_mult,Y,col,row, W); 

    double ** Xprime;

    fscanf(data,"%s\n",filename);

    fscanf(data,"%d\n",&col);
    fscanf(data,"%d\n",&row);
    col++; 

    //allocating for Xprime
    Xprime = (double **) malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++) {
        Xprime[i] = (double *) malloc(col * sizeof(double));
        Xprime[i][0] = 1; 
    }
    
    //train data input
    for (int i = 0; i < row; i++) {
        for (int j = 1; j < col; j++) {
           fscanf(data,"%lf ",&Xprime[i][j]);
        }
        fscanf(data,"\n");
    }
    
    //multiply Xprime and W
    price_mult = vectormult(Xprime,W,row,col,price_mult);

    //printing final matrix Yprime
    for (int i = 0; i < row; i++) {
        printf("%.0f\n",price_mult[i]);
    }

    for(int f = 0; f < col; f++){
        free(Xtranspose[f]); 
        free(transpose_mult[f]); 
        free(inverse_mult[f]); 
        free(multin[f]); 
    }
    free(Xtranspose); 
    free(transpose_mult);
    free(inverse_mult); 
    free(multin); 
    free(W);
    free(Y);
    free(price_mult);

    for(int f = 0; f < row; f++){
        free(Xprime[f]); 
    }
    free(Xprime); 

    exit(0);
}

