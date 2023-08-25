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
	int readbytes, fd, i = 1, n = 0, offset, linescount = 0;
	char buf[BUFSIZE];

	if (ac <= 1)
		errusage();
	while (av[i])
	{
		fd = open(av[i], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "Error: Can't open file %s\n", av[i]);
			exit(EXIT_FAILURE);
		}
		while ((readbytes = read(fd, buf, BUFSIZE)) > 0)
		{
			offset = 0;
			if (buf[readbytes] != '\n')
			{
				n = readbytes;
				while (n >= 0)
				{
					if (buf[n] == '\n' || buf[n] == ' ' || buf[n] == '	')
						break;
					n--;
					offset--;
				}
				if (n > -1)
				{
					offset = offset + 1;
					lseek(fd, offset, SEEK_CUR);
					readbytes = n + 1;
				}
			}
			linescount += interpret(buf, linescount, readbytes);
		}
		close(fd);
		i++;
	}
	return (0);
}

/**
 * interpret - interprets the lines of bytecode buffer and executes them
 * @buf: array of chars
 * @linescount: the lines count
 * @size: the buffer size
 *
 * Return: the count of lines
 */
int interpret(char *buf, int linescount, int size)
{
	char *opcode, *arg;

	buf[size] = '\0'; /* terminate the buffer string */
	while (*buf)
	{
		opcode = NULL;
		arg = NULL;
		if (*buf == '\n')
			linescount++;
		else if (*buf != 9 && *buf != 32)
		{
			opcode = buf;
			while (*buf != 9 && *buf != 32 && *buf != 10)
				buf++;
			if (*buf == '\n')
			{
				linescount++;
				*buf = '\0';
			}
			else
			{
				*buf = '\0';
				buf++;
				while (*buf == 9 || *buf == 32)
					buf++;
				if (*buf != '\n')
				{
					arg = buf;
					while (*buf != 9 && *buf != 32 && *buf != 10)
						buf++;
					if (*buf == '\n')
					{
						linescount++;
						*buf = '\0';
					}
					else
					{
						*buf = '\0';
						while (*buf != '\n')
							buf++;
						linescount++;
					}
				}
				else if (*buf == '\n')
					linescount++;
			}
			execopcode(opcode, arg, linescount);
		}
		buf++;
	}
	return (linescount);
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
	instruction_t *opcode;
	unsigned int num = 0;

	opcode = malloc(sizeof(instruction_t));
	if (opcode == NULL)
		errmalloc();
	opcode->opcode = opname;
	if (issame("push", opcode->opcode))
	{
		opcode->f = push;
		if (isnum(arg))
			num = atoi(arg);
		else
			errpush(linenum);
		opcode->f(&stack_f, num);
	}
	else if (issame("pall", opcode->opcode))
	{
		opcode->f = pall;
		opcode->f(&stack_f, linenum);
	}
	else if (issame("pint", opcode->opcode))
	{
		opcode->f = pint;
		opcode->f(&stack_f, linenum);
	}
	else if (issame("nop", opcode->opcode))
	{
		opcode->f = nop;
		opcode->f(&stack_f, linenum);
	}
	else
		erropcode(opcode, linenum);
}
