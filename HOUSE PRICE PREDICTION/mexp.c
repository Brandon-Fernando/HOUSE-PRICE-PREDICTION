#include <stdio.h>
#include <stdlib.h>


void multiply(int **mtrx, int **tempMtrx, int **resultMtrx, int k){
    for(int r = 0; r < k; r++){
        for(int c = 0; c < k; c++){
            resultMtrx[r][c] = 0;
            for(int x = 0; x < k; x++){
                resultMtrx[r][c] += mtrx[r][x] * tempMtrx[x][c];
            }
        }
    }
}


int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");

    if(file == NULL){
        return 1;
    }

    int k;
    fscanf(file,"%d", &k);

    int **mtrx = (int **)malloc(k * sizeof(int *));
    for(int row = 0; row < k; row++){
        mtrx[row] = (int *)malloc(k * sizeof(int));
        for(int col = 0; col < k; col++){
            fscanf(file, "%d", &mtrx[row][col]);
        }
    }

    int n;
    fscanf(file, "%d", &n);
    fclose(file);

    int **resultMtrx = (int **)malloc(k * sizeof(int *));
    for(int r = 0; r < k; r++){
        resultMtrx[r] = (int *) malloc(k * sizeof(int));
    }
    

    int **tempMtrx = (int **)malloc(k * sizeof(int *));
    for(int r = 0; r < k; r++){
        tempMtrx[r] = (int *)malloc(k * sizeof(int));
        for(int c = 0; c < k; c++){
            tempMtrx[r][c] = mtrx[r][c];
        }
    }

    if(n == 0){
        for(int r = 0; r < k; r++){
            for(int c = 0; c < k; c++){
                if(r == c){
                    resultMtrx[r][c] = 1;
                }else{
                    resultMtrx[r][c] = 0;
                }
            }
        }
    }else{
        for(int i = 0; i < n-1; i++){
        multiply(mtrx, tempMtrx, resultMtrx, k);
        
        for(int r = 0; r < k; r++){
            for(int c = 0; c < k; c++){
                tempMtrx[r][c] = resultMtrx[r][c];
            }
        }

        }
    }


    for(int r = 0; r < k; r++){
        for(int c = 0; c < k; c++){
            if(c == k-1){
                printf("%d", resultMtrx[r][c]);
            }else{
                printf("%d ", resultMtrx[r][c]);
            }
        }
        printf("\n");
    }
    
    for(int r = 0; r < k; r++){
        free(mtrx[r]);
        free(tempMtrx[r]);
        free(resultMtrx[r]);
    }
    free(mtrx);
    free(tempMtrx);
    free(resultMtrx);

    return 0;
}