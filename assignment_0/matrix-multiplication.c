#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i, j;
int n_max  = 100; 

double** generateRandomMatrix(int row, int column){
    double** M = (double**) malloc(column * sizeof(double*));;
    for(j = 0; j < row; j++){
        M[j] = (double*) malloc(row * sizeof(double));
        for(i = 0; i < column; i++){
            // generate matriz N x N
            M[j][i] = (double)rand()/n_max*2.0-1.0;
        }
    }
    printf ( "Matriz de tamanho %i por %i gerada \n", row, column);
    return M;
}

double* generateRandomVector(int size){
    double* vec_x = (double*) malloc(size * sizeof(double));
    for(j = 0; j < size; j++){
        // generate vector of size n
        vec_x[j] = (double)rand()/n_max*2.0-1.0;
    }
    printf ( "Vetor de tamanho %i gerado \n", size);
    return vec_x;
}

int main(int argc, char * argv [] )
{
    int N = strtol(argv[1], NULL, 10);
    double result[N];
    double** M = generateRandomMatrix(N,N);
    double*vec_x = generateRandomVector(N);
    // Fill matrix with random numbers
    srand(time(NULL));
    clock_t start = clock();
    for(i = 0; i < N; i++){
        double temp = 0;
        for(j = 0; j < N; j++){
            temp += M[i][j] * vec_x[j];
        }
        result[i] = temp;
    }
    clock_t end = clock();
    float time_elapsed = (float)(end - start) / CLOCKS_PER_SEC;
    printf ("Multiplicação tamanho %i calculada. Tempo: %f s \n", N, time_elapsed);
    return 0;
}