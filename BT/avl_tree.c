//avl_tree.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 32
#define nFlags 1
#define MIN 0
#define MAX 1

struct node {
    struct node *child [2];
    int info;
    short balance;
};

struct tree {
    struct node *root;
    int size;
};

struct tree *init_tree (void);
struct node *new_node (struct tree *, int);
struct node *search (struct tree*, const int);
void turn (struct node **);
struct node *insert (struct tree *, int);
struct node *del (struct node *);
struct tree *del_tree (struct tree *);
int rm (struct tree *, int);
void print_tree (struct tree*);
void walk (struct node *);
struct node *minORmax (const struct tree *, int);
int hight (const struct node *);

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
                printf ("a adding an element;\n");
                printf ("r removal of an element;\n");
                printf ("s element search;\n");
                printf ("n output of the minimal element;\n");
                printf ("x output of the maximal element;\n");
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

    struct tree *avl = init_tree ();
    if (!avl) {
        printf ("Error of memory\n");
        exit (EXIT_FAILURE);
    }

    struct node *exm = NULL;

    int tmp = 0;
    char operace = 0;

    printf ("This program creates a avl tree of search\n");

    do {
        printf ("Please, input operace and element.\n");
        switch (operace = getchar ()) {
            case 'a':
                if (scanf ("%i", &tmp)) {
                    if (insert (avl, tmp))
                        printf ("Element %i is successfully pushed into the tree.\n", tmp);
                    else
                        printf ("Element %i was not inserted into the tree.\n", tmp);
                }
                break;
            case 'r':
                if (scanf ("%i", &tmp)) {
                    if (rm (avl, tmp))
                        printf ("Element %i was not removed from the tree.\n", tmp);
                    else
                        printf ("Element %i was removed from the tree.\n", tmp);
                }
                break;
            case 's':
                if (scanf ("%i", &tmp)) {
                    if (search (avl, tmp))
                        printf ("Element %i already exists in the tree.\n", tmp);
                    else
                        printf ("Element %i was not searched in the tree.\n", tmp);
                }
                break;
            case 'p':
                printf ("The tree have %i elements:\n", avl->size);
                print_tree (avl);
                printf ("\n");
                break;
            case EOF:
                break;
            case 'n':
                exm = minORmax (avl, MIN);
                if (exm)
                    printf ("MinElement in the tree == %i\n", exm->info);
                else
                    printf ("MinElement was not searched in the tree.\n");
                break;
            case 'x':
                exm = minORmax (avl, MAX);
                if (exm)
                    printf ("MaxElement in the tree == %i\n", exm->info);
                else
                    printf ("MaxElement was not searched in the tree.\n");
                break;
            case 'h':
                printf ("Hight of the tree == %i\n", hight (avl->root));
                break;
            default:
                printf ("Unknow operace!\n");
                break;
        }

        while (operace != '\n' && operace != EOF && getchar () != '\n')
            continue;
    } while (operace != EOF);

    avl = del_tree (avl);
    exm = NULL;

    return EXIT_SUCCESS;
}

void print_tree (struct tree *pTree)
{
    if (pTree->root)
        walk (pTree->root);

    return;
}
void walk (struct node *pNode)
{
    if (pNode->child [0])
        walk (pNode->child [0]);

    printf ("(%i b%i)", pNode->info, pNode->balance);

    if (pNode->child [1])
        walk (pNode->child [1]);

    return;
}

struct tree *init_tree (void)
{
    struct tree *tree = malloc (sizeof *tree);
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

struct node *new_node (struct tree *n_tree, int item)
{
    struct node *new = malloc (sizeof *new);
    if (new) {
        new->child [0] = new->child [1] = NULL;
        new->info = item;
        new->balance = 0;
        n_tree->size++;
    }

    return new;
}

struct node *insert (struct tree *in_tree, int element)
{
    struct node *in_node = in_tree->root;
    struct node **new = &in_tree->root;

    struct node **array [MAX_H] = {};//массив хранящий указатели на все пройденные ноды
    short dirs [MAX_H] = {};//массив хранящий направления движения
    short count = 0;

    for (;;) {
        if (!in_node) {
            in_node = *new = new_node (in_tree, element);
            break;
        }
        else
            if (in_node->info == element)
                return NULL;
            else {
                array [count] = new;
                dirs [count] = element > in_node->info;
                new = &in_node->child [dirs [count]];
                in_node = in_node->child [dirs [count]];
                count++;
            }
    }

    if (in_node && count) {//когда произошла вставка происходит балансировка
        for (int i = count - 1; i >= 0; --i) {
            if ((*array [i])->balance) {//если баланс не равен нулю
                (*array [i])->balance = (dirs [i]) ? (*array [i])->balance - 1 : (*array [i])->balance + 1;//происходит изменение баланса в зависимости от направления
                if (abs ((*array [i])->balance) == 2)//выполняется поворот если надо
                    turn (array [i]);
                if (!(*array [i])->balance)//если баланс оказался равен 0, то дальнейшие корректировки не нужны
                    break;
            }
            else//если баланс узла был равен 0, то он изменяется в зависимости от направления
                (*array [i])->balance = (dirs [i]) ? -1 : 1;
        }
    }

