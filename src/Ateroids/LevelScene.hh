#pragma once
#include "Scene.hh"

// GameScene class with the main gameplay mode
class LevelScene : public Scene {
public:
	explicit LevelScene();
	~LevelScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	std::string name;
};