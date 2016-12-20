#pragma once
#include <SDL.h>
#include <iostream>
#include "Sprite.hh"
#include "Transform.hh"
#include <math.h>

#define PI 3.14159265

using namespace std;


class  Ship : public Sprite {
	int ship_speed;
	float ship_angle;
	bool alive = true;
public:
	Ship()
	{
		transform = { 300,200, 20,25 };
		objectID = ObjectID::PLAYER;
		ship_speed = 1;
		ship_angle = 0.0;
	}

	~Ship()
	{

	}

	bool isAlive() { return alive; }
	void dead() {
			alive = false;
	}
	void Movement()
	{
		if (alive == true) {
			float A = cos(ship_angle*PI / 180);
			float B = sin(ship_angle*PI / 180);
			transform.x += B * 10;
			transform.y -= A * 10;

			if (transform.y >= 400)transform.y = 0;
			else if (transform.y <= 0)transform.y = 400;
			else if (transform.x >= 600)transform.x = 0;
			else if (transform.x <= 0)transform.x = 600;
		}
		else {
			SM.SetCurScene<MenuScene>();
		}
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

