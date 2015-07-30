#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct gltext_font_t gltext_font_t;
typedef struct gltext_text_t gltext_text_t;
typedef struct gltext_paragraph_t gltext_paragraph_t;

typedef enum
{
	GLTEXT_ERROR_NONE = 0,
	GLTEXT_ERROR_UNKNOWN,
	GLTEXT_ERROR_OUT_OF_MEMORY,
	GLTEXT_ERROR_FREETYPE
} gltext_error_t;


/** 
	Initialize the opengltext library. 
*/
gltext_error_t gltext_init();

/** 
	Clean up the opengltext library. 
*/
void gltext_quit();

/** 
	Get a descriptive error message of the last error. 
*/
const char* gltext_get_error();


/**
	Loads and creates a font and its associated textures from file.

	@param fontpath Zero-terminated string specifying the file system location of a TTF file.
	@param[out] out The font structure to save the generated font in.
*/
gltext_error_t gltext_create_font(const char* fontpath, gltext_font_t** out);

/**
	Cleans up the specified paragraph structure.

	@param font The font structure to free the memory of.
*/
void gltext_destroy_font(gltext_font_t* font);

/**
	Creates a cached string of text that can be used to render a line of text.

	@param font The font used for text generation.
	@param string The text to generate as a zero-terminated ASCII string. Pays no heed to '\n' newline character.
	@param[out] out The text structure to save the generated text in.
*/
gltext_error_t gltext_create_text(const gltext_font_t* font, const char* string, gltext_text_t** out);

/**
	Cleans up the specified text structure.

	@param text The text structure to free the memory of.
*/
void gltext_destroy_text(gltext_text_t* text);

/**
	Creates a set of cached text lines that can be used to render a paragraph.

	@param font The font used for text generation.
	@param string The text to generate as a zero-terminated ASCII string. Can contain '\n' newline characters to specify line breaks.
	@param[out] out The paragraph structure to save the generated text in.
*/
gltext_error_t gltext_create_paragraph(const gltext_font_t* font, const char* string, gltext_paragraph_t** out);

/**
	Cleans up the specified paragraph structure.

	@param paragraph The paragraph structure to free the memory of.
*/
void gltext_destroy_paragraph(gltext_paragraph_t* paragraph);


/** 
	Render a single line of text with a given font.

	@param font The font used for text rendering.
	@param x The normalized device x coordinate for the first character.
	@param y The normalized device y coordinate for the baseline.
	@param string The text to render as a zero-terminated ASCII string. Pays no heed to '\n' newline character.
*/
gltext_error_t gltext_render(const gltext_font_t* font, float x, float y, const char* string);

/**
	Render a single line of text with precomputed buffers. Faster than gltext_render but more work to setup and update.

	@param text The precached text.
	@param x The normalized device x coordinate for the first character.
	@param y The normalized device y coordinate for the baseline.
*/
gltext_error_t gltext_render_cached(const gltext_text_t* text, float x, float y);

/**
	Render a paragraph of text with precomputed buffers. Can handle '\n' newlines.

	@param paragraph The precached paragraph.
	@param x The normalized device x coordinate for the first character.
	@param y The normalized device y coordinate for the baseline.
*/
gltext_error_t gltext_render_paragraph(const gltext_paragraph_t* paragraph, float x, float y);

#ifdef __cplusplus
}
#endif