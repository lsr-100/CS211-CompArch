#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

FILE *matfile;
matfile = fopen(argv[1], "r");
int rowcol, n;

fscanf(matfile, "%d", &rowcol);

/*allocating space for row in matrix as in lecture*/
int **mat1 = (int **)malloc(rowcol * sizeof(int *));
int **mat2 = (int **)malloc(rowcol * sizeof(int *));
int **result = (int **)malloc(rowcol*sizeof(int *));

/*edge case for n = 0, identity matrix to be printed*/
int **identityMatrix = (int **)malloc(rowcol * sizeof(int *)); 

/*allocating space for column in matrix as in lecture*/
for (int a = 0; a < rowcol; a++){
    mat1[a] = (int *)malloc(rowcol * sizeof(int));
    mat2[a] = (int *)malloc(rowcol * sizeof(int));
    result[a] = (int *)malloc(rowcol * sizeof(int));
    identityMatrix[a] = (int *)malloc(rowcol * sizeof(int)); 
}


/*getting the inputs into a matrix and creating a copy*/
for (int b = 0; b < rowcol; b++){
    for (int c = 0; c < rowcol; c++){

        fscanf(matfile, "%d", &mat1[b][c]);
        mat2[b][c] = mat1[b][c];
    }
}


/*take in the exponent*/
fscanf(matfile, "%d", &n);

/*edge case -- hard coded identity matrix --- exponent = 0; */
if(n == 0){
    for (int d = 0; d < rowcol; d++)
    {
        for (int e = 0; e < rowcol; e++)
        {
            if (d == e)
                printf("%d ", 1);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
    return 0;
}

/*edge case -- return og matrix if exponent = 1*/
if (n == 1){
    for(int f=0; f<rowcol; f++) {
        for(int g=0; g<rowcol; g++) {
            printf("%d ", mat1[f][g]);
        }
    printf("\n");
  }
  return 0; 
}

/*Matrix multiplication*/
for (int h = 0; h < n-1; h++){

    for (int i = 0; i < rowcol; i++)
    {
        for (int j = 0; j < rowcol; j++){
            result[i][j] = 0;
            for (int k = 0; k < rowcol; k++)
                result[i][j] = result[i][j] + (mat1[i][k] * mat2[k][j]);
        }
    }
    for(int l=0;l<rowcol; l++){
        for(int m=0;m<rowcol; m++){
            mat2[l][m] = result[l][m];
        }
    }
}

for(int n=0;n<rowcol; n++){
    for(int o=0;o<rowcol; o++){
        if(o==(rowcol-1)){
        printf("%d", result[n][o]);
        }
        else
        printf("%d ", result[n][o]); 
    }
    printf("\n");
}


/*free stuff that was malloced*/
//could make another function to free
for(int i = 0; i < rowcol; ++i){
    free(mat1[i]); 
    free(mat2[i]); 
    free(result[i]); 
    free(identityMatrix[i]); 
}
free(mat1); 
free(mat2); 
free(result); 
free(identityMatrix); 


fclose(matfile);
return 0;
}






