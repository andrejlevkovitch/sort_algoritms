//pile.c - неубывающая куча

#include <stdio.h>
#include <stdlib.h>

void heapify (int array [], int num, int lenght);
void build_heap (int array [], int lenght);

int main (void)
{
    int *pile = NULL;
    int size = 0;

    printf ("input size of array\n");
    scanf ("%i", &size);
    printf ("you input %i\n", size);

    if (size) {
        pile = malloc (size * sizeof *pile);

        printf ("input elements\n");

        for (unsigned int i = 0; i < size; ++i) {
            if (!scanf ("%i", &pile [i])) {
                printf ("missing input, try egan for element N %i\n", i + 1);
                while (getchar () != '\n')//для предотвращения ввода сообщения об ошибке
                    continue;
                --i;
            }
        }

        printf ("you array is:\n");
        for (unsigned int i = 0; i < size; ++i) {
            printf ("%i ", pile [i]);
        }
        printf ("\n\n");

        build_heap (pile, size);

        printf ("output pile is:\n");
        for (unsigned int i = 0; i < size; ++i) {
            printf ("%i ", pile [i]);
        }
        printf ("\n");
    }

    free (pile);
    pile = NULL;

    return EXIT_SUCCESS;
}

void heapify (int array [], int num, int lenght)
{
    int left = 0, right = 0;
    int largest = 0;
    int temp = 0;

    left = 2 * num + 1;//находим левого и правого потомка
    right = 2 * num + 2;
    largest = num;//устанавливаем дефолтное значение наибольшего элемента == тeкущему узлу

    if (left < lenght && array [left] > array [largest])//если потомок есть и он больше узла
        largest = left;//то меняем значение наибольшего
    if (right < lenght && array [right] > array [largest])
        largest = right;

    if (largest != num) {//если один из потомков больше родителя
        temp = array [num];//то меняем местами текущее значение узла и значение наибольшего потомка
        array [num] = array [largest];
        array [largest] = temp;

        heapify (array, largest, lenght);//рекурсия для проверки и восстановления свойств кучи после произошедшей замены
    }

    return;
}

void build_heap (int array [], int lenght)
{
    for (signed int i = (lenght - 1) / 2; i >= 0; --i) {//идем от последнего узла до корня
        heapify (array, i, lenght);//восстанавливаем свойства кучи
    }

    return;
}
