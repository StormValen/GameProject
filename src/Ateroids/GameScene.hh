#pragma once
#include "Scene.hh"
#include "Asteroid.hh"
#include "Ship.hh"
#include "Shoot.hh"
#include <vector>

//Escena principal de juego.
class GameScene : public Scene {
public:
	explicit GameScene(void);
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void AddAST() {
		Asteroid nuevo_asteroide(0); //Generador de asteroides, tamaño grande.
		Asts.push_back(nuevo_asteroide); //Se añade al contenedor de la clase.
	}

	void AddSHOOT() {
		Shoot nuevo_shoot(ship);
		Shoots.push_back(nuevo_shoot);
	}

	void DeleteAST(int pos) {	//Destructor de los asteroides, (Todavia por definir) -> NO EXISTEN COLISIONES.	
		int D = (Asts[pos].dim) + 1;
		if (pos == 0)Asts.erase(Asts.begin());
		else Asts.erase(Asts.begin() + (pos));
		
		if (D < 3) {
			for (int i = 0; i < 2; i++) {
					Asteroid nuevo_asteroide(D);
					Asts.push_back(nuevo_asteroide);
			}
		}
		switch (D) {	//Sistema de puntuaciones.
		case 0:m_score += 20;break;		//Grande.
		case 1:m_score += 50;break;		//Mediano.
		case 2:m_score += 100;break;	//Pequeño.
		default: break;
		}
	}
	void Colision() {
		for (int i = 0; i < Asts.size(); i++) {
			if (Asts[i].dim == 0) {
				if (ship.transform.x > Asts[i].x && ship.transform.x < Asts[i].x + 90 && ship.transform.y > Asts[i].y && ship.transform.y < Asts[i].y + 90) {
					player_life -= 1;
					ship.transform.x = 300;
					ship.transform.y = 200;
				}
			}
			else if (Asts[i].dim == 1) {
				if (ship.transform.x > Asts[i].x && ship.transform.x < Asts[i].x + 60 && ship.transform.y > Asts[i].y && ship.transform.y < Asts[i].y + 60) {
					player_life -= 1;
					ship.transform.x = 300;
					ship.transform.y = 200;
				}
			}
			else if (Asts[i].dim == 2) {
				if (ship.transform.x > Asts[i].x && ship.transform.x < Asts[i].x + 30 && ship.transform.y > Asts[i].y && ship.transform.y < Asts[i].y + 30) {
					player_life -= 1;
					ship.transform.x = 300;
					ship.transform.y = 200;
				}
			}
		}
		if (player_life <= 0) {
			player_life = num_ovnis = ovnis_velocity = increment_ovnis = -1; //Cuando el jugador se queda sin vidas , se limpian todas las variables para que no carguen cosas erroneas en partidas posteriores.
			Asts.clear();
			m_score = 0;
			LevelScene::param.clear();
			SM.SetCurScene<MenuScene>();
		}
	}
	void ColisionSHOOT(){
		for (int i = 0; i < Asts.size(); i++) {
			for (int j = 0; j < Shoots.size(); j++) {
				if (Asts[i].dim == 0) {
					if (Shoots[i].transform.x > Asts[i].x && Shoots[i].transform.x < Asts[i].x + 90 && Shoots[i].transform.y > Asts[i].y && Shoots[i].transform.y < Asts[i].y + 90) {
						std::cout << "HIT" << std::endl;
						DeleteAST(i);
					}
				}
				else if (Asts[i].dim == 1) {
					if (Shoots[i].transform.x > Asts[i].x && Shoots[i].transform.x < Asts[i].x + 60 && Shoots[i].transform.y > Asts[i].y && Shoots[i].transform.y < Asts[i].y + 60) {
						std::cout << "HIT" << std::endl;
						DeleteAST(i);
					}
				}
				else if (Asts[i].dim == 2) {
					if (Shoots[i].transform.x > Asts[i].x && Shoots[i].transform.x < Asts[i].x + 30 && Shoots[i].transform.y > Asts[i].y && Shoots[i].transform.y < Asts[i].y + 30) {
						std::cout << "HIT" << std::endl;
						DeleteAST(i);
					}
				}
			}
		}
	}
	void DeleteSHOOT() {
		if (Shoots.size() > 1) {
			for (int i = 0; i < Shoots.size(); i++) {
				if (Shoots[i].transform.x < 0)Shoots.erase(Shoots.begin());
				if (Shoots[i].transform.x > 600)Shoots.erase(Shoots.begin());
				if (Shoots[i].transform.y < 0)Shoots.erase(Shoots.begin());
				if (Shoots[i].transform.y > 400)Shoots.erase(Shoots.begin());
			}
		}
	}
private:
	std::vector<Asteroid> Asts;	//Contenedor de los asteroides que se van creando.
	std::vector<Shoot> Shoots; //Contenedor de los disparos.
	Sprite m_background;
	Ship ship;

	int m_score; //Puntuacion de la partida, se debe guardar en un archivo externo.
	int player_life, num_ovnis, increment_ovnis; //Varibles leidas de xml segun el nivel escogido.
	float ovnis_velocity;

	//La frequencia de actualizacion del update del gameScene es damasiado alta y se llama a la funciones movimiento de cada emento demasiadas veces, por lo que se mueve muy rapido.
	//Saltarse algunas iteraciones del update es una solucion temporal, ya que en funcion de la maquina en la que se esté ejecutando el programa el update se hara mas rapido o as lento.
	int frequencia;		//TEMP
	int frames;			//TEMP
	int frames_ship;	//TEMP
};