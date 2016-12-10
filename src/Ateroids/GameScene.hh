#pragma once

#include "Sprite.hh"
#include "Scene.hh"
#include "InputManager.hh"


class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	int m_score{ 0 };
};