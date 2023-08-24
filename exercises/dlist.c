#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

/**
 * add_dnodeint_end - check the code
 * @head: pointer addr of head of list
 * @n: value to add
 *
 * Return: pointer to new node.
 */
dlistint_t *add_dnodeint_end(dlistint_t **head, char *n)
{
	dlistint_t *node;
	dlistint_t *tail;

	node = malloc(sizeof(dlistint_t));
	if (node == NULL)
	{
		free(node);
		free_list(*head);
		exit(98);
	}

	node->n = n;

	if (*head == NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		*head = node;
	}
	else
	{
		tail = *head;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = node;
		node->prev = tail;
		node->next = NULL;
	}

	return (node);
}

/**
 * print_dlistint - check the code
 * @h: head of the list
 *
 * Return: num of elements.
 */
size_t print_dlistint(const dlistint_t *h)
{
	size_t i = 0;
	const dlistint_t *curr;

	if (h != NULL)
	{
		curr = h;
		while (curr != NULL)
		{
			printf("%s\n", curr->n);
			curr = curr->next;
			i = i + 1;
		}
	}

	return (i);
}

/**
 * free_list - check the code
 * @head: head of the list
 *
 * Return: nothing.
 */
void free_list(dlistint_t *head)
{
	dlistint_t *node;

	if (head != NULL)
	{
		node = head;
		if (node != NULL && node->next != NULL)
		{
			free_node(node->next);
		}
		free(head);
	}
}

/**
 * free_node - frees mem usage by the node
 * @node: node to free up
 *
 * Return: nothing.
 */
void free_node(dlistint_t *node)
{
	if (node->next != NULL)
	{
		free_node(node->next);
	}
	free(node);
}
