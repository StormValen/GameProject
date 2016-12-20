#pragma once
#include "Scene.hh"

//Escena para escoger el nivel de dificultad.
class LevelScene : public Scene {
public:
	static std::vector<int> param; //Contenedor para la informacion del XML.
	explicit LevelScene();
	~LevelScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void PrintLevel(std::string s) {//Imprime los datos leidos del XMl.
		std::cout << "--------------------------" << std::endl;
		std::cout << ">" << s << " mode loaded" << std::endl;
		std::cout << "- Player Life: " << param[0] << std::endl;
		std::cout << "- Initial enemies: " << param[1] << std::endl;
		std::cout << "- Increment number: " << param[2] << std::endl;
		std::cout << "- Enemy velocity: " << param[3] << std::endl;
		std::cout << "--------------------------" << std::endl;
	}
private:
	Sprite m_background;
};