#include "../include/opengltext.h"
#include "context.h"
#include "freetype_error.h"

gltext_library_t library;

gltext_error_t gltext_init()
{
	FT_Error error;

	library.gltext_malloc = malloc;
	library.gltext_free = free;

	error = FT_Init_FreeType(&library.freetype);
	if (error)
	{
		library.error = GLTEXT_ERROR_FREETYPE;
		sprintf(library.error_message_custom, "Freetype error: %s", ft_errors[error].message);
		return library.error;
	}

	return GLTEXT_ERROR_NONE;
}

void gltext_quit()
{
	FT_Done_FreeType(library.freetype);
}

const char* gltext_get_error()
{
	switch (library.error)
	{
		case GLTEXT_ERROR_NONE:
			return "No error.";
		case GLTEXT_ERROR_UNKNOWN:
			return "Unknown error.";
		case GLTEXT_ERROR_OUT_OF_MEMORY:
			return "Out of memory.";
		case GLTEXT_ERROR_FREETYPE:
			return library.error_message_custom;
		default:
			return "No error message specified.";
	}
}