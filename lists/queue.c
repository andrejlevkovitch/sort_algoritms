//queue.c - очередь

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (void)
{
    unsigned short size = 0;
    int *queue = NULL;
    char operace = 0;
    int head = 0, tail = 0;//голова и хвост
    bool empty = true;//служит для определение пустая ли очередь

    printf ("input size\n");
    scanf ("%hu", &size);
    printf ("you input %hu\n", size);

    while (getchar () != '\n')
        continue;

    if (size)//если размер не равен нулю
        queue = malloc (size * sizeof *queue);

        do {
            printf ("input operace (and element)\n");
            switch (operace = getchar ()) {
                case '+'://добавление элемента
                    if (tail == head && !empty)
                        printf ("queue overflow\n");
                    else {
                        if (scanf ("%i", &queue [tail])) {
                            tail++;
                            if (tail == size)//зацикливание
                                tail = 0;
                            empty = false;
                        }
                        else
                            printf ("missing input\n");
                    }
                    break;
                case '-'://удаление элемента
                    if (head == tail && empty)
                        printf ("queue is empty\n");
                    else {
                        printf ("remove element %i\n", queue [head]);
                        head++;
                        if (head == size)//зацикливание
                            head = 0;
                        if (head == tail)
                            empty = true;
                    }
                    break;
                case EOF://выход из программы
                    printf ("end\n");
                    break;
                case '\n'://показать все элементы
                    if (head < tail) {//вывод
                        for (unsigned int i = head; i < tail; ++i) {
                            printf ("%i ", queue [i]);
                        }
                        printf ("\n");
                    }
                    else {
                        for (unsigned int i = head; i < size; ++i) {
                            printf ("%i ", queue [i]);
                        }
                        for (unsigned int i = 0; i < tail; ++i) {
                            printf ("%i ", queue [i]);
                        }
                        printf ("\n");
                    }
                    break;
                default:
                    printf ("unknown operace\n");
                    break;
            }
            if (operace != EOF && operace != '\n')
                while (getchar () != '\n')
                    continue;
        } while (operace != EOF);

    free (queue);
    queue = NULL;

    return EXIT_SUCCESS;
}
