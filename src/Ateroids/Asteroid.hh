#pragma once
#include "Sprite.hh"
#include "Transform.hh"


class Asteroid : public Sprite {

public:
	int x, y;
	int velocity;
	int dim, dir;
	
	Asteroid(int dim):dim(dim){
		x = rand()%600;
		y = rand()%400;
		velocity = 1;
		dir = rand() % 8;
		switch (dim) {
		case 0:
			//asteroid_image = { { x, y,50,50 },ObjectID::GREAT_AST };
			transform = { x,y, 90,90 };
			objectID = ObjectID::GREAT_AST;

			break;
		case 1:
			//asteroid_image = { { x, y,50,50 },ObjectID::MIDDLE_AST };
			transform = { x,y,60,60 };
			objectID = ObjectID::MIDDLE_AST;
			break;
		case 2:
			//asteroid_image = { { x, y,50,50 },ObjectID::LITTLE_AST };
			transform = { x,y, 30,30 };
			objectID = ObjectID::LITTLE_AST;
			break;
		default:
			break;
		}
		
	}
	~Asteroid() {
	}
	void Update() {
		/*switch (dim) {
		case 0:
			asteroid_image = { { x, y,90,90 },ObjectID::GREAT_AST };
			break;
		case 1:
			asteroid_image = { { x, y,60,60 },ObjectID::MIDDLE_AST };
			break;
		case 2:
			asteroid_image = { { x, y,30,30 },ObjectID::LITTLE_AST };
			break;
		default:
			break;
		}*/
		switch (dim) {
		case 0:
			//asteroid_image = { { x, y,50,50 },ObjectID::GREAT_AST };
			transform = { x,y, 90,90 };
			objectID = ObjectID::GREAT_AST;

			break;
		case 1:
			//asteroid_image = { { x, y,50,50 },ObjectID::MIDDLE_AST };
			transform = { x,y,60,60 };
			objectID = ObjectID::MIDDLE_AST;
			break;
		case 2:
			//asteroid_image = { { x, y,50,50 },ObjectID::LITTLE_AST };
			transform = { x,y, 30,30 };
			objectID = ObjectID::LITTLE_AST;
			break;
		default:
			break;
		}
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
	virtual void Draw() { R.Push(objectID, transform); };
};