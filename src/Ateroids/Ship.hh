#pragma once
#include <SDL.h>
#include <iostream>
#include "Sprite.hh"
#include "Transform.hh"
#include <math.h>

#define PI 3.14159265

using namespace std;


class  Ship : public Sprite {

	//SDL_Point pos;
	int ship_speed;
	float ship_angle;
	bool alive = true;

public:
	
	//Sprite ship_image;

	Ship()
	{
		transform = { 300,200, 20,25 };
		objectID = ObjectID::PLAYER;
		ship_speed = 1;
		ship_angle = 0.0;

		//ship_image = { { pos.x, pos.y, 20, 25 }, ObjectID::PLAYER };
	}

	~Ship()
	{

	}

	//SDL_Point getPos() { return pos; }
	bool isAlive() { return alive; }
	//void setAlive() { alive; }
	//void rotate(const int& val) { rotation = val; }

	
	void Movement()
	{
		
			
			std::cout << ship_angle << std::endl;


			float A = cos(ship_angle*PI / 180);
			float B = sin(ship_angle*PI / 180);

			transform.x += B*10;
			std::cout << B << std::endl;
			transform.y -= A*10;
			std::cout << A << std::endl;



		
	
	    if (transform.y >= 400)transform.y = 0;
		else if (transform.y <= 0)transform.y = 400;
		else if (transform.x >= 600)transform.x = 0;
		else if (transform.x <= 0)transform.x = 600;
	}
	void RotateRight() {
		ship_angle += 5;
		if (ship_angle >= 360)ship_angle = 0;
	
		std::cout << ship_angle << std::endl; 
	}
	void RotateLeft() {
		if (ship_angle == 0) {
			ship_angle = 355;
		}
		else {
			ship_angle -= 5;
		}

		if (ship_angle >= 360)ship_angle = 0;
		std::cout << ship_angle << std::endl;
	}
	

	
	virtual void Draw() { R.Push(objectID, transform, ship_angle); };
};

