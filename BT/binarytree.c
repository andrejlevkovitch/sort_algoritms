//binarytree.c - двоичное дерево поиска

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define nFlags 1

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
struct node *min (const struct tree *);
struct node *max (const struct tree *);
int hight (const struct node *);
void del_node (struct node *);

int main (int argc, char *argv [])
{
    if (argc > 1) {
        int kurrentFlag = 0;
        char *validFlags [nFlags] = {"-help"};

        for (kurrentFlag = 0; kurrentFlag < nFlags; ++kurrentFlag) {
            if (!strcmp (argv [1], validFlags [kurrentFlag]))
                break;
        }

        switch (kurrentFlag) {
            case 0:
                printf ("This program performs the following operations:\n");
                printf ("+ adding an element;\n");
                printf ("- removal of an element;\n");
                printf ("s element search;\n");
                printf ("a output of the minimal element;\n");
                printf ("z output of the maximal element;\n");
                printf ("h output hight of the tree;\n");
                printf ("p output of the tree.\n");
                printf ("\nIf you want to exit input cntrl+d\n");
                break;
            default:
                printf ("Flag does not exists.\n");
                break;
        }

        return EXIT_SUCCESS;
    }

    struct tree *arbo = create ();
    struct node *exm = NULL;

    int tmp = 0;
    char operace = 0;

    printf ("This program creates a binary tree of search\n");

    do {
        printf ("Please, input operace and element.\n");
        switch (operace = getchar ()) {
            case '+':
                if (scanf ("%i", &tmp)) {
                    if (insert (arbo, tmp))
                        printf ("Element %i is successfully pushed into the tree.\n", tmp);
                    else
                        printf ("Element %i was not inserted into the tree.\n", tmp);
                }
                break;
            case '-':
                if (scanf ("%i", &tmp)) {
                    if (rm (arbo, tmp))
                        printf ("Element %i was removed from the tree.\n", tmp);
                    else
                        printf ("Element %i was not removed from the tree.\n", tmp);
                }
                break;
            case 's':
                if (scanf ("%i", &tmp)) {
                    if (search (arbo, tmp))
                        printf ("Element %i already exists in the tree.\n", tmp);
                    else
                        printf ("Element %i was not searched in the tree.\n", tmp);
                }
                break;
            case 'p':
                printf ("The tree have %i elements:\n", arbo->size);
                print_tree (arbo);
                printf ("\n");
                break;
            case EOF:
                break;
            case 'a':
                exm = min (arbo);
                if (exm)
                    printf ("MinElement in the tree == %i\n", exm->info);
                else
                    printf ("MinElement was not searched in the tree.\n");
                break;
            case 'z':
                exm = max (arbo);
                if (exm)
                    printf ("MaxElement in the tree == %i\n", exm->info);
                else
                    printf ("MaxElement was not searched in the tree.\n");
                break;
            case 'h':
                printf ("Hight of the tree == %i\n", hight (arbo->root));
                break;
            default:
                printf ("Unknow operace!\n");
                break;
        }

        while (operace != '\n' && operace != EOF && getchar () != '\n')
            continue;
    } while (operace != EOF);

    del_node (arbo->root);
    free (arbo);
    arbo = NULL;
    exm = NULL;

    return EXIT_SUCCESS;
}

struct tree *create (void)
{
    struct tree *new_tree = malloc (sizeof *new_tree);//выделение памяти под структуру

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
        walk (kur_node->left);//рекурсия влево - пока не упрется в самый маленький элемент
        printf ("%i ", kur_node->info);
        walk (kur_node->right);//рекурсия вправо
    }

    return;
}

void print_tree (const struct tree *kur_tree)
{
    walk (kur_tree->root);
    return;
}

struct node *min (const struct tree *search_tree)
{
    struct node *search_node = search_tree->root;

    if (!search_node)
        return NULL;

    while (search_node->left) {
        search_node = search_node->left;
    }

    return search_node;
}

struct node *max (const struct tree *search_tree)
{
    struct node *search_node = search_tree->root;

    if (!search_node)
        return NULL;
    while (search_node->right) {
        search_node = search_node->right;
    }

    return search_node;
}

int hight (const struct node *h_node)
{
    int h1 = 0, h2 = 0;

    if (!h_node)
        return 0;
    else {
        if (h_node->left) {
            h1 = hight (h_node->left);
        }
        if (h_node->right) {
            h2 = hight (h_node->right);
        }
    }

    if (h1 > h2)
        return h1 + 1;
    else
        return h2 + 1;
}

void del_node (struct node *rm_node)
{
    if (rm_node->left)
        del_node (rm_node->left);
    if (rm_node->right)
        del_node (rm_node->right);

    rm_node->left = NULL;
    rm_node->right = NULL;
    free (rm_node);

    return;
}
