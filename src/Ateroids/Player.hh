#pragma once
#include "InputManager.hh"
#include "Sprite.hh"
#include "Transform.hh"
#include "Sprite.hh"

class Player {
	int x, y, angle;
	int velocity;
	Sprite player;
	//Sprite player = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::PLAYER };;
public:
	Player(){

	}
	~Player() {

	}
	void Move(int, int, int);
	void Rotate(int);
	void Update();
	void Draw();
};

void Player::Rotate(int angle) {
	//Hace rotar el sprite player segun el angulo / velocidad de rotacion.
}

void Player::Move(int x, int y, int velocity) {
	//Mueve el jugador en la direccion a la que apunta la nave, algoritmo en x/y por la velocidad.
}