//queue.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (void)
{
    unsigned short size = 0;
    int *queue = NULL;
    char operace = 0;
    int head = 0, tail = 0;
    bool empty = true;

    printf ("input size\n");
    scanf ("%hu", &size);
    printf ("you input %hu\n", size);

    queue = malloc (size * sizeof *queue);

    while (getchar () != '\n')
        continue;

    if (size)
        do {
            printf ("input operace (and element)\n");
            switch (operace = getchar ()) {
                case '+':
                    if (tail == head && !empty)
                        printf ("queue overflow\n");
                    else {
                        if (!scanf ("%i", &queue [tail]))
                            printf ("missing input\n");
                        else {
                            tail++;
                            if (tail == size)
                                tail = 0;
                            empty = false;
                        }
                    }
                    break;
                case '-':
                    if (head == tail && empty)
                        printf ("queue is empty\n");
                    else {
                        printf ("remove element %i\n", queue [head]);
                        head++;
                        if (head == size)
                            head = 0;
                        if (head == tail)
                            empty = true;
                    }
                    break;
                case EOF:
                    printf ("end\n");
                    break;
                default:
                    printf ("unknown operace\n");
                    break;
            }
            if (operace != EOF)
                while (getchar () != '\n')
                    continue;
        } while (operace != EOF);

    free (queue);
    queue = NULL;

    return EXIT_SUCCESS;
}
