#include <avr/io.h>

#define F_CPU 1000000
#include <util/delay.h>

#define N 8

int shift_status = 0;

// unsigned char mat1[N][N] = {
// //  0  1  2  3  4  5  6  7
//     {1, 0, 0, 0, 0, 0, 0, 1}, // 0
//     {0, 1, 0, 0, 0, 0, 1, 0}, // 1
//     {0, 0, 1, 0, 0, 1, 0, 0}, // 2
//     {0, 0, 0, 1, 1, 0, 0, 0}, // 3
//     {0, 0, 0, 1, 1, 0, 0, 0}, // 4
//     {0, 0, 1, 0, 0, 1, 0, 0}, // 5
//     {0, 1, 0, 0, 0, 0, 1, 0}, // 6
//     {1, 0, 0, 0, 0, 0, 0, 1}  // 7
// };

unsigned char mat1[N][N] = {
//  0  1  2  3  4  5  6  7
    {0, 0, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 0, 1, 1, 0, 1, 0}, // 1
    {1, 0, 0, 1, 1, 0, 0, 1}, // 2
    {1, 0, 1, 1, 1, 1, 0, 1}, // 3
    {1, 1, 0, 1, 1, 0, 1, 1}, // 4
    {1, 0, 0, 1, 1, 0, 0, 1}, // 5
    {0, 1, 0, 1, 1, 0, 1, 0}, // 6
    {0, 0, 1, 1, 1, 1, 0, 0}  // 7
};

unsigned char get_row(unsigned char* row) {
    unsigned char res = 0;
    for (int j = 0; j < N; ++j) {
        res |= (row[j] << j);
    }
    return res;
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
            mat[N - 1 - j][i] = temp_mat[i][j];
        }
    }
}

void render(unsigned char mat[N][N], int frame_count) {
    while (frame_count--) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 5; ++j) {
                PORTA = (1 << i);
                PORTD = ~get_row(mat[i]);
            }
            _delay_ms(2.5);
        }
    }
}

int main(void) {
    DDRA = 0xFF;
	DDRD = 0xFF;
	DDRB = 0xFE;
	
    while (1) {
        unsigned char in = (PINB & 0x01);
        if (in) {
            shift_status = !shift_status;
            render(mat1, 15);
        }
        if (shift_status) {
            hshift(mat1,-1);
        }
        render(mat1, 1);
    }
}

