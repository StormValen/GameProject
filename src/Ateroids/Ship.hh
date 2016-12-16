#pragma once
#include <SDL.h>
#include <iostream>
#include "GameScene.hh"

using namespace std;


class Ship {
	// SDL_Point contiene las variables x e y en SDL
	SDL_Point *ship = NULL;

	SDL_Point prevPos;
	SDL_Point pos;
	
	float player_vel = 0.0;
	float player_angl = 0.0;
	float vel[2]; // Static, Movement
	bool alive = true;

	float cosA = 0.0;
	float sinA = 0.0;

public:	
	/** He creado 3 puntos de colisión para que al chocar con los
	* asteroides sea más real, por eso he usado el Rect de SDL.
	*/
	SDL_Rect *colPoints = NULL;
	Sprite image;
	Sprite player;
	int rot = NONE;

	enum rotateDir { LEFT = 1, RIGHT = 2, NONE = 0 };

	// Constructor con las posiciones iniciales
	Ship() : prevPos({ 300,200 }), pos({ 300,200 })
{
	ship = new SDL_Point[5];
	colPoints = new SDL_Rect[3];

	vel[0] = 0.0;
	vel[1] = 0.0;

	this->trace();
}

	~Ship()
{
	delete ship;
	delete colPoints;
}
	// Recoger la velocidad
	float* getVel() { return vel; }
	// Recoger la posicion
	SDL_Point getPos() { return pos; }
	// Esta vivo
	bool isAlive() { return alive; }
	// Volver a la vida
	void setAlive(const bool& val) { alive = val; }
	// Rotar sin hace cambios muy agudos
	void rotate(const int& val) { rot = val; }

	//void fire();


	// Path of the player and collision points
	void trace()
	{

	cosA = cos(player_angl);
	sinA = sin(player_angl);

	ship[0] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y - pos.y) + pos.y) };

	ship[1] = { int(cosA * (pos.x + 10 - pos.x) - sinA * (pos.y - 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 10 - pos.x) + cosA * (pos.y - 10 - pos.y) + pos.y) };

	ship[2] = { int(cosA * (pos.x + 5 - pos.x) - sinA * (pos.y - pos.y) + pos.x),
		int(sinA * (pos.x + 5 - pos.x) + cosA * (pos.y - pos.y) + pos.y) };

	ship[3] = { int(cosA * (pos.x + 10 - pos.x) - sinA * (pos.y + 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 10 - pos.x) + cosA * (pos.y + 10 - pos.y) + pos.y) };

	ship[4] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y - pos.y) + pos.y) };

	colPoints[0] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y - 0 - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y - 0 - pos.y) + pos.y),2,2 };

	colPoints[1] = { int(cosA * (pos.x + 10 - pos.x) - sinA * (pos.y - 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 10 - pos.x) + cosA * (pos.y - 10 - pos.y) + pos.y),2,2 };

	colPoints[2] = { int(cosA * (pos.x + 10 - pos.x) - sinA * (pos.y + 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 10 - pos.x) + cosA * (pos.y + 10 - pos.y) + pos.y),2,2 };
	}

	// Si se acaba de morir
	void deadAnim()
	{
	vel[0] = 0;
	vel[1] = 0;
	}

	// No se si deberia ir aqui o actualizarse en el GameScene.cc
	void updatePosition(const float& dt)
	{
		if (alive)
		{
			player_vel += 1;

			if (player_vel > 5)
			{
				player_vel = 5;
			}
			vel[0] += player_vel * cosA;
			vel[1] += player_vel * sinA;
		}
		else
		{
			player_vel = 0;
		}

		switch (rot) {
		case LEFT:
		{
			player_vel -= 0.175;
			break;
		}
		case RIGHT:
		{
			player_vel += 0.175;
			break;
		}
		case NONE:
		{
			break;
		}
		}

		// Actualizar las posiciones
		pos.x = prevPos.x - vel[0] * dt;
		pos.y = prevPos.y - vel[1] * dt;

		if (pos.x > 600) pos.x -= 600;
		
		if (pos.x < 0) pos.x += 600;

		if (pos.y > 400) pos.y -= 400;

		if (pos.y < 0) pos.y += 400;

		// Actualizar la posicion anterior
		prevPos.x = pos.x;
		prevPos.y = pos.y;
	}

	// El movimiento por teclado se tiene que hacer aqui o en otro sitio?
	// No entiendo muy bien como funciona esto en SDL 
	void movementShip()
	{
		if (alive == true)
		{
			
		}
	}
};