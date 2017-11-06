//generator.c - генератор псевдослучайных чисел

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main (void)
{
    FILE *input;
    unsigned short size = 0;
    int randElement = 0;
    int min = 0, max = 0;
    char condition = 0;
    char lie = 0;

    srand (time (NULL));

    printf ("Enter ghe desired size of the array. %i < n <= %i\n", 0, USHRT_MAX);
    scanf ("%hu", &size);

    if (size == 0)
        exit (EXIT_FAILURE);

    printf ("Enter size %hu\n", size);

    printf ("Enter min and max digit. %i <= min; max <= %i\n", INT_MIN, INT_MAX - 1);
    printf ("min = ");
    scanf ("%i", &min);
    printf ("max = ");
    scanf ("%i", &max);

    if (max == INT_MAX)
        exit (EXIT_FAILURE);

    if (max - min == size - 1) {
        printf ("Do you want the numbers in the array not to be repeated? y/n\n");
        scanf ("%c", &lie);
        scanf ("%c", &condition);
    }

    if ((input = fopen ("input.txt", "w")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (input, "%hu\n", size);

    if (condition == 'y') {
        int *array = malloc (size * sizeof *array);
        unsigned short last = size;
        int temp = 0;

        for (unsigned int i = 0; i < size; ++i) {
            array [i] = min + i;
        }

        do {
            randElement = 0 + rand() % last;
            --last;
            temp = array [randElement];
            array [randElement] = array [last];
            array [last] = temp;
        } while (last != 0);

        for (unsigned int i = 0; i < size; ++i) {
            fprintf (input, "%i ", array [i]);
        }
    }
    else {
        for (unsigned int i = 0; i < size; ++i) {
            randElement = min + rand() % (max + 1);

            fprintf (input, "%i ", randElement);
        }
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    printf ("The file was created successfully.\n");

    return EXIT_SUCCESS;
}
