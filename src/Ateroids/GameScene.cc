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
	top[0] = 3000;
	top[1] = 25;
	top[2] = 50;
	top[3] = 10;
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

	//CONTROL VELOCIDADES
	if (IM.IsKeyDown<KEY_BUTTON_U>()) {//Disminuir velocidad de rotacion de la nave
		top[3] += 1;
		std::cout << top[3] << std::endl;
	}
	if (IM.IsKeyDown<KEY_BUTTON_H>()) {//Augmentar velocidad de rotacion de la nave 
		top[3] -= 1;
		std::cout << top[3] << std::endl;
	}
	if (IM.IsKeyDown<KEY_BUTTON_I>()) {//Augmentar velocidad de aparicion asteroides
		top[0] += 200;
		std::cout << top[0] << std::endl;
	}
	if (IM.IsKeyDown<KEY_BUTTON_J>()) {//Disminuir velocidad de aparicion asteroides
		top[0] -= 200;
		std::cout << top[0] << std::endl;
	}
	if (IM.IsKeyDown<KEY_BUTTON_O>()) {//Disminuir velocidad de movimiento de asteroides y disparos
		top[1] += 1;
		std::cout << top[1] << std::endl;
	}
	if (IM.IsKeyDown<KEY_BUTTON_K>()) {//Augmentar velocidad de movimiento de asteroides y disparos
		top[1] -= 1;
		std::cout << top[1] << std::endl;
	}
	if (IM.IsKeyDown<KEY_BUTTON_P>()) {//Disminuir velocidad de movimiento de la nave
		top[2] += 5;
		std::cout << top[2] << std::endl;

	}
	if (IM.IsKeyDown<KEY_BUTTON_L>()) {//Augmentar velocidad de movimiento de la nave
		top[2] -= 5;
		std::cout << top[2] << std::endl;
	}


	//HABILIDADES
	if (IM.IsKeyDown<KEY_BUTTON_TAB>()) { 
		AddSHOOT();
		std::cout << ">Shoot" << std::endl;
	}

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		AddSHOOT();
		std::cout << ">Shoot" << std::endl;
	}

	if (IM.IsKeyDown<KEY_BUTTON_LALT>()) {
		ship.Hyperespacio();
		std::cout << ">Hyperspace" << std::endl;
	}


	//CONTROLES NAVE
	if (IM.IsKeyHold<KEY_BUTTON_UP>()) {
		if (frames_ship >= top[2]) { //TEMPORAL -> l update se actualiza demasiado rapido.
			ship.Movement();
			frames_ship = 0;
		}
	}

	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
		if (frames_ship >= top[3]) { //TEMPORAL -> l update se actualiza demasiado rapido.
			ship.RotateRight();
			frames_ship = 0;
		}
	}
	if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
		if (frames_ship >= top[3]) { //TEMPORAL -> l update se actualiza demasiado rapido.
			ship.RotateLeft();
			frames_ship = 0;
		}
	}

	if (frequencia == top[0]) { //TEMPORAL -> l update se actualiza demasiado rapido.
		AddAST();
		frequencia = 0;
		std::cout << ">Asteroid created" << std::endl;
	}

	if (frames >= top[1]) { //TEMPORAL -> l update se actualiza demasiado rapido.
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