#include "shell.h"

/**
 * list_len - decide length of linked list
 * @h: pointer
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns array of strings
 * @pntr_hd: pointer
 * Return: array
 */

char **list_to_strings(list_t *pntr_hd)
{
	list_t *node = pntr_hd;
	size_t i = list_len(pntr_hd), j;
	char **strs;
	char *str;

	if (!pntr_hd || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints elements of a list_t linked list
 * @li_ted: pointer
 * Return: size of list
 */

size_t print_list(const list_t *li_ted)
{
	size_t i = 0;

	while (li_ted)
	{
		_puts(convert_number(li_ted->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(li_ted->str ? li_ted->str : "(nil)");
		_puts("\n");
		li_ted = li_ted->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node
 * @ndd_pntr: pointer
 * @strng_pre: string
 * @c: char
 * Return: match node ! null
 */

list_t *node_starts_with(list_t *ndd_pntr, char *strng_pre, char c)
{
	char *p = NULL;

	while (ndd_pntr)
	{
		p = starts_with(ndd_pntr->str, strng_pre);
		if (p && ((c == -1) || (*p == c)))
			return (ndd_pntr);
		ndd_pntr = ndd_pntr->next;
	}
	return (NULL);
}

/**
 * get_node_index - index of node
 * @head: pointer
 * @node: pointer
 * Return: index or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
