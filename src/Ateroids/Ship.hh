#pragma once
#include <SDL.h>
#include <iostream>
#include "Sprite.hh"
#include "Transform.hh"

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
		if (alive)
		{
			// Go forward
			


			//if (IM.IsKeyHold<KEY_BUTTON_UP>()) {
				//transform.x -= ship_speed;

			std::cout << ship_angle << std::endl;
			float xx = cos(ship_angle);
			float yy = sin(ship_angle);

			std::cout << xx << std::endl;
			std::cout << yy << std::endl;

			

			transform.y -= xx;
			transform.x += yy;

			//}
			/*if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
				//transform.x -= ship_speed;
				ship_angle -= 5;
			}*/

			/*if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
				//transform.x += ship_speed;
				ship_angle += 5;
			}*/
		}
	    if (transform.y == 400)transform.y = 0;
		else if (transform.y == 0)transform.y = 400;
		else if (transform.x == 600)transform.x = 0;
		else if (transform.x == 0)transform.x = 600;
	}
	void RotateRight() {
		ship_angle += 5 % 360;
	}
	void RotateLeft() {
		ship_angle -= 5 % 360;
	}
	

	
	virtual void Draw() { R.Push(objectID, transform, ship_angle); };
};

