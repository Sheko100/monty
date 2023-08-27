#include "monty.h"

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
	int isend, linenum = 1;

	buf[size] = '\0';
	linescount = getlinescount(buf);

	while (linenum <= linescount)
	{
		opcode = NULL;
		arg = NULL;
		isend = 0;

		while (*buf != '\n')
		{
			if (*buf != ' ' && *buf != 9)
			{
				if (opcode == NULL)
					isend = stripword(&opcode, &buf);
				else if (arg == NULL)
					isend = stripword(&arg, &buf);

				if (isend)
					break;
			}
			buf++;
		}
		if (opcode != NULL)
			execopcode(opcode, arg, linenum);
		buf++;
		linenum++;
	}
	return (linescount);
}

/**
 * backtoline - Checks and reduces the file offset and read bytes count to
 * the first char of the line or word
 * @fd: file descriptor
 * @buf: pointer to array of the chars which have been read
 * @readbytes: the count of bytes which have been read
 *
 * Return: a new count of bytes
 */
int backtoline(int fd, char *buf, int readbytes)
{
	int offsetmargin = 0, n = readbytes;
	char tab = 9;

	while (n > -1)
	{
		if (buf[n] == '\n' || buf[n] == ' ' || buf[n] == tab)
			break;
		n--;
		offsetmargin--;
	}
	if (n == -1)
		return (readbytes);
	n++;
	offsetmargin++;
	lseek(fd, offsetmargin, SEEK_CUR);

	return (n);
}

/**
 * getlinescount - counts the number of lines
 * @buf: pointer to a buffer
 *
 * Return: lines count
 */

int getlinescount(char *buf)
{
	int lines = 0;

	while (*buf)
	{
		if (*buf == '\n')
			lines++;
		buf++;
	}
	return (lines);
}

/**
 * stripword - strips word from a line and checks if it's the end of line
 * @word: pointer which will be assigned to the word
 * @buf: pointer to the first char of the word
 *
 * Return: 1 if it's the end of line
 * 0 otherwise
 */

int stripword(char **word, char **buf)
{
	int isend = 0;

	*word = *buf;
	while (**buf != ' ' && **buf != 9 && **buf != '\n')
		(*buf)++;

	if (**buf == '\n')
		isend = 1;

	**buf = '\0';

	return (isend);
}
