#pragma once
#include <SDL.h>
#include <iostream>
#include "Sprite.hh"
#include "Transform.hh"

using namespace std;


class Ship {

	SDL_Point pos;
	int ship_speed;
	float cosA;
	float sinA;
	float vel[2];
	float ship_angle;
	bool alive = true;
	int rot = NONE;

public:
	
	Sprite ship_image;
	enum rotateDir { LEFT = 1, RIGHT = 2, NONE = 0 };

	Ship() : pos({ 300,200 })
	{
		ship_speed = 1;
		ship_angle = 0.0;
		cosA = 0.0;
		sinA = 0.0;
		vel[0] = 0.0;
		vel[1] = 0.0;

		ship_image = { { pos.x, pos.y, 20, 25 }, ObjectID::PLAYER };
	}

	~Ship()
	{

	}

	SDL_Point getPos() { return pos; }
	bool isAlive() { return alive; }
	//void setAlive() { alive; }
	//void rotate(const int& val) { rotation = val; }

	
	void Movement()
	{
		if (alive)
		{
			cosA = cos(ship_angle);
			sinA = sin(ship_angle);

			// Go forward
			pos.y -= ship_speed;
			vel[0] += ship_speed * cosA;
			vel[1] += ship_speed * sinA;
	

			if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
				pos.x -= ship_speed;
			}

			if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
				pos.x += ship_speed;
			}

			switch (rot)
			{
			case LEFT:
				ship_angle -= 0.175;
				break;

			case RIGHT:
				ship_angle += 0.175;
				break;

			case NONE:
				break;

			default:
				break;
			}
			//pos.x -= vel[0];
			//pos.x += vel[1];

		
		}
	    if (pos.y == 400)pos.y = 0;
		else if (pos.y == 0)pos.y = 400;
		else if (pos.x == 600)pos.x = 0;
		else if (pos.x == 0)pos.x = 600;
	}
	
	void Update()
	{
		ship_image = { { pos.x, pos.y, 20, 25 }, ObjectID::PLAYER };
	}
};