    return in_node;
}

int rm (struct tree *rm_tree, int element)
{
    struct node *rm_node = rm_tree->root;
    struct node **q = &rm_tree->root;

    struct node **array [MAX_H] = {};//тоже что и во вставке
    short dirs [MAX_H] = {};
    short count = 0;

    for (;;) {
        if (!rm_node)
            return 1;
        else
            if (rm_node->info == element)
                break;
            else {
                array [count] = q;
                dirs [count] = element > rm_node->info;
                q = &rm_node->child [dirs [count]];
                rm_node = rm_node->child [dirs [count]];
                count++;
            }
    }

    if (!rm_node->child [0]) {
        *q = rm_node->child [1];
    }
    else {
        struct node *y = rm_node->child [0];
        
        dirs [count] = 0;//в этом случае создание массива продолжается
        array [count] = q;//в массив вводится указатель на удаляемую ноду, которая будет заменена другой
        count++;

        if (!y->child [1]) {
            y->child [1] = rm_node->child [1];

            y->balance = rm_node->balance;//удаляемая нода изменяется, но баланс остается
            *q = y;
        }
        else {
            struct node *x = y->child [1];
            short px = 0;
            px = count;
            dirs [count] = 1;//дополнение в массив указателей происходит ниже
            count++;

            while (x->child [1]) {
                dirs [count] = 1;
                array [count] = &y->child [1];
                count++;

                y = x;
                x = x->child [1];
            }

            y->child [1] = x->child [0];
            x->child [0] = rm_node->child [0];
            x->child [1] = rm_node->child [1];

            array [px] = &x->child [0];//вот оно, так как именно эта нода заменяет собой удаляемую

            x->balance = rm_node->balance;

            *q = x;
        }
    }

    for (int i = count - 1; i >= 0; --i) {//опять балансировка
        if ((*array [i])->balance) {
            (*array [i])->balance = (dirs [i]) ? (*array [i])->balance + 1 : (*array [i])->balance - 1;
            if (abs ((*array [i])->balance) == 2)
                turn (array [i]);
        }
        else
            (*array [i])->balance = (dirs [i]) ? 1 : -1;

        if ((*array [i])->balance)
            break;
    }

    rm_tree->size--;

    free (rm_node);
    rm_node = NULL;

    return 0;
}

struct node *search (struct tree *sTree, const int value)
{
    struct node *sNode = sTree->root;
    if (!sNode)
        return NULL;
    while (value != sNode->info) {
        sNode = sNode->child [value > sNode->info];

        if (!sNode)
            break;
    }

    return sNode;
}

struct tree *del_tree (struct tree *rTree)
{
    rTree->root = (rTree->root) ? del (rTree->root) : NULL;

    rTree->size = 0;
    free (rTree);

    return NULL;
}

struct node *del (struct node *rNode)
{
    for (int i = 0; i < 2; ++i) {
        rNode->child [i] = (rNode->child [i]) ? del (rNode->child [i]) : NULL;
    }

    free (rNode);

    return NULL;
}

void turn (struct node **tNode)
{
    struct node *B = NULL;//балансируемый узел
    struct node *A = NULL;//ребенок балансируемого узла
    struct node *C = NULL;//ребенок узла А
    struct node *beta = NULL;//подветка узла С
    struct node *hama = NULL;//подветка узла С или А

    B = *tNode;

    short dir = (B->balance < 0);//направление
    short mod = (dir) ? 1: -1;//модификатор, зависящий от направления

    switch (B->child [dir]->balance * mod) {//операции поворота одни и теже, но происходят зеркально, взависимости от направления
        case -1: case 0:
            A = B->child [dir];
            hama = A->child [!dir];
            A->child [!dir] = B;
            B->child [dir] = hama;
            *tNode = A;

            switch (A->balance * mod) {
                case -1:
                    B->balance = 0;
                    A->balance = 0;
                    break;
                case 0:
                    B->balance = -1 * mod;
                    A->balance = 1 * mod;
                    break;
            }
            break;
        case 1:
            A = B->child [dir];
            C = A->child [!dir];
            beta = C->child [!dir];
            hama = C->child [dir];
            C->child [dir]= A;
            C->child [!dir]= B;
            A->child [!dir]= hama;
            B->child [dir]= beta;
            *tNode = C;

            switch (C->balance * mod) {
                case -1:
                    B->balance = 1 * mod;
                    A->balance = 0;
                    C->balance = 0;
                    break;
                case 0:
                    B->balance = 0;
                    A->balance = 0;
                    C->balance = 0;
                    break;
                case 1:
                    B->balance = 0;
                    A->balance = -1 * mod;
                    C->balance = 0;
                    break;
            }
            break;
        default:
            break;
    }

    return;
}

struct node *minORmax(const struct tree *search_tree, int dir)
{
    struct node *search_node = search_tree->root;

    if (!search_node)
        return NULL;

    while (search_node->child [dir]) {
        search_node = search_node->child [dir];
    }

    return search_node;
}

int hight (const struct node *h_node)
{
    short h1 = 0, h2 = 0;

    if (!h_node)
        return 0;
    else {
        if (h_node->child [0]) {
            h1 = hight (h_node->child [0]);
        }
        if (h_node->child [1]) {
            h2 = hight (h_node->child [1]);
        }
    }

    if (h1 > h2)
        return h1 + 1;
    else
        return h2 + 1;
}
