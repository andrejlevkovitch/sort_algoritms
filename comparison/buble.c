//buble.c - сотировка пузырьком

#include <stdio.h>
#include <stdlib.h>

void bubleSort (int array [], int size);

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

    bubleSort (array, size);

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

void bubleSort (int array [], int size)
{
    int temp = 0;

    for (unsigned int i = 1; i < size; ++i) {
        for (unsigned int j = 0; j < size - i; ++j) {
           if (array [j] > array [j + 1]) {
               temp = array [j];
               array [j] = array [j + 1];
               array [j + 1] = temp;
           }
        }
    }

    return;
}
