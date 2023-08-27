#include "monty.h"


stack_t *stack_f = NULL;

/**
 * push - pushes an integer to the top of the stack
 * @stack: pointer to the top of the stack
 * @num: number to push to the stack
 *
 * Return: void
 */
void push(stack_t **stack, unsigned int num)
{
	stack_t *frame = NULL, *newframe = NULL;

	newframe = malloc(sizeof(stack_t));
	if (newframe == NULL)
		errmalloc();
	newframe->n = num;
	newframe->prev = NULL;
	newframe->next = NULL;

	frame = *stack;
	if (frame != NULL)
	{
		frame->prev = newframe;
		newframe->next = frame;
	}
		*stack = newframe;
}

/**
 * pall - prints all the stack elements
 * @stack: pointer to the top of the stack
 * @linenum: the number of line
 *
 * Return: void
 */
void pall(stack_t **stack, __attribute__ ((unused))unsigned int linenum)
{
	stack_t *frame;

	frame = *stack;
	while (frame != NULL)
	{
		printf("%d\n", frame->n);
		frame = frame->next;
	}
}

/**
 * pint - prints the value at the top of the stack
 * @stack: pointer to the top of the stack
 * @linenum: the number of line
 *
 * Return: void
 */

void pint(stack_t **stack, unsigned int linenum)
{
	stack_t *frame = NULL;

	frame = *stack;
	if (frame != NULL)
		printf("%d\n", frame->n);
	else
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", linenum);
		exit(EXIT_FAILURE);
	}
}

/**
 * nop - does nothing
 * @stack: pointer to the top of the stack
 * @linenum: the number of line
 *
 * Return: void
 */
void nop(__attribute__ ((unused))stack_t **stack,
		__attribute__ ((unused))unsigned int linenum)
{

}
