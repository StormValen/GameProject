#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"

using namespace Logger;

GameScene::GameScene(void){
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	ast.x = 100;
	ast.y = 100;
	ast.dir = 0;
	player.image = { {300,200, 20, 20}, ObjectID::PLAYER };
	ast.asteroid_image = { {ast.x, ast.y,50,50},ObjectID::MIDDLE_AST };
	ast.velocity = 1;
	m_score = 0;
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
		ast.RandomDir();
	}
	ast.asteroid_image = { { ast.x, ast.y,50,50 },ObjectID::MIDDLE_AST };
	ast.Movement();
	std::cout << ast.x << std::endl;
}

void GameScene::Draw(void) {
	m_background.Draw();
	player.image.Draw();
	ast.asteroid_image.Draw();

	GUI::DrawTextSolid<FontID::ASTEROIDS>("score: " + std::to_string(m_score),
	{ W.GetWidth() >> 2, int(W.GetHeight()*.9f), 1, 1 },
	{ 255, 255, 255 });
}