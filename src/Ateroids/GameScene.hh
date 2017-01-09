#pragma once
#include "Scene.hh"
#include "Asteroid.hh"
#include "Ship.hh"
#include "Shoot.hh"
#include <vector>
#include "LevelScene.hh"
#include <iostream>
#include <fstream>
#include <string>
#include "Ranking.hh"


using namespace std;

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
		Asteroid nuevo_asteroide(0,velocidadNivel); //Generador de asteroides, tamaño grande.
		Asts.push_back(nuevo_asteroide); //Se añade al contenedor de la clase.
	}
	void DeleteAST(int pos) { //Destruye el asteroide y genera dos del nivel inferior.

		int D = (Asts[pos].dim) + 1;
		if (D < 3) {
			for (int i = 0; i < 2; i++) {
					Asteroid nuevo_asteroide(D,Asts[pos].transform.x, Asts[pos].transform.y, Asts[pos].velocity ); //Asteroides nuevos.
					Asts.push_back(nuevo_asteroide);
			}
		}
		if (pos == 0)Asts.erase(Asts.begin()); //Destruccion del asteroide contactado.
		else Asts.erase(Asts.begin() + (pos)); //
		switch (D) {	//Sistema de puntuaciones.
		case 1:m_score += 20;break;		//Grande.
		case 2:m_score += 50;break;		//Mediano.
		case 3:m_score += 100;break;	//Pequeño.
		default: break;
		}
	}
	void AddSHOOT() {
		Shoot nuevo_shoot(ship); //Generado de Disparos.
		Shoots.push_back(nuevo_shoot); //Se añade al contenedor de disparos.
	}
	void DeleteSHOOT(int pos) { //Destructor de disparos.
		if (pos == 0)Shoots.erase(Shoots.begin());
		else Shoots.erase(Shoots.begin() + (pos));
	}
	void OutSHOOT() { //Comprovacion si los disparon han salido de los limites de la pantalla.
		if (Shoots.size() > 1) {
			for (int i = 0; i < Shoots.size(); i++) {
				if (Shoots[i].transform.x < 0)Shoots.erase(Shoots.begin());
				if (Shoots[i].transform.x > 600)Shoots.erase(Shoots.begin());
				if (Shoots[i].transform.y < 0)Shoots.erase(Shoots.begin());
				if (Shoots[i].transform.y > 400)Shoots.erase(Shoots.begin());
			}
		}
	}
	void ColisionSHIP() {
		for (int i = 0; i < Asts.size(); i++) {
			if (Asts[i].dim == 0) { //Recolocacion de la nave cuando ha colisionado con un asteroide grande.
				if (ship.transform.x > Asts[i].x && ship.transform.x < Asts[i].x + 90 && ship.transform.y > Asts[i].y && ship.transform.y < Asts[i].y + 90) {
					player_life -= 1; 
					ship.transform.x = 300;
					ship.transform.y = 200;	
				}
			}
			else if (Asts[i].dim == 1) { //Recolocacion de la nave cuando ha colisionado con un asteroide mediano.
				if (ship.transform.x > Asts[i].x && ship.transform.x < Asts[i].x + 60 && ship.transform.y > Asts[i].y && ship.transform.y < Asts[i].y + 60) {
					player_life -= 1;
					ship.transform.x = 300;
					ship.transform.y = 200;
				}
			}
			else if (Asts[i].dim == 2) { //Recolocacion de la nave cuando ha colisionado con un asteroide pequeño.
				if (ship.transform.x > Asts[i].x && ship.transform.x < Asts[i].x + 30 && ship.transform.y > Asts[i].y && ship.transform.y < Asts[i].y + 30) {
					player_life -= 1;
					ship.transform.x = 300;
					ship.transform.y = 200;
				}
			}
		}
	}
	void ColisionSHOOT(){
		std::vector<int> astsToDelete;
		std::vector<int> shootsToDelete;
		for (int i = 0; i < Asts.size(); i++) {
			for (int j = 0; j < Shoots.size(); j++) {
				if (Asts[i].dim == 0) {	//Comprovacion si los disparos chocan con asteroides grandes.
					if (Shoots[j].transform.x > Asts[i].x && Shoots[j].transform.x < Asts[i].x + 90 && Shoots[j].transform.y > Asts[i].y && Shoots[j].transform.y < Asts[i].y + 90) {
						DeleteAST(i);
						DeleteSHOOT(j);
						//astsToDelete.push_back(i);
						//shootsToDelete.push_back(j);
					}
				}
				else if (Asts[i].dim == 1) { //Comprovacion si los disparos chocan con asteroides medianos.
					if (Shoots[j].transform.x > Asts[i].x && Shoots[j].transform.x < Asts[i].x + 60 && Shoots[j].transform.y > Asts[i].y && Shoots[j].transform.y < Asts[i].y + 60) {
						DeleteAST(i);
						DeleteSHOOT(j);
						//astsToDelete.push_back(i);
						//shootsToDelete.push_back(j);
					}
				}
				else if (Asts[i].dim == 2) { //Comprovacion si los disparos chocan con asteroides pequeños.
					if (Shoots[j].transform.x > Asts[i].x && Shoots[j].transform.x < Asts[i].x + 30 && Shoots[j].transform.y > Asts[i].y && Shoots[j].transform.y < Asts[i].y + 30) {
						DeleteAST(i);
						DeleteSHOOT(j);
						//astsToDelete.push_back(i);
						//shootsToDelete.push_back(j);
					}
				}
			}
		}

		/*for (int i = 0; i < shootsToDelete.size(); i++) {
			DeleteSHOOT(shootsToDelete[i]);
		}
		for (int i = 0; i < astsToDelete.size(); i++) {
			DeleteAST(astsToDelete[i]);
		}
		astsToDelete.clear();
		shootsToDelete.clear();*/
	}

private:
	int m_score; //Puntuacion de la partida.
	std::vector<Asteroid> Asts;	//Contenedor de los asteroides que se van creando.
	std::vector<Shoot> Shoots; //Contenedor de los disparos.

	Sprite m_background, m_background2, m_background3;	//3 backgrounds usados en el GameScene - game, pause y ranking.
	Ship ship;	//Objeto nave.
	Ranking rkg; //Objeto ranking
	//El objeto ranking se sobreescribe cada vez que se guarda partida, ya que es un array estatico y no es posible 
	//simplemente añadir una nueva posicion.

	int player_life, starterEnem, velocidadNivel, enemIncrement, progLevel, topScoreToChangeVel; //Varibles leidas de xml segun el nivel escogido.
	bool pause; //Variable que controla si el pause esta activo.
};