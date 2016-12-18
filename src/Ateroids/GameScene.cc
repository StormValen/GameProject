#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"
#include "Ship.hh"

using namespace Logger;

GameScene::GameScene(void){
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	player.image = { { 300,200, 20, 20 }, ObjectID::PLAYER };
	m_score = 0;
	limit = 5;
	//ship.image = { {300,200, 20, 20}, ObjectID::PLAYER };
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
		AddAST();
	}
	if (IM.IsKeyDown<KEY_BUTTON_LCTRL>()) {
		DeleteAST(0);
	}
	if (frames >= 20) {
		for (int i = 0; i < Asts.size(); i++) {
			Asts[i].Movement();
			Asts[i].Update();
		}
		frames = 0;
	}
	frames++;
}

void GameScene::Draw(void) {
	m_background.Draw();
	player.image.Draw();
	//ship.image.Draw();

	for (int i = 0; i < Asts.size(); i++) {
		Asts[i].asteroid_image.Draw();
	}

	GUI::DrawTextSolid<FontID::ASTEROIDS>("score: " + std::to_string(m_score),
	{ W.GetWidth() >> 2, int(W.GetHeight()*.9f), 1, 1 },
	{ 255, 255, 255 });
}