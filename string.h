#ifndef _STRING_H_
#define _STRING_H_

#ifndef _IO_H_
#include "io.h"
#endif

/* strlen:  count length of string; to null terminator */
static int
strlen (const char *s)
{
	const char *p = s;
	while (*p++);
	return (p-s-1);
}

/* getline:  get string of characters; size of lim-1 */
static int
getline (char *s, int lim)
{
	char *p = s;
	char c;
	while (lim-- > 2 && (c = getche()) != '\r')
		switch (c) {
			case '\b':
				*--s = '\0';
				print(" \b");
				break;
			case '\r':
				putchar('\n');
				break;
			default:
				*s++ = c;
			break;
		}
	if (c == '\r') {
		*s++ = c;
		*s++ = '\n';
	}
	*s = '\0';
	return s-p;
}

/* trim:  trim new line off string s */
static void
trim(char *s)
{
	while (*s) {
		if (*s == '\r' || *s == '\n')
			break;
		s++;
	}
	*s = '\0';
}

/* strcpy:  copy t to s; returns length on success, if failed returns -1 */
static int
strcpy (char *s, const char *t)
{
	char *p = s;
	while ((*s++ = *t++) != '\0');
	return s-p-1;
}

/* memcpy:  copy p2 to p1, n amount of bytes; returns void (nothing) */
static void
memcpy (void *p1, void *p2, int n)
{
	char *p = (char*)p2;
	while (((char*)p2)-p < n)
		*((char*)p1++) = *((char*)p2++);
}

/* metset:  set p1 to n amount of bytes */
static void
memset (void *p1, char byte, int n)
{
	char *p = (char*)p1;
	while (p-((char*)p1) < n)
		*p++ = byte;
}

/* strcmp:  compare t to s; returns 0 if match, anything else if false */
static int
strcmp (const char *s, const char *t)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return *s-*t;
	return *s-*t;
}

#endif
