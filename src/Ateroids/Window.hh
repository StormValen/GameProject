#pragma once
#include <SDL.h>
#include <string>

class Window {
	Window(std::string &&name, int width, int height): w_name(name), w_height(height), w_width(width) {

	}
public:
	~Window() {

	}
private:
	int w_width, w_height;
	std::string w_name;
	SDL_Window *window{ nullptr };
};