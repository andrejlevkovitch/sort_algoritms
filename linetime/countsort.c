//countsort.c - сортировка подсчетом (без отрицательных чисел и если размер = последнему элементу)

#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int max = 0;
    int *array = NULL;
    int *rezult = NULL;
    int *countArray = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    max = size;//если max = size!!! первый элемент = 1

    array = malloc (size * sizeof *array);
    rezult = malloc (size * sizeof *rezult);
    countArray = malloc ((max + 1) * sizeof *countArray);

    for (unsigned int i = 0; i < max + 1; ++i) {
        countArray [i] = 0;//обнуляем все элементы, чтобы избавится от мусора
    }

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &array [i]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < size; ++i) {
        countArray [array [i]] += 1;//подсчитываем сколько таких элементов в массиве
    }
    for (unsigned int i = 1; i < max + 1; ++i) {
        countArray [i] += countArray [i - 1];//подсчитываем на каком месте должны стоять элементы
    }
    for (signed int i = size - 1; i >= 0; --i) {
        countArray [array [i]] -= 1;//поскольку место отсчитывается от 1 а не от 0, сначала уменшаем индекс
        rezult [countArray [array [i]]] = array [i];//и ставим элемент на нужное место в массиве
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < size; ++i) {
        fprintf (output, "%i ", rezult [i]);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
