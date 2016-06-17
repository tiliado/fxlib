#include <string.h>
#include "fxlib/macros.h"
#include "fxlib/ref.h"
#include "fxlib/strbuf.h"


struct fxstrbuf
{
	char* buffer;
	size_t size;
	uint offset;
};

static void fxstrbuf_init(fxstrbuf_t* buf, size_t size);
static void fxstrbuf_free(fxstrbuf_t* buf);

#define FXSTRBUF_ALLOC_STEP 32

fxstrbuf_t* fxstrbuf_new(size_t size)
{
	fxstrbuf_t* buf = fx_new(fxstrbuf_t, (fx_free_func*) fxstrbuf_free);
	fxstrbuf_init(buf, size);
	return buf;
}

static void fxstrbuf_init(fxstrbuf_t* buf, size_t size)
{	
	buf->size = size > FXSTRBUF_ALLOC_STEP ? size : FXSTRBUF_ALLOC_STEP;
	buf->buffer = fx_alloc(buf->size, char);
	buf->offset = 0;
}

void fxstrbuf_reset(fxstrbuf_t* buf, size_t size)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	fxstrbuf_free(buf);
	fxstrbuf_init(buf, size);
}

void fxstrbuf_extend(fxstrbuf_t* buf, uint increment)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	if (buf->offset + increment >= buf->size)
    {
		buf->size += FXSTRBUF_ALLOC_STEP > increment ? FXSTRBUF_ALLOC_STEP : increment;
		buf->buffer = realloc((void*) buf->buffer, buf->size);
	}
}

void fxstrbuf_append_c(fxstrbuf_t* buf, char value)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	fxstrbuf_extend(buf, 1);
	buf->buffer[buf->offset] = value;
	buf->offset++;
}

void fxstrbuf_append(fxstrbuf_t* buf, char* value)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	if (value == NULL || value[0] == '\0')
		return;
	int offset;
	int len = strlen(value);
	fx_return_if_fail(buf->buffer != NULL);
	fxstrbuf_extend(buf, len);
	for (offset = 0; offset < len; offset++)
		buf->buffer[buf->offset + offset] = value[offset];
	buf->offset += len;
}

void fxstrbuf_append_bool(fxstrbuf_t* buf, bool value)
{
	fxstrbuf_append(buf, value ? "true" : "false");
}

void fxstrbuf_append_int(fxstrbuf_t* buf, int value)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	int tmp, len, pos;
	tmp = value;
	len = value > 0 ? 1 : 2;
	while (tmp /= 10)
		len++;
	fxstrbuf_extend(buf, len);
	buf->offset += len;
	if (value < 0)
	{
		buf->buffer[buf->offset - len] = '-';
		len--;
		value *= -1;
	}
	for (pos = 0; pos < len; pos++)
	{
		buf->buffer[buf->offset - pos - 1] = "0123456789abcdef"[value % 10];
		value /= 10;
	}
}

void fxstrbuf_append_uint(fxstrbuf_t* buf, uint value)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	uint tmp;
	int len, pos;
	tmp = value;
	len = 1;
	while (tmp /= 10)
		len++;
	fxstrbuf_extend(buf, len);
	buf->offset += len;
	for (pos = 0; pos < len; pos++)
	{
		buf->buffer[buf->offset - pos - 1] = "0123456789abcdef"[value % 10];
		value /= 10;
	}
}

void fxstrbuf_append_double(fxstrbuf_t* buf, double value, int precision)
{
	fx_return_if_fail(buf != NULL && buf->buffer != NULL);
	int zeroes = 0;
	int digit;
	fxstrbuf_append_int(buf, (int) value);
	value -= (int) value;
	if (precision > 0)
	{
		fxstrbuf_append_c(buf, '.');
		if (value >= 0.00001)
		{
			for (int i = 0; i < precision && value > 0; i++)
			{
				value *= 10;
				digit = (int) (value + ((i == precision - 1) ? .5 : 0));
				if (i == 0 || digit > 0)
				{
					while (zeroes > 0)
						fxstrbuf_append_c(buf, '0'), zeroes--;
					fxstrbuf_append_c(buf, '0' + digit);
				}
				else
				{
					zeroes++;
				}
				value -= (int) value;
			}
		}
		else
		{
			fxstrbuf_append_c(buf, '0');
		}
	}
}

int fxstrbuf_offset(fxstrbuf_t* buf)
{
	return buf->offset;
}

size_t fxstrbuf_size(fxstrbuf_t* buf)
{
	return buf->size;
}

char* fxstrbuf_peek(fxstrbuf_t* buf)
{
	return buf->buffer;
}

char* fxstrbuf_end(fxstrbuf_t* buf)
{
	fx_return_val_if_fail(buf->buffer != NULL, NULL);
	fxstrbuf_append_c(buf, '\0');
	char* buffer = buf->buffer;
	buf->buffer = NULL;
	fx_unref(buf);
	return buffer;
}

static void fxstrbuf_free(fxstrbuf_t* buf)
{
	if (buf->buffer != NULL)
		free(buf->buffer);
}
