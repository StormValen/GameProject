#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"

using namespace Logger;

GameScene::GameScene(void){
	std::cout << ">GameScene created" << std::endl;
	m_background.transform = { 0, 0, W.GetWidth(), W.GetHeight() };
	m_background.objectID = ObjectID::BG_00;
	m_score = 0;
	player_life = num_ovnis = ovnis_velocity = increment_ovnis = -1; //-1 simboliza que aun no se ha asignado ningun dato de XML.
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	if (player_life == -1)player_life = LevelScene::param[0];	//Asignacion de las variables ledias de XML.
	if (num_ovnis == -1)num_ovnis = LevelScene::param[1];
	if (ovnis_velocity == -1)ovnis_velocity = LevelScene::param[2];
	if (increment_ovnis == -1)increment_ovnis = LevelScene::param[3];
	
	static MouseCoords mouseCoords(0, 0);
		
	if (frequencia == 3000) { //TEMPORAL -> l update se actualiza demasiado rapido.
		AddAST();
		frequencia = 0;
		std::cout << ">Asteroid created" << std::endl;
	}

	if (IM.IsKeyDown<KEY_BUTTON_TAB>()) { //Funcion TEMPORAL para destruir asteroides.
		AddSHOOT();
	}

	if (IM.IsKeyHold<KEY_BUTTON_UP>()) {
		if (frames_ship >= 50) { //TEMPORAL -> l update se actualiza demasiado rapido.
			ship.Movement();
			frames_ship = 0;
		}
	}
	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
		if (frames_ship >= 10) { //TEMPORAL -> l update se actualiza demasiado rapido.
			ship.RotateRight();
			frames_ship = 0;
		}
	}
	if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
		if (frames_ship >= 10) { //TEMPORAL -> l update se actualiza demasiado rapido.
			ship.RotateLeft();
			frames_ship = 0;
		}
	}
	if (frames >= 25) { //TEMPORAL -> l update se actualiza demasiado rapido.
		for (int i = 0; i < Asts.size(); i++) {
			Asts[i].Movement();
			Asts[i].Update();
		}
		for (int i = 0; i < Shoots.size(); i++) {
			Shoots[i].Movement();
			OutSHOOT();
		}
		frames = 0;
	}
	ColisionSHIP();
	ColisionSHOOT(); 
	frames++;frames_ship++;frequencia++; //Actualizacion de las variables temporales frames.
}

void GameScene::Draw(void) {
	m_background.Draw();
	ship.Draw();

	for (int i = 0; i < Asts.size(); i++) {
		Asts[i].Draw();
	}
	for (int i = 0; i < Shoots.size(); i++) {
		Shoots[i].Draw();
	}

	GUI::DrawTextSolid<FontID::ASTEROIDS01>("score: " + std::to_string(m_score),
	{ W.GetWidth() >> 3, int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextSolid<FontID::ASTEROIDS01>("life: " + std::to_string(player_life),
	{ W.GetWidth() >> 3, int(W.GetHeight()*.17f), 1, 1 },
	{ 255, 255, 255 });
}