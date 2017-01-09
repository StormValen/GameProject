#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"

using namespace Logger;

GameScene::GameScene(void){
	std::cout << ">GameScene created" << std::endl;
	m_background.transform = { 0, 0, W.GetWidth(), W.GetHeight() }; //Fondo de juego.
	m_background.objectID = ObjectID::BG_00;
	m_background2.transform = { 0, 0, W.GetWidth(), W.GetHeight() }; //Fondo de ranking.
	m_background2.objectID = ObjectID::BG_01;
	m_background3.transform = { 0, 0, W.GetWidth(), W.GetHeight() }; //Fondo de pause.
	m_background3.objectID = ObjectID::BG_02;

	m_score = 0;
	progLevel = 1;
	topScoreToChangeVel = 1000;
	player_life = starterEnem = enemIncrement = velocidadNivel = -1; //-1 simboliza que aun no se ha asignado ningun dato de XML.
	pause = false;
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	if (player_life == -1)player_life = LevelScene::param[0];	//Asignacion de las variables leidas de XML.
	if (starterEnem == -1)starterEnem = LevelScene::param[1];
	if (enemIncrement == -1)enemIncrement = LevelScene::param[2];
	if (velocidadNivel == -1)velocidadNivel = LevelScene::param[3];

	static MouseCoords mouseCoords(0, 0);

	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) { 
		if (pause == true) {
		pause = false;
		}
		else if (pause == false) {
			pause = true;
		}
	} //Escape activa o desactiva el menu de pause.
	
	if (pause == true) {//PAUSE LOOP
		if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
			mouseCoords = IM.GetMouseCoords();
			if (mouseCoords.x < 360 && mouseCoords.x > 240 && mouseCoords.y < 351 && mouseCoords.y > 288)SetState<SceneState::EXIT>();
		}
	}
	
	if (pause == false) {//GAME LOOP
		if (player_life != 0) {//GAME LOOP (ALIVE)
			
			//HABILIDADES
			if (IM.IsKeyDown<KEY_BUTTON_TAB>())AddSHOOT();
			if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>())AddSHOOT();
			if (IM.IsKeyDown<KEY_BUTTON_LALT>())ship.Hyperespacio();

			//CONTROLES NAVE
			if (IM.IsKeyHold<KEY_BUTTON_UP>())ship.Movement();
			if (IM.IsKeyHold<KEY_BUTTON_RIGHT>())ship.RotateRight();
			if (IM.IsKeyHold<KEY_BUTTON_LEFT>())ship.RotateLeft();

			//MOVIMIENTO OBJETOS
			for (int i = 0; i < Asts.size(); i++) {
				Asts[i].Movement();
				Asts[i].Update();
			}
			for (int i = 0; i < Shoots.size(); i++) {
				Shoots[i].Movement();
				OutSHOOT();
			}

			//COLISIONES
			ColisionSHIP();
			ColisionSHOOT();

			//ACTUALIZACION DL ESTADO DEL JUEGO (VELOCIDAD POR PUNTUACION & OLEADA COMPLETADA)
			if (m_score > topScoreToChangeVel) {
				for (int i = 0; i < Asts.size(); i++) {
					Asts[i].velocity++;
				}
				topScoreToChangeVel += 1000;
			}

			if (Asts.empty()) {
				std::cout << ">Level clear - Level "<< progLevel << " loaded" << std::endl;
				int A = starterEnem + enemIncrement*progLevel;
				for (int i = 0; i < A; i++) {
					AddAST();
				}
				progLevel++;
			}

		}
		else {//GAME LOOP (DEAD)

			if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
				SM.SetCurScene<MenuScene>();
				if (player_life <= 0) { 
					player_life = starterEnem = enemIncrement = velocidadNivel = -1;
					Asts.clear();
					m_score = 0;
					progLevel = 1;
					ship.ship_angle = 0.0;
					LevelScene::param.clear();
					//Cuando el jugador se queda sin vidas , 
					//se limpian todas las variables para que no carguen cosas erroneas en partidas posteriores.
				}
			}

			if (IM.IsKeyDown<KEY_BUTTON_S>()) {
				Ranking::Player aPlayer;//Objeto que almacena el nombre y score del jugador de la partida actual.

				cout << "Enter your name: ";
				cin >> aPlayer.playerName;//Asignacion de variables.
				aPlayer.playerScore = m_score;

				rkg.ReadFile();//Lee fichero y carga datos en el objeto ranking.
				rkg.OrderArray(aPlayer);//Ordena los valores e introduce el nuevo score (orden por bubble sort).
				rkg.WriteFile();//Sobreescribe el contenido del fichero binario con el nuevo contenido del objeto ranking.

				cout << "RANKING - TOP 10" << endl;
				for (int i = 0; i < 10; i++) {//Impresion del ranking.
					cout << i + 1 << "--" << rkg.ranking[i].playerName << "-";
					cout << rkg.ranking[i].playerScore << endl;
				}
			}

			if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {//Boton EXIT del ranking.
				mouseCoords = IM.GetMouseCoords();
				if (mouseCoords.x < 360 && mouseCoords.x > 240 && mouseCoords.y < 351 && mouseCoords.y > 288)SetState<SceneState::EXIT>();
			}
		}
	}	
}

void GameScene::Draw(void) {
	if (player_life != 0) {//GAME LOOP (ALIVE)
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

		if (pause == true) {// PAUSE LOOP
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
	else {//GAME LOOP (DEAD)
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