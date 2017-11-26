//swap.c - сортировка перестановкой пар

#include <stdio.h>
#include <stdlib.h>

void swapSort (int array [], int size);

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

    swapSort (array, size);

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

void swapSort (int array [], int size)
{
    int temp = 0;
    int index = 0;

    for (unsigned int i = 0; i < size; ++i) {
        temp = array [i];
        index = i;//индекс элемента сравнения

        for (unsigned int j = i + 1; j < size; ++j) {
            if (temp > array [j]) {
                temp = array [j];//если текущий элемент меньшье элемента сравнения, то текущий становится элементом сравнения
                index = j;//индекс также меняется
            }

            if (i != 0 && array [i - 1] == temp)
                break;//прерывает сравнение, если найден элемент, равный предыдущему отсортированному
        }

        if (index != i) {
            array [index] = array [i];
            array [i] = temp;
        }
    }

    return;
}
