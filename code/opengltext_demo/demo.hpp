#pragma once

#include <SDL2/SDL.h>
#include <GL/gl3w.h>
#include <string>

const int OPENGL_VERSION_MAJOR = 4;
const int OPENGL_VERSION_MINOR = 4;
const int VIEWPORT_INITIAL_WIDTH = 800;
const int VIEWPORT_INITIAL_HEIGHT = 600;
const std::string WINDOW_TITLE = "OpenGL Text Demo";

class Demo
{
public:
	Demo();
	~Demo();
private:
	SDL_Window* window;
	SDL_GLContext glcontext;
	GLuint viewport_width;
	GLuint viewport_height;
	bool running;

	void setup_context();
	void run();
	void handle_events();
	void render();
};