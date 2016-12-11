#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::ASTEROIDS>("fnt/Hyperspace.otf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
	
		R.LoadTexture < ObjectID::GREAT_AST>("gfx/gast.png");
		R.LoadTexture < ObjectID::MIDDLE_AST>("gfx/mast.png");
		R.LoadTexture < ObjectID::LITTLE_AST>("gfx/last.png");
		R.LoadTexture < ObjectID::PLAYER>("gfx/player.png");
		R.LoadTexture < ObjectID::SHOOT>("gfx/shot.png");
		R.LoadTexture<ObjectID::BG_00>("gfx/bg.jpg");
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<MenuScene>();	//FALTA A�ADIR LA ESCENA DEL JUEGO (POR CREAR)
		SM.AddScene<LevelScene>();
		SM.AddScene<GameScene>();
		SM.SetCurScene<MenuScene>();
	}
	/**
	* Runs the game specifying the window's name and dimensions
	* @tparam screenWidth Determines the window's width
	* @tparam screenHeight Determines the window's height
	* @param name Determines the window's title
	*/
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
			TM.FPSBegin(); // Calculates the time difference for deltaTime and FPS limiting purposes
#pragma region GAME_UPDATE
			switch (m_curScene->GetState()) { // Check for the state of the screen
			case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
			case SceneState::EXIT:		m_isRunning = false; break; // Triggers an end of the game looping
			case SceneState::SLEEP: default:;
			}
#pragma endregion
#pragma region GAME_DRAW
			TM.FPSEnd([&]() { // Limits the FPS rendering with a lambda function as the parameter that draws the whole game
				if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
					R.Clear();			// Clear the screen buffer
					m_curScene->Draw(); // Call the draw method of the scene
					R.Render();			// Update the screen buffer with all sprites that were pushed
				}});
#pragma endregion
		}
	}
}