#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bug (const char *p_text)
{
	fprintf(stderr, "BUG >> %s\n", p_text);
	exit (1);
}
