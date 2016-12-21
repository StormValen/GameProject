#pragma once
#include "Sprite.hh"
#include "Transform.hh"
#include "Ship.hh"
#include "GameScene.hh"

class Shoot : public Sprite {
	float shoot_angle;
public:
	Shoot(Ship s) {
		transform.x = s.transform.x;
		transform.y = s.transform.y;
		transform.h = 5;
		transform.w = 5;
		shoot_angle = s.Angle();
		objectID = ObjectID::SHOOT;
	}
	void Movement() { //Movimiento de la nave segun su angulo.
		float A = cos(shoot_angle*PI / 180);
		float B = sin(shoot_angle*PI / 180);
		transform.x += (B * 10);
		transform.y -= (A * 10);
	}
	
	virtual void Draw() { R.Push(objectID, transform); };
};