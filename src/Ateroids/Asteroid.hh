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
		x = rand()%600;
		y = rand()%400;
		velocity = 1;
		dim = 1;
		dir = rand() % 8;
		asteroid_image = { { x, y,50,50 },ObjectID::MIDDLE_AST };
	}
	~Asteroid() {
	}
	void Update() {
		asteroid_image = { {x,y,50,50},ObjectID::MIDDLE_AST };
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
		case 4:
			x += velocity; if (x == 600)x = 0;
			y += velocity; if (y == 400)y = 0;
			break;
		case 5:
			x -= velocity; if (x == 0)x = 600;
			y -= velocity; if (y == 0)y = 400;
			break;
		case 6:
			x += velocity; if (x == 600)x = 0;
			y -= velocity; if (y == 0)y = 400;
			break;
		case 7:
			x -= velocity; if (x == 0)x = 600;
			y += velocity; if (y == 400)y = 0;
			break;
		default:
			break;
		}
	}
	void RandomDir() {
		dir = rand() % 8;
	}
};