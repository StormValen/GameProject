#pragma once
#include <SDL.h>
#include <iostream>
#include "Sprite.hh"
#include "Transform.hh"

using namespace std;


class Ship {

	SDL_Point pos;
	float ship_speed;
	float ship_angle = 0.0;
	bool alive = true;

public:
	
	Sprite ship_image;
	enum rotateDir { LEFT = 1, RIGHT = 2, NONE = 0 };
	int rotation = NONE;

	Ship() : pos({ 300,200 })
	{
		ship_speed = 0.0;
		ship_angle = 0.0;
		ship_image = { { pos.x, pos.y, 20, 20 }, ObjectID::PLAYER };
	}

	~Ship()
	{

	}

	SDL_Point getPos() { return pos; }
	bool isAlive() { return alive; }
	//void setAlive() { alive; }
	//void rotate(const int& val) { rotation = val; }

	void update()
	{
		ship_image = { { pos.x, pos.y, 20, 20 }, ObjectID::PLAYER };
	}

	void movement()
	{
		switch (alive)
		{
		case 0:
			IM.IsKeyDown<KEY_BUTTON_UP>();
			ship_speed += 1;
			pos.y += 10;
			ship_angle = 0.0;

			if (pos.y == 400)pos.y = 0;
			break;

		case 1:
			IM.IsKeyDown<KEY_BUTTON_DOWN>();
			ship_speed += 1;
			pos.y -= 10;
			ship_angle = 0.0;

			if (pos.y == 0)pos.y = 4000;
			break;

		case 2:
			IM.IsKeyDown<KEY_BUTTON_LEFT>();
			ship_speed += 1;
			pos.x -= 10;
			ship_angle += 0.1;

			if (pos.x == 600)pos.x = 0;
			break;

		case 3:
			IM.IsKeyDown<KEY_BUTTON_RIGHT>();
			ship_speed += 1;
			pos.x += 10;
			ship_angle += 0.1;

			if (pos.x == 0)pos.x = 600;
			break;
	

		default:
			break;
		}
	}
};