//binarytree.c - двоичное дерево поиска

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

struct node {//структура узла
    int info;//элемент, содержащийся в узле
    struct node *left;//левый (меньший) потомок
    struct node *right;//правый (больший) потомок
};

struct tree {//структура дерева
    struct node *root;//корень
    int size;//размер дерева (количество элементов)
};

struct tree *create (void);//создание дерева
bool search (const struct tree *, int);//поиск элемента
bool insert (struct tree *, int);//добавление элемента
bool rm (struct tree *, int);//удаление элемента
void walk (const struct node *);//хотьба по дереву и печать элементов начиная с входного узла
void print_tree (const struct tree *);//печать структуры

int main (void)
{
    struct tree *arbo = create ();
    struct node **out_node = &arbo->root;//ВАЖНО!!! это указатель на указатель корня! Иначе нода просто останется равной NULL

    int array [SIZE] = {5, 0, 1, 3, 2, 4, 6, 8, 7, 9};

    for (unsigned int i = 0; i < SIZE; ++i) {
        if (search (arbo, array [i]))
            printf ("this element (%i) already exists in the tree\n", array [i]);
        else
            if (insert (arbo, array [i]))
                printf ("this element (%i) is successfully pushed into the tree\n", array [i]);
            else
                printf ("this element (%i) not was pushed into the tree\n", array [i]);
    }

    printf ("%i\n", arbo->size);
    if (*out_node)
        printf ("root == %i\n", (*out_node)->info);

    walk (arbo->root);
    printf ("\n");

    if (rm (arbo, 5))
        printf ("element %i is delete saccessfully\n", 5);
    else
        printf ("element %i not was delete\n", 5);

    if (*out_node)
        printf ("root == %i\n", (*out_node)->info);

    print_tree (arbo);
    printf ("\n");

    return EXIT_SUCCESS;
}

struct tree *create (void)
{
    struct tree *new_tree = malloc (sizeof new_tree);//выделение памяти под структуру

    if (new_tree == NULL)//если что-то пошло не так
        return NULL;

    new_tree->root = NULL;//инициализация корня и текущего размера
    new_tree->size = 0;

    return new_tree;
}

bool search (const struct tree *search_tree, int element)
{
    const struct node *search_node = search_tree->root;

    for (;;) {
        if (search_node == NULL)//элемент не обнаружен
            return false;
        else
            if (search_node->info == element)//элемент обнаружен
                return true;
            else
                if (search_node->info > element)//если элемента нет в текущем узле
                    search_node = search_node->left;
                else
                    search_node = search_node->right;
    }
}

bool insert (struct tree *in_tree, int element)
{
    struct node *in_node = in_tree->root;
    struct node **new = &in_tree->root;//нужен для изменения адреса, который содержится в root

    for (;;) {
        if (!in_node) {
            in_node = *new = malloc (sizeof *in_node);//выделение памяти под новый узел

            if (in_node) {
                in_node->info = element;//присваивание значений в новом узле
                in_node->left = in_node->right = NULL;
                in_tree->size++;//размер структуры увеличивается

                return true;
            }
            else
                return false;//если что-то пошло не так
        }
        else
            if (in_node->info == element)//на случай, если проверка не была проведена
                return false;
            else
                if (in_node->info > element) {//нахождение нужного места для вставки
                    new = &in_node->left;
                    in_node = in_node->left;
                }
                else {
                    new = &in_node->right;
                    in_node = in_node->right;
                }
    }
}

bool rm (struct tree *rm_tree, int element)
{
    struct node *rm_node = rm_tree->root;
    struct node **q = &rm_tree->root;//для изменения адреса в узле

    for (;;) {//поиск удаляемого элемента
        if (!rm_node)
            return false;
        else
            if (rm_node->info == element)
                break;
            else
                if (rm_node->info > element) {
                    q = &rm_node->left;
                    rm_node = rm_node->left;
                }
                else {
                    q = &rm_node->right;
                    rm_node = rm_node->right;
                }
    }

    //удаление элемента
    if (!rm_node->right)//если правая ветка пуста
        *q = rm_node->left;
    else {
        struct node *y = rm_node->right;//подветка основной ветки
        
        if (!y->left) {//если левая подветка пуста
            y->left = rm_node->left;//то левая ветка переносится в левую подветку
            *q = y;//а узел правого потомка смещается на место родителя
        }
        else {//если левая подветка заполнена
            struct node *x = y->left;//под-подветка левой подветки

            while (x->left) {//находится самый маленький элемент
                y = x;
                x = y->left;
            }

            y->left = x->right;//подветка принимает правого (единственного) ребенка себе
            x->left = rm_node->left;//а найденный минимальный элемент становится на место удаленного
            x->right = rm_node->right;
            *q = x;
        }
    }

    rm_tree->size--;//уменьшаем размер дерева

    free (rm_node);//это значение больше нигде не используется, так что освобождаем его
    rm_node = NULL;

    return true;
}

void walk (const struct node *kur_node)
{
    if (!kur_node)
        return;
    else {
        walk (kur_node->left);
        printf ("%i ", kur_node->info);
        walk (kur_node->right);
    }

    return;
}

void print_tree (const struct tree *kur_tree)
{
    walk (kur_tree->root);
}
