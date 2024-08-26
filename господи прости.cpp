#include <stdio.h>
#include <txlib.h>
#include <math.h>
#include <assert.h>


struct test_data {
    int test_square;
    double a, b, c;
    double x1_test_data, x2_test_data;
    int n_roots_test_data;
};

enum korni {
    NO_ROOTS     = 0,
    ONE_ROOTS    = 1,
    TWO_ROOTS    = 2,
    SS_INF_ROOTS = -1
};

const double FRACTION = 0.001;
const int ERROR_SWITCH = 999;

int failed_test(test_data data, double x1, double x2, int nRoots);
int clean_buffer();
int compare_zero (double number);
int choose();
int RGB_test();
int solve_square (double a, double b, double c, double* x1, double* x2);                            // TODO: rename all
int input (double* a, double* b, double* c);/// good name
int fast_test (int counter, test_data data);
int result  (double a, double b, double c);
int linear_solve (double* a, double* b, double* c, double* x1);  // TODO: use linear_solve

int main() {

    txSetConsoleAttr (FOREGROUND_BLACK | BACKGROUND_LIGHTBLUE);
    printf ("Для решения квадратного уравнения введите 1\n");

    printf ("Для проверки тестов введите 0\n");

    choose ();
}

int solve_square (double a, double b, double c, double* x1, double* x2) {

    assert (x1 != NULL);     ////////////
    assert (x2 != NULL);

    if (compare_zero(a)) {
        if (compare_zero(b)) {

           return (compare_zero(c)) ? SS_INF_ROOTS : NO_ROOTS;
        }
        else {
            *x1 = -c / b;

            return ONE_ROOTS;
        }
    }
    else {
        double d = b * b - 4 * a * c; // TODO: func like general_quadratic_equation
        if (compare_zero(d)) {
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

            assert (!compare_zero(x1 - x2));

            return TWO_ROOTS;                           //\\//\\//\\//\\//
        }
    }
}

int input (double* a, double* b, double* c) {

    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);

    while (scanf ("%lg %lg %lg", a, b, c) != 3) {
        clean_buffer();
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
        printf ("Попробуйте ещё раз\n");
    }
}

int fast_test (int counter, test_data data) {

    double x1 = 0, x2 = 0;
    int nRoots = solve_square (data.a, data.b, data.c, &x1, &x2);
    //TODO: change operator != with doubles (x1 and x2)
    if (nRoots != data.n_roots_test_data || x1 != data.x1_test_data || x2 != data.x2_test_data) {
        failed_test(data, x1, x2, nRoots);/////
        return 0;
    }
    else {
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);// TODO: make as function
        printf ("тест %d успешен\n", data.test_square);

        return 1;
    }
}

int RGB_test() {

    const int tests = 6;
    test_data data[tests] = {
        {1, 1, 0, -4, -2, 2, TWO_ROOTS},
        {.test_square = 2, .a = 1, .b = 0, .c = -4, .x1_test_data = -2, .x2_test_data = 2, .n_roots_test_data = TWO_ROOTS},
        {3, 5, 6, 7, 0, 0, NO_ROOTS},
        {4, 1, 2, 1, -1, -1, ONE_ROOTS},
        {5, 0.000001, 0.000002, 0.000001, 0, 0, SS_INF_ROOTS},
        {6, 0, 0, 0, 0, 0, SS_INF_ROOTS}
    };
    int counter = 0;

    for (int i = 0; i < tests; i++)
        counter += fast_test (i, data[i]);

    return counter;
}

int choose () {

    switch (getchar()) {
        case '0': {
            int counter = RGB_test();
            if (counter == 6) {       // TODO: make as func color_answer
                txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
            };
            if (counter < 6) {
                txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
            };
            printf ("количество верных тестов %d", counter);
            break;
        }

        case '1': {
            printf ("\n");
            printf ("вот сюда\n");
            double a = 0, b = 0, c = 0;
            input (&a, &b, &c);
            result (a, b, c) == ERROR_SWITCH;
            break;
        }
    }

    return 0;
}

int result (double a, double b, double c) {

    double x1 = 0, x2 = 0;
    int nRoots = solve_square (a, b, c, &x1, &x2);

    switch (nRoots) {
        case NO_ROOTS:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
            printf ("Нет решений\n");
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
            printf ("ОООООООООооооочень много решений");

            return SS_INF_ROOTS;

        default:
            txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
            printf (":main(): ERROR: nRoots = %d\n",nRoots);
            break;
    }

    return ERROR_SWITCH;
}

bool compare_zero (double number) { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!switch int -> bool

    if (fabs (number) < FRACTION) {

        return 1;
    }
    else {

        return 0;
    }
}

int clean_buffer() {
    while (getchar() != '\n') {
        continue;
    }
}

int failed_test(test_data data, double x1, double x2, int nRoots) {

    txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
    printf ("Ошибка в тесте %d, a = %lg, b = %lg, c = %lg,"
            "Получили: x1 = %lg, x2 = %lg, nRoots = %d\n"
            "Ожидалось: x1 = %lg, x2 = %lg, nRoots = %d\n",
            data.test_square, data.a, data.b, data.c,
            x1, x2, nRoots,
            data.x1_test_data, data.x2_test_data, data.n_roots_test_data);
}

int linear_solve
int general_quadratic_equation
int color_answer

