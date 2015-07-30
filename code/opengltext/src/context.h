#pragma once

#include "../include/opengltext.h"

#include <ft2build.h>
#include FT_FREETYPE_H

typedef void*(*gltext_malloc_t)(size_t);
typedef void(*gltext_free_t)(void*);

typedef struct
{
	FT_Library freetype;
	gltext_error_t error;
	char error_message_custom[128];
	gltext_malloc_t gltext_malloc;
	gltext_free_t gltext_free;
} gltext_library_t;

extern gltext_library_t library;