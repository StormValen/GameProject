#pragma once
#include "Scene.hh"
#include "Asteroid.hh"
#include "Ship.hh"
#include <vector>


class GameScene : public Scene {
public:
	explicit GameScene(void);
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void AddAST() {
			Asteroid nuevo_asteroide(0);
			Asts.push_back(nuevo_asteroide);	
	}
	void DeleteAST(int pos) {
		int D = (Asts[pos].dim)+1;
		if (pos == 0) {
			Asts.erase(Asts.begin());
		}
		else {
			Asts.erase(Asts.begin() + (pos - 1));
		}
		if (D < 3) {
			for (int i = 0; i < 2; i++) {
					Asteroid nuevo_asteroide(D); 
					Asts.push_back(nuevo_asteroide);
			}
		}
		switch (D-1) {
		case 0:
			m_score += 20;
			break;
		case 1:
			m_score += 50;
			break;
		case 2:
			m_score += 100;
			break;
		default: 
			break;
		}
	}
private:
	Sprite m_background;
	int m_score;
	Ship ship;
	std::vector<Asteroid> Asts;

	int player_life;	//XML
	int num_ovnis;		//XML
	float ovnis_velocity;  //XML
	int increment_ovnis;	//XML
	
	int frequencia;
	int frames; // CONTROLA LA FREQUENCIA A LA QUE SE ACTUALIZA LA POSICION DE LOS ASTEROIDES, POR DEFECTO LA VELOCIDAD 1 (MINIMA ES DEMASIADO ALTA)
	int frames_ship;	//CONTROLA LA FREQUENCIA A LA QUE SE ACTUALIZA LA POSICION DE LA NAVE (TAMBIEN LA MINIMA ES DEMASIADO ALTA).
};