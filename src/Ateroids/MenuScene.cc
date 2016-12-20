#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "LevelScene.hh"
using namespace Logger;

MenuScene::MenuScene(void) {
	m_background.transform = { 0, 0, W.GetWidth(), W.GetHeight() };
	m_background.objectID = ObjectID::BG_01;
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
		if (mouseCoords.x < 360 && mouseCoords.x > 240 && mouseCoords.y < 351 && mouseCoords.y > 288)SetState<SceneState::EXIT>();
		if (mouseCoords.x < 360 && mouseCoords.x > 240 && mouseCoords.y < 272 && mouseCoords.y > 209)SM.SetCurScene<LevelScene>();
	}
}

void MenuScene::Draw(void) {
	m_background.Draw();

	GUI::DrawTextSolid<FontID::ASTEROIDS>(":asteroids:",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 }); 

	GUI::DrawTextSolid<FontID::ASTEROIDS>("play",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	{ 255 });

	GUI::DrawTextSolid<FontID::ASTEROIDS>("exit",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
	{ 255 });
}