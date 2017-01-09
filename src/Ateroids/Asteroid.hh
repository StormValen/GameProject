#pragma once
#include "Sprite.hh"
#include "Transform.hh"


class Asteroid : public Sprite {

public:
	int x, y;
	int velocity;
	int dim, dir;
	
	Asteroid(int dim, int velocidadNivel):dim(dim){
		x = rand()%600;
		y = rand()%400;
		dir = rand() % 8;
		velocity = velocidadNivel;

		switch (dim) {//Switch que difine el sprite del asteroide segun su dimension.
		case 0:transform = { x,y, 90,90 }; objectID = ObjectID::GREAT_AST; break;
		case 1:transform = { x,y,60,60 };objectID = ObjectID::MIDDLE_AST; break;
		case 2:transform = { x,y, 30,30 };objectID = ObjectID::LITTLE_AST; break;
		default:break;
		}
		
	}
	Asteroid(int dim, int x, int y, int velocidadNivel) :dim(dim), x(x), y(y) {
		dir = rand() % 8;
		velocity = velocidadNivel;

		switch (dim) {//Switch que difine el sprite del asteroide segun su dimension.
		case 0:transform = { x,y, 90,90 }; objectID = ObjectID::GREAT_AST; break;
		case 1:transform = { x,y,60,60 }; objectID = ObjectID::MIDDLE_AST; velocity++; break;
		case 2:transform = { x,y, 30,30 }; objectID = ObjectID::LITTLE_AST; velocity += 2; break;
		default:break;
		}

	}
	~Asteroid() {
	}
	void Update() {
		switch (dim) { //Actualiza la posicion del sprite,
		case 0:transform = { x,y, 90,90 };objectID = ObjectID::GREAT_AST;break;
		case 1:transform = { x,y,60,60 };objectID = ObjectID::MIDDLE_AST;break;
		case 2:transform = { x,y, 30,30 };objectID = ObjectID::LITTLE_AST;break;
		default:break;
		}
	}

	void Movement() {
		
		switch (dir) {//Existen 8 opciones de movimiento para los asteroides 0�/90�/180�/270� y las diagonales.
		case 0:x += velocity; if (x > 600)x = 0; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 1:x -= velocity; if (x < 0)x = 600; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 2:y += velocity; if (y > 400)y = 0; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 3:y -= velocity; if (y < 0)y = 400; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 4:x += velocity; if (x > 600)x = 0;y += velocity; if (y > 400)y = 0; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 5:x -= velocity; if (x < 0)x = 600;y -= velocity; if (y < 0)y = 400; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 6:x += velocity; if (x > 600)x = 0;y -= velocity; if (y < 0)y = 400; std::cout << transform.x << " - " << transform.y << std::endl; break;
		case 7:x -= velocity; if (x < 0)x = 600;y += velocity; if (y > 400)y = 0; std::cout << transform.x << " - " << transform.y << std::endl; break;
		default:break;
		}
	}
	//La funcion Movement() actualiza la posicion del objeto en si, y la del Update() actualiza la de su sprite.
	void RandomDir() {
		dir = rand() % 8;
	}
	virtual void Draw() { R.Push(objectID, transform); };
};