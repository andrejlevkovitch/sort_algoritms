//insert.c - сортировка вставками

#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int temp = 0;
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

    for (unsigned int i = 0; i < size; ++i) {
        temp = array [i];//элементы для сравнения берутся по-порядку
        for (unsigned int j = 0; j < i; ++j) {
            if (temp < array [j]) {//если элемент сравнения меньше текущего
                for (unsigned int l = i; l > j; --l) {
                    array [l] = array [l - 1];//то выполняется смещение уже отсортированных элементов вправо
                }

                array [j] = temp;

                break;
            }
        }
    }

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
