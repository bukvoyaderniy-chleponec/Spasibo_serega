#include <stdio.h>
#include <txlib.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

const int tests = 6;

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
    SS_INF_ROOTS = -1,
    ERROR_ROOT   = 999
};

enum solver_status {
    SOLVER_OK    = 1,
    SOLVER_ERROR = 0
};

enum input_status {
    INPUT_OK    = 1,
    INPUT_ERROR = 2
};

enum test_result {
    TEST_OK     = 1,
    TEST_FAILED = 0
};

const test_data data[tests] = {
    {1, 1,        0,       -4,       -2,  2, TWO_ROOTS},
    {2, 0.1,      0.2,     -0.3,     -3,  1, TWO_ROOTS},
    {3, 5,        6,        7,        0,  0, NO_ROOTS},
    {4, 1,        2,        1,       -1, -1, ONE_ROOTS},
    {5, 0.000001, 0.000002, 0.000001, 0,  0, SS_INF_ROOTS},//�������� �� ����������� �����
    {6, 0,        0,        0,        0,  0, SS_INF_ROOTS}
};
const double FRACTION = 0.001;

int RGB_test();
int clean_buffer();
void color_answer();
input_status choose();
bool compare_zero (double number);
int result (double a, double b, double c);
int input (double* a, double* b, double* c);/// good name
void print_test_succed_result (test_data data);
test_result fast_test (int counter, test_data data);
int linear_solve (double b, double c, double* x1);
void print_failed_test_result (test_data data, double x1, double x2, int nRoots);
int solve_square (double a, double b, double c, double* x1, double* x2);
int general_quadratic_equation (double a, double b, double c, double* x1, double* x2);                               // TODO: rename all

int main() {

    txSetConsoleAttr (FOREGROUND_BLACK | BACKGROUND_LIGHTBLUE);
    printf ("��� ������� ����������� ��������� ������� 1\n");

    printf ("��� �������� ������ ������� 0\n");

    choose ();
}

int solve_square (double a, double b, double c, double* x1, double* x2) {

    assert (x1 != NULL);
    assert (x2 != NULL);

    if (compare_zero (a))
        return linear_solve (b, c, x1);
    else       // TODO: func like general_quadratic_equation
        return general_quadratic_equation (a, b, c, x1, x2);

    return ERROR_ROOT;
}

int input (double* a, double* b, double* c) {

    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);

    while (scanf ("%lg %lg %lg", a, b, c) != 3) {
        clean_buffer();
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
        printf ("���������� ��� ���\n");
    }

    return INPUT_OK;
}

input_status choose() { //���� ������: ������ ���������� ������ 0???

    switch (getchar()) {

        case '0': {// TODO: make as func color_answer
            color_answer();
            break;
        }

        case '1': {
            printf ("������� CVC ��� ����� �����\n");
            printf ("��� ����\n");
            double a = 0, b = 0, c = 0;
            input (&a, &b, &c);
            if (result (a, b, c) == ERROR_ROOT) {
                printf ("����, �������� � ������!!!!");

                return INPUT_ERROR;
            }
        }

        default:
            return INPUT_ERROR;
    }

    return INPUT_ERROR;
}

test_result fast_test (int counter, test_data data) {

    double x1 = 0, x2 = 0;
    int nRoots = solve_square (data.a, data.b, data.c, &x1, &x2);

    if (nRoots != data.n_roots_test_data || !compare_zero (x1 - data.x1_test_data) || (x2 - data.x2_test_data)) {
        print_failed_test_result (data, x1, x2, nRoots);

        return TEST_FAILED;
    }
    else {

        print_test_succed_result (data);

        return TEST_OK;
    }
}

int RGB_test() {

    int counter = 0;

    for (int i = 0; i < tests; i++)
        if (fast_test (i, data[i]) == TEST_OK) {
            counter += 1;
        }

    return counter;
}

int result (double a, double b, double c) {

    double x1 = 0, x2 = 0;
    int nRoots = solve_square (a, b, c, &x1, &x2);

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

    return ERROR_ROOT;
}

bool compare_zero (double number) {

    return fabs (number) < FRACTION;

}

int clean_buffer() {

    while (getchar() != '\n') {
        continue;
    }
}

void print_failed_test_result (test_data data, double x1, double x2, int nRoots) {

    txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
    printf ("������ � ����� %d, a = %lg, b = %lg, c = %lg,"
            "��������: x1 = %lg, x2 = %lg, nRoots = %d\n"
            "���������: x1 = %lg, x2 = %lg, nRoots = %d\n",
            data.test_square, data.a, data.b, data.c,
            x1, x2, nRoots,
            data.x1_test_data, data.x2_test_data, data.n_roots_test_data);
}

void print_test_succed_result (test_data data) {

    txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
    printf ("���� %d �������\n", data.test_square);
}

int linear_solve (double b, double c, double* x1) {

    if (compare_zero (b)) {

       return (compare_zero (c)) ? SS_INF_ROOTS : NO_ROOTS;
    }
    else {
        *x1 = -c / b;

        return ONE_ROOTS;
    }
}

int general_quadratic_equation (double a, double b, double c, double* x1, double* x2) {

    double d = b * b - 4 * a * c;

    if (compare_zero (d)) {
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

        assert (!compare_zero (x1 - x2));

        return TWO_ROOTS;
    }

    return ERROR_ROOT;
}

void color_answer() {

    int counter = RGB_test();

    if (counter == 6) {
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_GREEN);
    }
    if (counter < 6) {
        txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_RED);
    }

    printf ("���������� ������ ������ %d", counter);
}

