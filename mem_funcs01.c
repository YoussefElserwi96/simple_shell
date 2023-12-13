#include "shell.h"

/**
 **_memset - byte to memory
 *@s: pointer to mem
 *@b: the byte to fill
 *@n: bytes to be filled
 *Return: pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees s of sts
 * @pp: st of sts
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr_pr_mlc: pointer
 * @o_size: byte previous block
 * @n_size: byte new block
 * Return: pointer
 */

void *_realloc(void *ptr_pr_mlc, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!ptr_pr_mlc)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr_pr_mlc), NULL);
	if (n_size == o_size)
		return (ptr_pr_mlc);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)ptr_pr_mlc)[o_size];
	free(ptr_pr_mlc);
	return (p);
}
