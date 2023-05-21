#ifndef __TDLIST_H__
#define __TDLIST_H__

struct list_node_t
{
    struct list_node_t *prev;
    struct list_node_t *next;
    struct page_t *data;
};
struct list_t
{
    struct list_node_t *top;
    struct list_node_t *back;
    int MaxSize;
    int Size;
    int NumberOfHit;
};

struct page_t
{
    int var;
};

void ExcludeNode(struct list_node_t *n, struct list_t *lst, int where);

/**
 * @brief add page to the list
 *
 * @param p - page
 * @param lst - list
 */
void AddPage(struct page_t *p, struct list_t *lst);

/**
 * @brief Get the Page From List object
 *
 * @param p - page
 * @param lst - list
 * @return struct list_node_t* pointer to list_node_t object wtih *data == p
 */
struct list_node_t *GetPageFromList(struct page_t *p, struct list_t *lst, int *where);

/**
 * @brief Get the Node n From List object
 *
 * @param n - node
 * @param lst - list
 * @return int 0 if n is not in lst
 * @return int -1 if n is top of the lst
 * @return int -2 if n is back of the lst
 */
int IsNodeInList(struct list_node_t *n, struct list_t *lst);

/**
 * @brief create empty two directional list
 *
 * @param maxSize - maximum number of element in the list
 * @return struct list_t* pointer to the list
 */
struct list_t *list_create(int maxSize);
/**
 * @brief release memory allocated by list_create
 *
 * @param lst - pointer to the list
 */
void list_free(struct list_t *lst);

/**
 * @brief count size of elements in the list
 *
 * @param lst - list
 * @return int - number of element in the list
 */
int list_size(const struct list_t *lst);

/**
 * @brief return the last element in the list
 *
 * @param lst - list
 * @return struct page_t* - pointer to the last element
 */
struct page_t *list_back(struct list_t *lst);

/**
 * @brief this function remove safely the last element and returns ptr to memory
 * which was already allocated, so we don't need to allocate more memory
 *
 * @param lst - list
 * @return struct list_node_t* pointer to the last element that has been removed from the list
 */
struct list_node_t *list_pop_back(struct list_t *lst);

/**
 * @brief insert(in the wide sense) page_t in the 1 position of list,
 * moving the rest of list(last el. ceases to exist)
 * it is assumed that P should normally not present in the list.
 *
 * @param lst - list
 * @param q - pointer to the page to be inserted
 */
void list_push_front(struct list_t *lst, struct page_t *q);

/**
 * @brief we move list_node_t P to the first place in lst
 * it is assumed that P should normally be in the list.
 *
 * @param lst - list
 * @param p - list_node_t to be moved
 */
void list_move_upfront(struct list_t *lst, struct list_node_t *p, int where);

/**
 * @brief print to stdout content of the list
 *
 * @param lst - list to be printed
 */
void show_list(struct list_t *lst);

#endif // __TDLIST_H__