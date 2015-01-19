#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>


int main(int argc, char **argv)
{
    int groupsize = 3;
    char sepchar = '.';
    int maxseps = 0;
    if (argc >= 2)
        maxseps = atoi(argv[1]);
    int size;
    size_t allocated = 0;
    char *line = NULL;
    char *buffer = malloc(1024);
    int linenum = 0;
    while ((size = getline(&line, &allocated, stdin)) > 0)
    {
        if (size == 1 && line[0] == '\n')
            continue;
        linenum++;
        int linecursor = 0;
        int bufcursor = 0;
        while (line[linecursor])
        {
            if (isdigit(line[linecursor]))
            {
                char *number = line + linecursor;
                int numsize = 0;
                while (isdigit(number[numsize]))
                    numsize++;
                if (line[linecursor - 1] == ' ')
                {
                    int addspaces = maxseps - (numsize - 1) / groupsize;
                    for (int i = 0; i < addspaces; i++)
                        buffer[bufcursor++] = ' ';
                }
                if (numsize > groupsize)
                {
                    int prefix = numsize % groupsize;
                    if (prefix == 0)
                        prefix = groupsize;
                    for (int i = 0; i < prefix; i++)
                        buffer[bufcursor++] = *(number++);
                    linecursor += prefix;
                    numsize -= prefix;
                    for (int i = 0; i < numsize; i++)
                    {
                        if (i % groupsize == 0)
                            buffer[bufcursor++] = sepchar;
                        buffer[bufcursor++] = number[i];
                    }
                }
                else
                    for (int i = 0; i < numsize; i++)
                        buffer[bufcursor++] = number[i];
                linecursor += numsize;
            }
            else
                buffer[bufcursor++] = line[linecursor++];
        }
        if (buffer[bufcursor - 1] == '\n')
            buffer[bufcursor - 1] = '\0';
        else
            buffer[bufcursor] = '\0';
        puts(buffer);
    }
    free(line);
    free(buffer);
}




