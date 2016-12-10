#include "GameEngine.hh"

// Game constants
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int main(int argc, char* args[]) {
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("ENTI Crush");
	return 0;
}