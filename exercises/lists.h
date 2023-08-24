#ifndef LISTS_H
#define LISTS_H

/**
 * struct dlistint_s - doubly linked list
 * @n: integer
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 * 
 */
typedef struct dlistint_s
{
    char *n;
    struct dlistint_s *prev;
    struct dlistint_s *next;
} dlistint_t;

char *_getenv(const char *name);
dlistint_t *add_dnodeint_end(dlistint_t **head, char *n);
void free_list(dlistint_t *head);
void free_node(dlistint_t *node);
size_t print_dlistint(const dlistint_t *h);

#endif
