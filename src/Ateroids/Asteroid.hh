#pragma once
#include "Sprite.hh"
#include "Transform.hh"


class Asteroid {

public:
	int x, y;
	int velocity;
	int dim, dir;
	Sprite asteroid_image;
	Asteroid(){
	}
	~Asteroid() {
	}
	void Movement() {
		switch (dir) {
		case 0:
			x += velocity; if (x == 600)x = 0;
			break;
		case 1:
			x -= velocity; if (x == 0)x = 600;
			break;
		case 2:
			y += velocity; if (y == 400)y = 0;
			break;
		case 3:
			y -= velocity; if (y == 0)y = 400;
			break;
		default:
			break;
		}
	}
	void RandomDir() {
		dir = rand() % 4;
	}
};