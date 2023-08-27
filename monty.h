#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *stack_f;

int backtoline(int fd, char *buf, int readbytes);
int interpret(char *buf, int linescount, int size);
int getlinescount(char *buf);
int stripword(char **word, char **buf);
void execopcode(char *opname, char *arg, int linenum);
int issame(char *s1, char *s2);
int isnum(char *num);
stack_t *makeframe(void);
void push(stack_t **stack, unsigned int num);
void pall(stack_t **stack, unsigned int linenum);
void pint(stack_t **stack, unsigned int linenum);
void nop(stack_t **stack, unsigned int linenum);
void errusage(void);
void errmalloc(void);
void erropcode(char *opcode, int linenum);
void errpush(int linenum);

#endif
