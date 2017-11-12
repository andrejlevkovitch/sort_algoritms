//radix.c - цифровая сортировка (LSD, в качестве устойчивой используется сортировка подсчетом) для сортировки массива чисел по байтам

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 256//размер максимального числа для байта

void countSort (int array [], int size, int maxElement);

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int *array = NULL;
    int maxElement = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * sizeof *array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &array [i]);
        if (array [i] > maxElement)
            maxElement = array [i];
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    countSort (array, size, maxElement);

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

void countSort (int array [], int size, int maxElement)
{
    int countArray [LENGTH] = {};
    unsigned char *temp = NULL;
    int *rezult = NULL;

    rezult = malloc (size * sizeof *rezult);

    for (unsigned int l = 0; l < sizeof *array; ++l) {//от 0 до 3 если int; по-байтам идут сначала младшие, затем старшие разряды
        for (unsigned int i = 0; i < LENGTH; ++i) {
            countArray [i] = 0;
        }
        for (unsigned int i = 0; i < size; ++i) {
            temp = (long) &array [i] + (long) l;//(long) нужен для расчета адреса байта, иначе прибавляется 4 а не 1
            countArray [*temp] += 1;
        }
        for (unsigned int i = 1; i < LENGTH; ++i) {
            countArray [i] += countArray [i - 1];
        }
        for (signed int i = size - 1; i >= 0; --i) {
            temp = (long) &array [i] + (long) l;
            countArray [*temp] -= 1;
            rezult [countArray [*temp]] = array [i];
        }
        for (unsigned int i = 0; i < size; ++i) {
            array [i] = rezult [i];
        }
    }

    free (rezult);
    rezult = NULL;
}
