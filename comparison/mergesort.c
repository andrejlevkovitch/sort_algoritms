//mergesort.c - сортировка слиянием

#include <stdio.h>
#include <stdlib.h>

void merge (int array [], int first, int last);
void msort (int array [], int first, int midle, int last);

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

    merge (array, 0, size - 1);//вызов рекурсии

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

void merge (int array [], int first, int last)//рекурсия
{
    int midle = 0;

    if (first < last) {
        midle = first + (last - first) / 2;

        merge (array, first, midle);
        merge (array, midle + 1, last);

        msort (array, first, midle, last);//впервые вызывается, когда рекурсия достигла размера 1 элемента
    }

    return;
}

void msort (int array [], int first, int midle, int last)//сортировка
{
    int *arL = NULL;
    int *arR = NULL;//два массива, левый и правый

    int counterL = 0, counterR = 0;//счетчики индексов массивов левого и правого

    int num = first;//счетчик индексов основного массива

    int n1 = midle - first + 1;
    int n2 = last - midle;//размеры левого и правого массивов

    arL = malloc (n1 * sizeof *arL);
    arR = malloc (n2 * sizeof *arR);

    for (unsigned int i = 0; i < n1; ++i) {
        arL [i] = array [first + i];
    }
    for (unsigned int i = 0; i < n2; ++i) {
        arR [i] = array [midle + 1 + i];
    }

    while (counterL < n1 && counterR < n2) {//пока не закончился один из массивов
        if (arL [counterL] > arR [counterR]) {
            array [num] = arR [counterR];
            ++counterR;
        }
        else {
            array [num] = arL [counterL];
            ++counterL;
        }

        ++num;
    }

    if (counterL == n1) {//когда один из массивов закончился, то оставшиеся элементы второго массива добавляются без проверки
        for (unsigned int i = 0; i < n2 - counterR; ++i) {
            array [num + i] = arR [i + counterR];
        }
    }
    else {
        for (unsigned int i = 0; i < n1 - counterL; ++i) {
            array [num + i] = arL [i + counterL];
        }
    }

    free (arL);
    arL = NULL;
    free (arR);
    arR = NULL;

    return;
}
