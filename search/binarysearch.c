//binarysearch.c - двоичный поиск в массиве отсортированном по возрастанию

#include <stdio.h>
#include <stdlib.h>

int binary (int array [], int size, int digit);

int main (void)
{
    FILE *input;
    int size = 0;
    int *array = NULL;
    int digit = 0;

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

    printf ("what number you want to find?\n");
    scanf ("%i", &digit);

    printf ("this number have koord: %i\n", binary (array, size, digit));

    free (array);
    array = NULL;

    return EXIT_SUCCESS;
}

int binary (int array [], int size, int digit)
{
    int left = 0;
    int right = size;
    int midle = 0;

    if (size == 0) {
        return EOF;
    }
    else
        if (array [0] > digit) {
            return EOF;
        }
        else
            if (array [size - 1] < digit) {
                return EOF;
            }

    while (left < right) {
        midle = left + (right - left) / 2;

        if (digit <= array [midle])
            right = midle;
        else
            left = midle + 1;
    }

    if (array [right] == digit)
        return right;
    else
        return EOF;
}
