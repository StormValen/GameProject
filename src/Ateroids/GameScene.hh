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
		if (Asts.size() < limit) {
			Asteroid nuevo_asteroide(0);
			Asts.push_back(nuevo_asteroide);
		}
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
			m_score += 10;
			break;
		case 1:
			m_score += 5;
			break;
		case 2:
			m_score += 1;
			break;
		default: 
			break;
		}
	}
private:
	Sprite m_background;
	int m_score;
	int limit; // LEER DE XML !!!!!!!!!!!
	Ship ship;
	std::vector<Asteroid> Asts;

	int player_life;
	int num_ovnis;
	float ovnis_velocity;
	int increment_ovnis;
	float asteroids_velocity = 1;
	int frames;
	int frames_ship;
};