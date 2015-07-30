#include <ft2build.h>
#include FT_FREETYPE_H

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

static const struct
{
	int code;
	const char* message;
} ft_errors[] =

#include FT_ERRORS_H