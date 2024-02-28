#include <stdio.h>
#include <stdlib.h>

int input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);

int main(void) {
    int **matrix_first = NULL, n_first, m_first;

    if (scanf("%d %d", &n_first, &m_first) != 2 || getchar() != '\n') return 1;
    matrix_first = (int **)malloc(n_first * sizeof(int));

    if (input(matrix_first, &n_first, &m_first) != 0) {
        printf("n/a");
        return 1;
    }
    output(matrix_first, n_first, m_first);

     for (int i = 0; i < n_first; ++i)
     {
        free(matrix_first[i]);
     }
        free(matrix_first);
    return 0;
}

int input(int **matrix, int *n, int *m) {
    if(!matrix) return 1;
    for (int i = 0; i < *n; ++i) {
        matrix[i] = (int *)malloc(*m * sizeof(int));
        if(!matrix[i]) return 1;
        for (int j = 0; j < *m; ++j)
            if (scanf("%d", &matrix[i][j]) != 1) return 1;
    }

    if (getchar() != '\n') return 1;

    return 0;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", matrix[i][j]);
            if (j != m - 1) printf(" ");
        }
        if (i != n - 1) printf("\n");
    }
}

