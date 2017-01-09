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
	m_background2.transform = { 0, 0, W.GetWidth(), W.GetHeight() };
	m_background2.objectID = ObjectID::BG_01;
	m_background3.transform = { 0, 0, W.GetWidth(), W.GetHeight() };
	m_background3.objectID = ObjectID::BG_02;
	m_score = 0;
	player_life = num_ovnis = ovnis_velocity = increment_ovnis = -1; //-1 simboliza que aun no se ha asignado ningun dato de XML.
	top[0] = 30000;
	top[1] = 75;
	top[2] = 100;
	top[3] = 50;
	pause = false;
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

	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {
		pause = !pause;
	}

	if (pause == true) {
		if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
			mouseCoords = IM.GetMouseCoords();
			if (mouseCoords.x < 360 && mouseCoords.x > 240 && mouseCoords.y < 351 && mouseCoords.y > 288)SetState<SceneState::EXIT>();
		}
	}
	
	if (pause == false) {
		if (player_life != 0) {
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
			}

			if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
				AddSHOOT();
			}

			if (IM.IsKeyDown<KEY_BUTTON_LALT>()) {
				ship.Hyperespacio();
			}


			//CONTROLES NAVE
			if (IM.IsKeyHold<KEY_BUTTON_UP>()) {
				if (frames_ship >= top[2]) {
					ship.Movement();
					frames_ship = 0;
				}
			}

			if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
				if (frames_ship >= top[3]) {
					ship.RotateRight();
					frames_ship = 0;
				}
			}
			if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
				if (frames_ship >= top[3]) {
					ship.RotateLeft();
					frames_ship = 0;
				}
			}

			if (frequencia == top[0]) {
				AddAST();
				frequencia = 0;
			}

			if (frames >= top[1]) {
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
			frames++; frames_ship++; frequencia++; //Actualizacion de las variables temporales frames.
		}
		else {

			if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
				SM.SetCurScene<MenuScene>();
				if (player_life <= 0) { //Cuando el jugador se queda sin vidas , se limpian todas las variables para que no carguen cosas erroneas en partidas posteriores.
					player_life = num_ovnis = ovnis_velocity = increment_ovnis = -1;
					Asts.clear();
					m_score = 0;
					ship.ship_angle = 0.0;
					LevelScene::param.clear();
				}
			}
			if (IM.IsKeyDown<KEY_BUTTON_S>()) {
				Ranking::Player aPlayer;

				cout << "Enter your name: ";
				//cin >> aPlayer.playerName;
				aPlayer.playerName = "sdsfsd";
				aPlayer.playerScore = m_score;

				rkg.ReadFile();
				rkg.OrderArray(aPlayer);
				rkg.WriteFile();

				cout << "RANKING - TOP 10" << endl;
				for (int i = 0; i < 10; i++) {
					cout << i + 1 << "--" << rkg.ranking[i].playerName << "-";
					cout << rkg.ranking[i].playerScore << endl;
				}
			}

			if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
				mouseCoords = IM.GetMouseCoords();
				if (mouseCoords.x < 360 && mouseCoords.x > 240 && mouseCoords.y < 351 && mouseCoords.y > 288)SetState<SceneState::EXIT>();
			}
		}
	}	
}

void GameScene::Draw(void) {
	if (player_life != 0) {
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

		if (pause == true) {
			m_background3.Draw();

			GUI::DrawTextSolid<FontID::ASTEROIDS>("pause",
			{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
			{ 255 });

			GUI::DrawTextSolid<FontID::ASTEROIDS01>("<press again to resume>",
			{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
			{ 255 });


			GUI::DrawTextSolid<FontID::ASTEROIDS>("exit",
			{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
			{ 255 });
		}
	}
	else {
		m_background2.Draw();

		GUI::DrawTextSolid<FontID::ASTEROIDS>(":Ranking:",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 255, 255, 255 });

		GUI::DrawTextSolid<FontID::ASTEROIDS02>("<press -s- to type your name on the console>",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
		{ 255 });

		GUI::DrawTextSolid<FontID::ASTEROIDS02>("<then press -Enter- to save your score>",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 255 });

		GUI::DrawTextSolid<FontID::ASTEROIDS>("score: " + std::to_string(m_score),
		{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
		{ 255 });

		GUI::DrawTextSolid<FontID::ASTEROIDS01>("<Press -ENTER- to continue>",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
		{ 255 });

		GUI::DrawTextSolid<FontID::ASTEROIDS>("exit",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
		{ 255 });
	}
}