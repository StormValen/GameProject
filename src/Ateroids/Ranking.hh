#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Ranking {
public:
	typedef struct Player { 
		string playerName;
		int playerScore;
	};

	const Player posicion = { "  ---  ",0 };

	Player ranking[10] = {posicion,
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
		ifstream fentrada("../../res/ranking/Ranking24.dat", ios::in | ios::binary);
		if (fentrada.fail())cout << "<WARNING> Binary file can not be opened" << endl;
		fentrada.read(reinterpret_cast<char *>(&ranking), sizeof(ranking));
		fentrada.close();
	}
	void WriteFile() {
		ofstream fsalida("../../res/ranking/Ranking24.dat", ios::out | ios::binary);
		if (fsalida.fail())cout << "<WARNING> Binary file can not be opened" << endl;
		fsalida.write(reinterpret_cast<char *>(&ranking), sizeof(ranking));
		fsalida.close();
	}
	void OrderArray(Player aPlayer) {
		Ranking::Player temporal;
		Ranking::Player temporal2;

		bool scoreSet = false;
		int counter = 0;
		while (counter < 30) {
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
		for (int a = 0; a < 10; a++) {
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