#include <stdio.h>
#include <stdarg.h>
#include "fxlib/typedefs.h"
#include "fxlib/strbuf.h"
#include "fxlib/strfmt.h"

void fxprintf(char* format, ...)
{
	va_list args;
	char* result;
	va_start(args, format);
	result = fxstrfmtva(format, args);
	puts(result);
	free(result);
	va_end(args);
}

char* fxstrfmt(char* format, ...)
{
	va_list args;
	char* result;
	va_start(args, format);
	result = fxstrfmtva(format, args);
	va_end(args);
	return result;
}

char* fxstrfmtva(char* format, va_list args)
{
	fxstrbuf_t* buf = fxstrbuf_new(32);
	uint offset = 0;
	int i_value;
	uint u_value;
	char* s_value;
	double g_value;
	char ctrch;
	// %[flags][width][.precision][length]specifier
	int fmt_width; // parsed but ignored
	bool fmt_dot;
	int fmt_precision; // parsed but used only for double
	  
	while (true)
	{
	    while (format[offset] != '%')
	    {
			if (format[offset] == 0)
				goto exit;
			fxstrbuf_append_c(buf, format[offset++]);
	    }
	    
	    fmt_width = -1;
	    fmt_precision = -1;
	    fmt_dot = false;
	    ctrch = format[++offset];
	    if (ctrch == 0)
			goto exit;
	    if (ctrch == '.')
	    {
			fmt_dot = true;
			ctrch = format[++offset];
			if (ctrch == 0)
				goto exit;
		}
		else
		{
			while (ctrch >= '0' && ctrch < '9')
		    {
				int digit = ctrch - '0';
				fmt_width = fmt_width == -1 ? digit : fmt_width * 10 + digit;
				ctrch = format[++offset];
			}
			if (ctrch == '.')
		    {
				fmt_dot = true;
				ctrch = format[++offset];
			}
			if (ctrch == 0)
				goto exit;
		}
		if (fmt_dot)
		{
			while (ctrch >= '0' && ctrch < '9')
		    {
				int digit = ctrch - '0';
				fmt_precision = fmt_precision == -1 ? digit : fmt_precision * 10 + digit;
				ctrch = format[++offset];
			}
			if (ctrch == 0)
				goto exit;
		}
	
	    switch(ctrch)
	    {
		case 'd':
		case 'i':
			i_value = va_arg(args, int);
			fxstrbuf_append_int(buf, i_value);
			break;
		case 'u':
			u_value = va_arg(args, uint);
			fxstrbuf_append_uint(buf, u_value);
			break;
		case 's':
			s_value = va_arg(args, char*);
			fxstrbuf_append(buf, s_value != NULL ? s_value : "(null)");
			break;
		case 'f':
		case 'g':
		case 'e':
		case 'E':
			g_value = va_arg(args, double);
			fxstrbuf_append_double(buf, g_value, fmt_dot && fmt_precision >= 0 ? fmt_precision : 6);
		break;
		case '%':
			fxstrbuf_append_c(buf, '%');
			break;
		case 'b':
			i_value = va_arg(args, int);
			fxstrbuf_append_bool(buf, i_value);
			break;
		default:
			goto exit;
			break;
		}
		offset++;
	}
	exit:
		return fxstrbuf_end(buf);
}
