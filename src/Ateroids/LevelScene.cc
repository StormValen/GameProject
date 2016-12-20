#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "LevelScene.hh"
#include "MenuScene.hh"
#include "XML.hh"
#include "GameScene.hh"
using namespace Logger;


std::vector<int> LevelScene::param;

LevelScene::LevelScene(void) {
	m_background.transform = { 0, 0, W.GetWidth(), W.GetHeight() };
	m_background.objectID = ObjectID::BG_01;
}

LevelScene::~LevelScene(void) {
}

void LevelScene::OnEntry(void) {
}

void LevelScene::OnExit(void) {
}

void LevelScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
		//EASY
		if (mouseCoords.x < 370 && mouseCoords.x > 224 && mouseCoords.y < 186 && mouseCoords.y > 131) {
			Xml("easyMode.xml");
			PrintLevel("Easy");
			SM.SetCurScene<GameScene>();
		}
		//MEDIUM
		if (mouseCoords.x < 397 && mouseCoords.x > 199 && mouseCoords.y < 269 && mouseCoords.y > 216) {
			Xml("mediumMode.xml");
			PrintLevel("Medium");
			SM.SetCurScene<GameScene>();
		}
		//HARD
		if (mouseCoords.x < 370 && mouseCoords.x > 224 && mouseCoords.y < 351 && mouseCoords.y > 293) {
			Xml("hardMode.xml");
			PrintLevel("Hard");
			SM.SetCurScene<GameScene>();
		}
	}
}

void LevelScene::Draw(void) {
	m_background.Draw();

	GUI::DrawTextSolid<FontID::ASTEROIDS>(":dificulty:",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextSolid<FontID::ASTEROIDS>("easy",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 255 });

	GUI::DrawTextSolid<FontID::ASTEROIDS>("medium",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	{ 255 });

	GUI::DrawTextSolid<FontID::ASTEROIDS>("hard",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
	{ 255 });
}