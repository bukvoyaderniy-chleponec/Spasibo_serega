#include <stdio.h>
#include <txlib.h>
#include <math.h>
#include <assert.h>


struct Pekusi {// TODO: rename all
    int n1test;// TODO: rename all
    double a, b, c;
    double x1banal, x2banal;// TODO: rename all
    int nRootsbanal;
};

enum Korni {
    NO_ROOTS     = 0,
    ONE_ROOTS    = 1,
    TWO_ROOTS    = 2,
    SS_INF_ROOTS = -1
};

const double poltarachka_v_edinichke = 0.001;// TODO: rename all

int choose (double* a, double* b, double* c);
int RGB_test();
int SolveSquare (double a, double b, double c, double* x1, double* x2);// TODO: rename all
int input (double* a, double* b, double* c);// good name
int RTRTRTRTRTRTRTRTRT (int counter, Pekusi data);   // TODO: rename all
int switch_case  (double a, double b, double c); // TODO: rename all
int linear_solve (double* a, double* b, double* c, double* x1);

int main() {
    txSetConsoleAttr (FOREGROUND_BLACK | BACKGROUND_LIGHTBLUE);
    printf ("��� ������� ����������� ��������� ������� 1\n");

    printf ("��� �������� ������ ������� 0\n");

    printf ("��� ���������� ��������� ������� +\n");

    choose (&a, &b, &c);
}

int SolveSquare (double a, double b, double c, double* x1, double* x2) {

    assert (x1 != NULL);
    assert (x2 != NULL);

    if (fabs (a) < poltarachka_v_edinichke) {    // TODO: func to compare double and 0
        if (fabs (b) < poltarachka_v_edinichke) {
           return (fabs (c) < poltarachka_v_edinichke) ? SS_INF_ROOTS : NO_ROOTS;
        }
        else {
            *x1 = -c / b;
            return ONE_ROOTS;
        }
    }
    else {
        double d = b * b - 4 * a * c;
        if (fabs (d) < poltarachka_v_edinichke) {
            *x1 = *x2 = -b / (2 * a);
            return ONE_ROOTS;
        }
        if (d < 0) {
            return NO_ROOTS;
        }
        else {
            double sqrt_d = sqrt (d);

            *x1 = (-b - sqrt_d) / (2 * a);
            *x2 = (-b + sqrt_d) / (2 * a);

            assert (fabs (x1 - x2) > poltarachka_v_edinichke); // TODO: try to make less complicated

            return TWO_ROOTS;
        }
    }
}

int input (double* a, double* b, double* c) {

    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);

    while (scanf ("%lg %lg %lg", a, b, c) != 3) {
        while (getchar() != '\n') {
            continue;
        }
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
        printf ("���������� ��� ���");
    }
}

int RTRTRTRTRTRTRTRTRT (int counter, Pekusi data) {

    double x1 = 0, x2 = 0;
    int nRoots = SolveSquare (data.a, data.b, data.c, &x1, &x2);

    if (nRoots != data.nRootsbanal || x1 != data.x1banal || x2 != data.x2banal) {
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
        printf ("Error test %d, a = %lg, b = %lg, c = %lg,"
               "��������: x1 = %lg, x2 = %lg, nRoots = %d\n"
               "���������: x1 = %lg, x2 = %lg, nRoots = %d\n",
                data.n1test, data.a, data.b, data.c,
                x1, x2, nRoots,
                data.x1banal, data.x2banal, data.nRootsbanal);
        return 0;
    }
    else {
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
        printf ("test %d succeed\n", data.n1test);
        return 1;
    }
}

int RGB_test() {
    const int tests = 6;
    Pekusi data[tests] = {
    {1, 1, 0, -4, -2, 2, TWO_ROOTS},
    {.n1test = 2, .a = 1, .b = 0, .c = -4, .x1banal = -2, .x2banal = 2, .nRootsbanal = TWO_ROOTS},
    {3, 5, 6, 7, 0, 0, NO_ROOTS},
    {4, 1, 2, 1, -1, -1, ONE_ROOTS},
    {5, 0.000001, 0.000002, 0.000001, 0, 0, SS_INF_ROOTS},
    {6, 0, 0, 0, 0, 0, SS_INF_ROOTS}
    };
    int counter = 0;
    for (int i = 0; i < tests; i++)
        counter += RTRTRTRTRTRTRTRTRT (i, data[i]);  //////////////////////
    return counter;
}

int choose (double* a, double* b, double* c) {  // TODO: remove a, b, c
    char ch = getchar();
    switch (ch) {
        case '0': {
            int counter = RGB_test();
            if (counter == 6) {
                txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
            };
            if (counter < 6) {
                txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
            };
            printf ("���������� ������ ������ %d", counter);
        }
        break;

        case '1':
            printf ("\n");
            printf ("��� ����\n");
            double a = 0, b = 0, c = 0;
            input (&a, &b, &c);
            switch_case (a,b,c);// TODO: rename all
            break;
    }
    return 0;
}

int switch_case (double a, double b, double c) {// TODO: rename all

    double x1 = 0, x2 = 0;

    int nRoots = SolveSquare (a, b, c, &x1, &x2);
    switch (nRoots) {
        case NO_ROOTS:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
            printf ("��� �������\n");
            return NO_ROOTS;

        case ONE_ROOTS:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
            printf ("x = %lg\n", x1);
            return ONE_ROOTS;

        case TWO_ROOTS:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
            printf ("x1 = %lg, x2 = %lg\n", x1, x2);
            return TWO_ROOTS;;

        case SS_INF_ROOTS:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
            printf ("������������������ ����� �������");
            return SS_INF_ROOTS;

        default:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
            printf (":main(): ERROR: nRoots = %d\n",nRoots);
            break;
    }
}
