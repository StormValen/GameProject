#pragma once
#include "Scene.hh"
#include "Ship.hh"

class GameScene : public Scene {
public:
	explicit GameScene(void);
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	int m_score;
	Ship ship;
	int player_life;
	int num_ovnis;
	float ovnis_velocity;
	int increment_ovnis;
	float asteroids_velocity = 1;
};