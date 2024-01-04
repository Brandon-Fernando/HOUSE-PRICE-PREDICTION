void invert(double **mtrx, double **identity, int size) {
    int i, j, x;
    double f;

    for(i = 0; i < size; i++) {
        f = mtrx[i][i];
        for(j = 0; j < size; j++) {
            mtrx[i][j] /= f;
            identity[i][j] /= f;
        }
        for(x = 0; x < size; x++) {
            if(x != i) {
                f = mtrx[x][i];
                for(j = 0; j < size; j++) {
                    mtrx[x][j] -= mtrx[i][j] * f;
                    identity[x][j] -= identity[i][j] * f;
                }
            }
        }
    }
}