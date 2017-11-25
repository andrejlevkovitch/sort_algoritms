//stack.c - стэк

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

    while (getchar () != '\n')
        continue;

    if (size)
        stack = malloc (size * sizeof *stack);

        do {
            printf ("input operace (and element)\n");
            switch (operace = getchar ()) {
                case '+'://добавление элемента
                    if (top == size)
                        printf ("stack overflow!\n");
                    else {
                        if (scanf ("%i", &stack [top]))
                            top++;
                        else
                            printf ("missing input\n");
                    }
                    break;
                case '-'://удаление элемента
                    if (!top)
                        printf ("stack is empty\n");
                    else {
                        top--;
                        printf ("remove element %i\n", stack [top]);
                    }
                    break;
                case EOF://выход из программы
                    printf ("end\n");
                    break;
                case '\n'://вывод стэка
                    for (unsigned int i = 0; i < top; ++i) {
                        printf ("%i ", stack [i]);
                    }
                    printf ("\n");
                    break;
                default:
                    printf ("unknown operace\n");
                    break;
            }
            if (operace != EOF && operace != '\n')
                while (getchar () != '\n')
                    continue;
        } while (operace != EOF);

    free (stack);
    stack = NULL;

    return EXIT_SUCCESS;
}
