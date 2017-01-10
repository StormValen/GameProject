#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Ranking { //Objeto que lee(de fichero binario), ordena y escribe(en fichero binario) el ranking.
public:
	typedef struct Player { //Tipo de objeto almacenado en el ranking
		string playerName;
		int playerScore;
	};

	const Player posicion = { "  ---  ",0 };	
	//Cuando es la primera vez que se crea el archivo de ranking en el pc
	//se inician las 10 posiciones con el valor predeterminado (posicion).

	Player ranking[10] = {posicion,	//Contenedor Ranking.
						  posicion,
						  posicion, 
					   	  posicion, 
						  posicion, 
						  posicion, 
						  posicion, 
						  posicion, 
						  posicion, 
						  posicion, };

	void ReadFile() { 
		ifstream fentrada("../../res/ranking/Ranking24.dat", ios::in | ios::binary); //Abre archivo
		if (fentrada.fail())cout << "<WARNING> Binary file can not be opened" << endl; //Lanza error si no se ha abierto bien.
		fentrada.read(reinterpret_cast<char *>(&ranking), sizeof(ranking)); //Lee el contenido y se almacena en el contenedor.
		fentrada.close(); //Cierra el archivo.
	}
	void WriteFile() { 
		ofstream fsalida("../../res/ranking/Ranking24.dat", ios::out | ios::binary); //Abre archivo
		if (fsalida.fail())cout << "<WARNING> Binary file can not be opened" << endl; //Lanza error si no se ha abierto bien.
		fsalida.write(reinterpret_cast<char *>(&ranking), sizeof(ranking)); //Sobreescribe el archivo con el contenido del array.
		fsalida.close(); //Cierra el archivo.
	}
	void OrderArray(Player aPlayer) { 
		Ranking::Player temporal;
		Ranking::Player temporal2;

		bool scoreSet = false;
		int counter = 0;
		while (counter < 30) { //Metodo de ordenacion del ranking (BUBBLE SORT).
			for (int i = 0; i < 9; i++) {
				int Score1 = ranking[i].playerScore;
				int Score2 = ranking[i + 1].playerScore;
				if (Score1 < Score2) {
					temporal = ranking[i + 1];
					ranking[i + 1].playerName = ranking[i].playerName;
					ranking[i + 1].playerScore = ranking[i].playerScore;
					ranking[i].playerName = temporal.playerName;
					ranking[i].playerScore = temporal.playerScore;
				}
			}
			counter++;
		}
		for (int a = 0; a < 10; a++) { //Insercion del nuevo score (SHIFT DOWN)
			if (aPlayer.playerScore > ranking[a].playerScore && scoreSet == false) {
				for (int j = 9; j >= a; j--) {
					ranking[j].playerName = ranking[j - 1].playerName;
					ranking[j].playerScore = ranking[j - 1].playerScore;
				}
				ranking[a].playerName = aPlayer.playerName;
				ranking[a].playerScore = aPlayer.playerScore;
				scoreSet = true;
			}
		}
	}
};