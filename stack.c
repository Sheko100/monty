#include "monty.h"

/**
 * makeframe - creates a new stack frame
 *
 * Return: a pointer to the new frame
 */

stack_t *makeframe(void)
{
	stack_t *newframe = NULL;

	newframe = malloc(sizeof(stack_t));
	if (newframe == NULL)
		errmalloc();

	return (newframe);
}

/**
 * freestack - frees the stack
 *
 * Return: void
 */
void freestack(void)
{
	stack_t *frame = NULL, *nextframe = NULL;

	frame = stack_f;
	while (frame != NULL)
	{
		nextframe = frame->next;
		free(frame);
		frame = nextframe;
	}
}
