#include "monty.h"

#define BUFSIZE 1024

/**
 * main - opens and reads the monty files to interpret
 * @ac: arguments count
 * @av: arguments values
 *
 * Return: 0 on success
 */

int main(int ac, char **av)
{
	int readbytes, fd, n = 0, linescount = 0;
	char buf[BUFSIZE] = {};

	if (ac != 2)
		errusage();

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while ((readbytes = read(fd, buf, BUFSIZE)) > 0)
	{
		if (buf[readbytes] != '\n')
			readbytes = backtoline(fd, buf, readbytes);

		linescount += interpret(buf, linescount, readbytes);
	}
	close(fd);
	return (0);
}

/**
 * execopcode - check the opcode and executes it
 * @opname: the name of the opcode
 * @arg: the argument of the opcode
 * @linenum: the number of the line
 *
 * Return: void
 */
void execopcode(char *opname, char *arg, int linenum)
{
	instruction_t opcode;
	unsigned int num = 0;

	opcode.opcode = opname;
	if (issame("push", opcode.opcode))
	{
		opcode.f = push;
		if (isnum(arg))
			num = atoi(arg);
		else
			errpush(linenum);
		opcode.f(&stack_f, num);
	}
	else if (issame("pall", opcode.opcode))
	{
		opcode.f = pall;
		opcode.f(&stack_f, linenum);
	}
	else if (issame("pint", opcode.opcode))
	{
		opcode.f = pint;
		opcode.f(&stack_f, linenum);
	}
	else if (issame("nop", opcode.opcode))
	{
		opcode.f = nop;
		opcode.f(&stack_f, linenum);
	}
	else
		erropcode(opcode.opcode, linenum);
}
