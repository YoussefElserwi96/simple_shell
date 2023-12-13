#include "shell.h"

/**
 * bfree - frees a pointer
 * @pntr: add of ptr
 * Return: 1 if free, otherwise 0.
 */

int bfree(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
