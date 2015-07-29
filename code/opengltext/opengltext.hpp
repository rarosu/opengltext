#pragma once

#include <GL/gl3w.h>

namespace gltext
{
	/*
		Loads a font and generates a collection of glyph textures for rendering use.
	*/
	class Font
	{
	public:
		/*
			Load a font from file.
		*/
		Font(const char* fontpath);
	private:
		 
	};



	/* 
		A pre-cached string of text, ready for rendering.
	*/
	class Text
	{
	public:
		/*
			Generate a text with the font given.
		*/
		Text(const Font& font, const char* text);

		/*
			Render a line of text with the first character at normalized device coordinates (x, y) where y specifies the baseline. 
		*/
		void render(float x, float y);
	private:
		
	};



	/*
		A set of pre-cached strings of text, for multiline rendering.
	*/
	class Paragraph
	{
	public:
		/*
			Generate a paragraph with the font given. The text can include '\n' as line breaks.
		*/
		Paragraph(const Font& font, const char* text);

		/*
			Render the entire paragraph, with the first character at normalized device coordinates (x, y) where y specifies the baseline of the first line.
		*/
		void render(float x, float y);
	private:

	};



	/*
		Render a string with the font given with the first character at normalized device coordinates (x, y) where y specifies the baseline.
	*/
	void render_text(const Font& font, float x, float y, const char* text);
}
