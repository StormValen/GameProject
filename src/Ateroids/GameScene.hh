#pragma once
#include "Scene.hh"
#include "Asteroid.hh"
#include <vector>

struct Player {
	int player_x, player_y;
	int player_vel, player_angl;
	Sprite image;
};

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
			Asteroid nuevo_asteroide;
			Asts.push_back(nuevo_asteroide);
		}
	}
	void DeleteAST() {
		Asts.pop_back();
	}
private:
	Sprite m_background;
	int m_score;
	int limit;
	Player player;
	std::vector<Asteroid> Asts;
	int player_life;
	int num_ovnis;
	float ovnis_velocity;
	int increment_ovnis;
	float asteroids_velocity = 1;
	int frames;
};