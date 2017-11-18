//countsort.c - сортировка подсчетом

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void countSort (int array [], int size, int min, int max);

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int *array = NULL;
    int minElement = INT_MAX, maxElement = INT_MIN;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * sizeof *array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &array [i]);
        if (array [i] < minElement)
            minElement = array [i];
        else
            if (array [i] > maxElement)
                maxElement = array [i];
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    countSort (array, size, minElement, maxElement);

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

    free (array);
    array = NULL;

    return EXIT_SUCCESS;
}

void countSort (int array [], int size, int minElement, int maxElement)
{
    unsigned int *countArray = NULL;
    int *rezult = NULL;

    countArray = malloc ((maxElement + 1 - minElement) * sizeof *countArray);

    rezult = malloc (size * sizeof *rezult);

    for (unsigned int i = 0; i < maxElement + 1 - minElement; ++i) {
        countArray [i] = 0;//обнуляем все элементы, чтобы избавится от мусора
    }

    for (unsigned int i = 0; i < size; ++i) {
        countArray [array [i] - minElement] += 1;//подсчитываем сколько таких элементов в массиве
    }
    for (unsigned int i = 1; i < maxElement + 1 - minElement; ++i) {
        countArray [i] += countArray [i - 1];//подсчитываем на каком месте должны стоять элементы
    }
    for (signed int i = size - 1; i >= 0; --i) {
        countArray [array [i] - minElement] -= 1;//поскольку место отсчитывается от 1 а не от 0, сначала уменшаем индекс
        rezult [countArray [array [i] - minElement]] = array [i];//и ставим элемент на нужное место в массиве
    }

    for (unsigned int i = 0; i < size; ++i) {
        array [i] = rezult [i];
    }

    free (rezult);
    rezult = NULL;
    free (countArray);
    countArray = NULL;
}
