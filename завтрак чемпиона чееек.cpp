#include <stdio.h>
#include <txlib.h>
#include <math.h>
#include <stdlib.h>

int matrica (int *massiv, size_t size_x, size_t size_y);

int main() {

    int massiv[5][4] = {
        {11, 12, 13, 14},
        {21, 22, 23, 24},
        {31, 32, 33, 34},
        {41, 42, 43, 44},
        {51, 52, 53, 54}
    };

    int size_x = 4, size_y = 5;
    matrica (massiv[0], size_x, size_y);

    sizeof (massiv)/sizeof (massiv[0]); // TODO: ”¡–¿“‹ ¡≈—œŒÀ≈«Õ”ﬁ —“–Œ◊ ”
}

int matrica (int* massiv, size_t size_x, size_t size_y) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++)
            printf ("Á‡‚Ú‡Í ˜ÂÏÔËÓÌ‡ ÌÓÏÂ [%d][%d] = %d ", i, j, *(int*)((size_t)massiv + i*size_x*4 +j*4));

        printf ("\n");
    }
}
