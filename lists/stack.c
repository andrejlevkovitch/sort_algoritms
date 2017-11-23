//stack.c

#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    unsigned short size;
    int *stack = NULL;
    int top = 0;
    char operace = 0;

    printf ("input size of stack\n");
    scanf ("%hu", &size);

    printf ("you input %hu\n", size);

    stack = malloc (size * sizeof *stack);

    while (getchar () != '\n')
        continue;

    if (size)
        do {
            printf ("input operace (and element)\n");
            switch (operace = getchar ()) {
                case '+':
                    if (top == size)
                        printf ("stack overflow!\n");
                    else {
                        if (scanf ("%i", &stack [top]))
                            top++;
                        else
                            printf ("missing input\n");
                    }
                    break;
                case '-':
                    if (!top)
                        printf ("stack is empty\n");
                    else {
                        top--;
                        printf ("remove element %i\n", stack [top]);
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

    free (stack);
    stack = NULL;

    return EXIT_SUCCESS;
}
