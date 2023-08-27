#include "monty.h"

/**
 * errusage - prints an error to stderr when the arguments are out of range
 *
 * Return: void
 */
void errusage(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}

/**
 * errmalloc - prints an error to stderr when malloc fails
 *
 * Return: void
 */
void errmalloc(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}

/**
 * erropcode - prints an error to stderr when the opcode is invalid
 * @opcode: pointer to the structure of opcode
 * @linenum: the number of the line
 *
 * Return: void
 */
void erropcode(char *opcode, int linenum)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", linenum, opcode);
	exit(EXIT_FAILURE);
}

/**
 * errpush - prints an error to stderr when the argument is not integer
 * @linenum: the line of the number
 *
 * Return: void
 */

void errpush(int linenum)
{
	fprintf(stderr, "L%d: usage: push integer\n", linenum);
	exit(EXIT_FAILURE);
}
