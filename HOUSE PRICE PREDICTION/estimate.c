#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//method to multiply matrix 
void multiply(double **mtrxOne, double **mtrxTwo, double **result, int row, int col, int n){
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            result[r][c] = 0;
            for(int x = 0; x < n; x++){
                result[r][c] += mtrxOne[r][x] * mtrxTwo[x][c];
            }
        }
    }
}



//method to transosing 
void transposeMtrx(double **mtrx, double **result, int row, int col){
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            result[i][j] = mtrx[j][i];
        }
    }
}


//method to invert
void invert(double **mtrx, double **identity, int size){
    int i, j, x;
    double f;

    for(i = 0; i < size; i++){
        f = mtrx[i][i];
        for(j = 0; j < size; j++){
            mtrx[i][j] /= f;
            identity[i][j] /= f;
        }
        for(x = 0; x < size; x++){
            if(x != i){
                f = mtrx[x][i];
                for(j = 0; j < size; j++){
                    mtrx[x][j] -= mtrx[i][j] * f;
                    identity[x][j] -= identity[i][j] * f;
                }
            }
        }
    }

    for(i = size - 1; i >= 0; i--){
        for(x = i -1; x >= 0; x--){
            f = mtrx[x][i];
            for(j = 0; j < size; j++){
                mtrx[x][j] -= mtrx[i][j] * f;
                identity[x][j] -= identity[x][j] * f;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *train = fopen(argv[1], "r");
    FILE *data = fopen(argv[2], "r");

    if(train == NULL || data == NULL){
        return 1;
    }

    char type1[100];
    fscanf(train, "%s", type1);

    char type2[100];
    fscanf(data, "%s", type2);


    
    int kTrain; //col
    fscanf(train, "%d", &kTrain);
    kTrain = kTrain+1;

    int n; //row
    fscanf(train, "%d", &n);

    //matrix X and Matrix Y 
    double **mtrxX = (double **)malloc(n * sizeof(double *));
    double **mtrxY = (double **)malloc(n * sizeof(double *));
    for(int r = 0; r < n; r++){
        mtrxX[r] = (double *)malloc(kTrain * sizeof(double));
        for(int c = 0; c < kTrain; c++){
            if(c == 0){
                mtrxX[r][c] = 1;
            }else{
                fscanf(train, "%lf", &mtrxX[r][c]);
            }
        }
        mtrxY[r] = (double *)malloc(sizeof(double));
        fscanf(train, "%lf", &mtrxY[r][0]);
    }
    

    int kData; //col
    fscanf(data, "%d", &kData);
    kData = kData +1 ;

    int m; //row
    fscanf(data, "%d", &m);

    //data matrix 
    double **mtrxXprime = (double **)malloc(m * sizeof(double *));
    for(int r = 0; r < m; r++){
        mtrxXprime[r] = (double *)malloc(kData * sizeof(double));
        for(int c = 0; c < kData; c++){
            if(c == 0){
                mtrxXprime[r][c] = 1;
            }else{
                fscanf(data, "%lf", &mtrxXprime[r][c]);  
            }
        }
    }

    

    // //the result for the transposed matrix X
    double **transposed = (double **)malloc(kTrain * sizeof(double *));
    for(int r = 0; r < kTrain; r++){
        transposed[r] = (double *)malloc(n * sizeof(double));
    }

    
    transposeMtrx(mtrxX, transposed, n, kTrain);


    //the restult when you multiply X^T and X 
    double **transMult = (double **)malloc(kTrain * sizeof(double *));
    for(int r = 0; r < kTrain; r++){
        transMult[r] = (double *)malloc(kTrain * sizeof(double));
    }

    
    multiply(transposed, mtrxX, transMult, kTrain, kTrain, n);

    //the result when you find the inverse of(X^TX)
    double **identity = (double **)malloc(kTrain * sizeof(double *));
    for(int r = 0; r < kTrain; r++){
        identity[r] = (double *)malloc(kTrain * sizeof(double));
        for(int c = 0; c < kTrain; c++){
            if(r == c){
                identity[r][c] = 1;
            }else{
                identity[r][c] = 0;
            }
        }
    }

    invert(transMult, identity, kTrain);

    //the result of (X^TX)^-1 X^T
    double **invXtrans = (double **)malloc(kTrain * sizeof(double *));
    for(int r = 0; r < kTrain; r++){
        invXtrans[r] = (double *)malloc(n * sizeof(double));
    }

    multiply(identity, transposed, invXtrans, kTrain, n, kTrain);



    //the result of (X^TX)^-1 X^T Y which is the weight
    double **weight = (double **)malloc(n * sizeof(double *));
    for(int r = 0; r < n; r++){
        weight[r] = (double *)malloc(sizeof(double));
    }


    multiply(invXtrans, mtrxY, weight, kTrain, 1, n);

    
    double **prices = (double **)malloc(m * sizeof(double *));
    for(int r = 0; r < m; r++){
        prices[r] = (double *)malloc(sizeof(double));
    }

    multiply(mtrxXprime, weight, prices, m, 1, kTrain);


    for(int r = 0; r < m; r++){
        for(int c = 0; c < 1; c++){
            printf("%.0f\n", prices[r][c]);
        }
    }




    for(int r = 0;r < m; r++){
        free(prices[r]);
        free(mtrxXprime[r]);
    }
    free(prices);
    free(mtrxXprime);
    for(int r = 0; r < n; r++){
        free(mtrxX[r]);
        free(mtrxY[r]);
        free(weight[r]);
    }
    
    free(mtrxX);
    free(mtrxY);
    free(weight);

    for(int r = 0; r < kTrain; r++){
        free(transposed[r]);
        free(transMult[r]);
        free(identity[r]);
        free(invXtrans[r]);

    }
    free(transposed);
    free(transMult);
    free(identity);
    free(invXtrans);
    

    fclose(train);
    fclose(data);
    return 0;
}