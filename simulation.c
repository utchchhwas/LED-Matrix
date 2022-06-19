#include <stdio.h>

#define N 8

unsigned char mat1[N][N] = {
//  0  1  2  3  4  5  6  7
    1, 0, 0, 0, 0, 0, 0, 0, // 0
    0, 1, 0, 0, 0, 0, 0, 0, // 1
    0, 0, 1, 0, 0, 0, 0, 0, // 2
    0, 0, 0, 1, 0, 0, 0, 0, // 3
    0, 0, 0, 0, 1, 0, 0, 0, // 4
    0, 0, 0, 0, 0, 1, 0, 0, // 5
    0, 0, 0, 0, 0, 0, 1, 0, // 6
    0, 0, 0, 0, 0, 0, 0, 1  // 7
};

unsigned char get_row(unsigned char* row) {
    unsigned char res = 0;
    for (int j = 0; j < N; ++j) {
        res |= (row[j] << j);
    }
    return res;
}

void print_bits(unsigned char x) {
    for (int j = N-1; j >= 0; --j) {
        printf("%d", ((x >> j) & 1));
    }
    printf("\n");
}

void hshift(unsigned char mat[N][N], int shift) {
    unsigned char temp_mat[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp_mat[i][j] = mat[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[i][j] = temp_mat[i][(j - shift + 8) % 8];
        }
    }
}

void vshift(unsigned char mat[N][N], int shift) {
    unsigned char temp_mat[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp_mat[i][j] = mat[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[i][j] = temp_mat[(i - shift + 8) % 8][j];
        }
    }
}

void pos_rotate(unsigned char mat[N][N]) {
    unsigned char temp_mat[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp_mat[i][j] = mat[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[j][N - 1 - i] = temp_mat[i][j];
        }
    }
}

void neg_rotate(unsigned char mat[N][N]) {
    unsigned char temp_mat[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp_mat[i][j] = mat[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[N - 1 - j][j] = temp_mat[i][j];
        }
    }
}

void print_mat(unsigned char mat[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    for (int k = 0; k < 5; ++k) {
        print_mat(mat1);
        pos_rotate(mat1);
        printf("\n");
    }

    return 0;
}