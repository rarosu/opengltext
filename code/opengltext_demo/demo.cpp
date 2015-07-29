#include "demo.hpp"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	int result = 0;
	try
	{
		Demo demo;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cin.get();
		result = 1;
	}
	catch (...)
	{
		std::cerr << "Unrecognized exception caught at outmost level." << std::endl;
		std::cin.get();
		result = 1;
	}

	return result;
}

void __stdcall output_debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* param)
{
	if (type == GL_DEBUG_TYPE_ERROR)
	{
		std::cerr << message << std::endl;
	}
}

Demo::Demo()
	: window(nullptr)
	, glcontext(nullptr)
	, viewport_width(VIEWPORT_INITIAL_WIDTH)
	, viewport_height(VIEWPORT_INITIAL_HEIGHT)
	, running(true)
{
	setup_context();
	run();
}

Demo::~Demo()
{

}

void Demo::setup_context()
{
	// Setup SDL.
	if (SDL_Init(SDL_INIT_TIMER) != 0)
	{
		throw std::runtime_error(std::string("Failed to initialize SDL: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, viewport_width, viewport_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());
	}

	// Initialize the OpenGL context.
	SDL_GLcontextFlag flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#ifndef NDEBUG
	flags = (SDL_GLcontextFlag)(flags | SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_VERSION_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_VERSION_MINOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, flags);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);

	glcontext = SDL_GL_CreateContext(window);
	if (glcontext == nullptr)
	{
		throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
	}

	// Initialize the profile loader.
	if (gl3wInit() != 0)
	{
		throw std::runtime_error(std::string("Failed to initialize gl3w"));
	}

	if (gl3wIsSupported(OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR) != 1)
	{
		std::stringstream ss;
		ss << "OpenGL " << OPENGL_VERSION_MAJOR << "." << OPENGL_VERSION_MINOR << " is not supported.";
		throw std::runtime_error(ss.str());
	}

	// Setup an error callback function.
	glDebugMessageCallback(output_debug_message, nullptr);

	// Setup the initial OpenGL context state.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, viewport_width, viewport_height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	{
		int major;
		int minor;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);

		std::cout << "OpenGL version: " << major << "." << minor << std::endl;
	}

	// Set V-Sync enabled.
	SDL_GL_SetSwapInterval(1);
}

void Demo::run()
{
	while (running)
	{
		handle_events();
		render();
	}
}

void Demo::handle_events()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				running = false;
			} break;

			case SDL_KEYDOWN:
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			} break;

			case SDL_WINDOWEVENT:
			{
				switch (e.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
					{
						viewport_width = e.window.data1;
						viewport_height = e.window.data2;
						glViewport(0, 0, viewport_width, viewport_height);
					} break;
				}
			} break;
		}
	}
}

void Demo::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SDL_GL_SwapWindow(window);
}