#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"

using namespace Logger;

GameScene::GameScene(void){
	m_background.transform = { 0, 0, W.GetWidth(), W.GetHeight() };
	m_background.objectID = ObjectID::BG_00;
	m_score = 0;
	limit = 5;
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

	if (IM.IsKeyHold<KEY_BUTTON_UP>()) {
		if (frames_ship >= 50) {
			ship.Movement();
			frames_ship = 0;
		}
	}
	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
		if (frames_ship >= 50) {
			ship.RotateRight();
			frames_ship = 0;
		}
	}
	if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
		if (frames_ship >= 50) {
			ship.RotateLeft();
			frames_ship = 0;
		}
	}
	
	if (frames >= 100) {
		for (int i = 0; i < Asts.size(); i++) {
			Asts[i].Movement();
			Asts[i].Update();
		}
		frames = 0;
	}
	frames++;
	frames_ship++;
}

void GameScene::Draw(void) {
	m_background.Draw();
	ship.Draw();
	

	for (int i = 0; i < Asts.size(); i++) {
		Asts[i].Draw();
	}

	GUI::DrawTextSolid<FontID::ASTEROIDS>("score: " + std::to_string(m_score),
	{ W.GetWidth() >> 2, int(W.GetHeight()*.9f), 1, 1 },
	{ 255, 255, 255 });
}