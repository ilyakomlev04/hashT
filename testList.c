#include "TDList.h"
#include <stdio.h>
int GetNumberOfHit(int m, int n, struct page_t P[])
{
    struct list_t *lst = list_create(m);
    int i = 0;
    while (i < n)
    {
        AddPage(&(P[i]), lst);
        i++;
    }

    show_list(lst);
    m = lst->NumberOfHit;
    list_free(lst);

    return m;
}
int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int PI[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &PI[i]);
    int i = 0;
    struct page_t P[n];
    while (i < n)
    {

        P[i].var = PI[i];
        i++;
    }
    printf("%d", GetNumberOfHit(m, n, P));

    return 0;
    // return 0;
}
