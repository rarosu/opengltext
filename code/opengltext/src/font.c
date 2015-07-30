#include "../include/opengltext.h"
#include "context.h"
#include <GL/gl3w.h>
#include "freetype_error.h"

struct gltext_font_t
{
	FT_Face face;
	GLuint texture_atlas;
	GLuint distance_texture_atlas;
};

gltext_error_t gltext_create_font(const char* fontpath, gltext_font_t** out)
{
	FT_Error error;

	*out = (gltext_font_t*) library.gltext_malloc(sizeof(gltext_font_t));

	// Load the font face.
	error = FT_New_Face(library.freetype, fontpath, 0, &(*out)->face);
	if (error)
	{
		library.gltext_free(*out);
		library.error = GLTEXT_ERROR_FREETYPE;
		sprintf(library.error_message_custom, "Freetype error: %s", ft_errors[error].message);

		return library.error;
	}

	// Select the charmap.


	//glGenTextures(1, &(*out)->texture_atlas);
	
	//(*out)->face->

	return GLTEXT_ERROR_NONE;
}

void gltext_destroy_font(gltext_font_t* font)
{
	FT_Done_Face(font->face);
	library.gltext_free(font);
}

