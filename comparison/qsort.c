//qsort.c - быстрая сортировка с выбором среднего элемента в качестве опоры

#include <stdio.h>
#include <stdlib.h>

void quick (int array [], int first, int last);

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int *array = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * sizeof *array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &array [i]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    quick (array, 0, size - 1);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < size; ++i) {
        fprintf (output, "%i ", array [i]);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void quick (int array [], int first, int last)
{
    int left = first;
    int right = last;
    int midle = array [(left + right) / 2];
    int temp = 0;

    while (left <= right) {
        while (array [left] < midle) {
            ++left;
        }
        while (array [right] > midle) {
            --right;
        }

        if (left <= right) {//если обнаружен элементы не соответствующие условиям
            temp = array [left];
            array [left] = array [right];
            array [right] = temp;//они переставляются
            ++left;
            --right;
        }
    }

    if (first < right) {//рекурсия
        quick (array, first, right);
    }

    if (last > left) {
        quick (array, left, last);
    }
}
