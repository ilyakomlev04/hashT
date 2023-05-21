#include "TDList.h"
#include <stdlib.h>
#include <stdio.h>

void ExcludeNode(struct list_node_t *n, struct list_t *lst, int where)
{
    // int where = IsNodeInList(n, lst);
    if (where == 0)
        return;
    if (where == -1)
    {
        // lst->Size--;
        if (lst->Size == 1)
        {
            // top
            lst->top = NULL;
            // back
            lst->back = NULL;
        }
        else if (lst->Size == 2)
        {
            lst->top = lst->back;
            lst->top->prev = NULL;
        }
        else if (lst->Size > 2)
        {
            struct list_node_t *topnew = lst->top->next;
            topnew->prev = NULL;
            lst->top = topnew;
        }
        lst->Size--;
    }
    else if (where == -2)
    {
        list_pop_back(lst);
    }
    else
    {
        struct list_node_t *pr = n->prev;
        struct list_node_t *nxt = n->next;
        pr->next = nxt;
        nxt->prev = pr;
        lst->Size--;
    }

    return;
}

void AddPage(struct page_t *p, struct list_t *lst)
{
    if (p == NULL || lst == NULL)
    {
        printf("Give page and list");
        exit(1);
    }
    printf("Page %d \n", p->var);
    int where;
    struct list_node_t *n = GetPageFromList(p, lst, &where);
    if (n == NULL)
    {
        // new node
        list_push_front(lst, p);
        printf("After push_front \n");
        show_list(lst);
    }
    else
    {
        // int where = IsNodeInList(p, lst);
        list_move_upfront(lst, n, where);
        printf("After move_upfront \n");
        show_list(lst);
    }
}

struct list_t *list_create(int maxSize)
{
    struct list_t *res = malloc(sizeof(struct list_t));
    res->top = NULL;
    res->back = NULL;
    res->MaxSize = maxSize;
    res->NumberOfHit = 0;
    res->Size = 0;
    return res;
}

int list_size(const struct list_t *lst)
{
    // int i = 0;
    // struct list_node_t *cr = lst->top;
    // while (cr != NULL)
    // {
    //     cr = cr->next;
    //     i++;
    // }
    // return i;
    return lst->Size;
}

struct page_t *list_back(struct list_t *lst)
{
    return ((lst->back)->data);
}

struct list_node_t *list_pop_back(struct list_t *lst)
{
    struct list_node_t *oldBack = lst->back;

    if (lst->Size == 1)
    {
        // top
        lst->top = NULL;
        // back
        lst->back = NULL;
        lst->Size = 0;
    }
    else if (lst->Size == 2)
    {
        lst->Size--;
        lst->back = lst->top;
        lst->back->next = NULL;
    }
    else if (lst->Size > 2)
    {
        lst->Size--;
        struct list_node_t *backnew = lst->back->prev;
        backnew->next = NULL;
        lst->back = backnew;
    }

    return oldBack;
}

void list_push_front(struct list_t *lst, struct page_t *q)
{
    struct list_node_t *pToNewListNode;
    int curentSize = lst->Size;
    if (lst->MaxSize > curentSize) // list is not fully occupied. simply place q on the front
    {
        // allocate memory
        pToNewListNode = malloc(sizeof(struct list_node_t));
    }
    else
    {
        // remove last element
        pToNewListNode = list_pop_back(lst);
    }
    // It is necessary to update curentSize because  list_pop_back may change lst
    // !!!!!!!!!!!! it was the error
    curentSize = lst->Size;
    if (curentSize == 0)
    {
        // top
        pToNewListNode->prev = NULL;
        pToNewListNode->next = NULL;
        pToNewListNode->data = q;
        lst->top = pToNewListNode;
        // back
        lst->back = lst->top;
        lst->Size++;
    }
    else if (curentSize > 0)
    {
        // top
        pToNewListNode->prev = NULL;
        pToNewListNode->next = lst->top;
        pToNewListNode->data = q;
        lst->top->prev = pToNewListNode;
        lst->top = pToNewListNode;
        // back
        lst->Size++;
    }
}

struct list_node_t *GetPageFromList(struct page_t *p, struct list_t *lst, int *where)
{
    if (lst->Size < 1)
        return NULL;
    struct list_node_t *result = lst->top;
    while (result != NULL)
    {
        if (result->data->var == p->var)
        {
            if (result == lst->top)
            {
                *where = -1;
            }
            else if (result == lst->back)
            {
                *where = -2;
            }
            else
            {
                *where = 1;
            }
            return result;
        }

        result = result->next;
    }
    return NULL;
}

int IsNodeInList(struct list_node_t *n, struct list_t *lst)
{
    if (list_size(lst) < 1)
        return 0;
    struct list_node_t *r = lst->top;
    while (r != NULL)
    {
        if (r == n)
        {
            if (n == lst->top)
            {
                return -1;
            }
            else if (n == lst->back)
            {
                return -2;
            }
            else
            {
                return 1;
            }
        }
        r = r->next;
    }
    return 0;
}

void list_move_upfront(struct list_t *lst, struct list_node_t *p, int where)
{
    // int where = IsNodeInList(p, lst);
    if (where == 0)
    {
        printf("\n Node is not in the list");
        exit(1);
    }
    lst->NumberOfHit++;
    if (where == -1)
    {
        return;
    }
    printf("Before Exclude \n");
    show_list(lst);

    ExcludeNode(p, lst, where);
    printf("After Exclude \n");
    show_list(lst);

    p->prev = NULL;
    p->next = lst->top;
    lst->top->prev = p;
    lst->top = p;
    lst->Size++;
}

void list_free(struct list_t *lst)
{
    struct list_node_t *cr = lst->top;
    while ((cr) != NULL)
    {
        struct list_node_t *crn = cr->next;
        free(cr);
        cr = crn;
    }
    free(lst);
}

// for tests
void show_list(struct list_t *lst)
{
    printf("List Size %d \n", lst->Size);

    struct list_node_t *cr = lst->top;
    while (cr != NULL)
    {
        printf("%d ", ((*(cr->data)).var));
        cr = cr->next;
    }
    printf("\n");
}
