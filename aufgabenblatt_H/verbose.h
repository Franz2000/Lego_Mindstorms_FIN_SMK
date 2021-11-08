#ifndef VERBOSE_HEADER
#define VERBOSE_HEADER

#include <stdio.h>
#include <stdarg.h>

extern int is_verbose;

/*****************************************************************************
* print_verbose
*
* @param[in] condition	condition to print the verbose message
* @param[in] *format	verbose message
* @param[in] ...		free variable parameter for more e.g. %s
*
* The function prints a verbose message if the verbose is on and another
* condition is true.
******************************************************************************/
static void print_verbose(int condition, const char *format, ...)
{
	if(!condition || !is_verbose)
	{
		return;
	}

	va_list args;
	va_start(args, format);
	while(*format != '\0')
	{
		if(*format == '%')
		{
			++format;
			switch(*format)
			{
				case 'i':	printf("%i", va_arg(args, int));
							break;
				case 's':	printf("%s", va_arg(args, char*));
							break;
				default:	printf("NOT FOUND");
			}
			++format;
			continue;
		}
		printf("%c", *format);
		++format;
	}
	va_end(args);
}
#endif
