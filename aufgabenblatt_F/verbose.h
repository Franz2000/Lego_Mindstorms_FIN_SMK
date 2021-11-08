#ifndef VERBOSE_HEADER
#define VERBOSE_HEADER

#include <stdio.h>
#include <stdarg.h>

extern int is_verbose;

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
