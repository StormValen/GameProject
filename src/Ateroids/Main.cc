#include "GameEngine.hh"

// Game constants
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

int main(int argc, char* args[]) {
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Asteroids v0.2");
	return 0;
}