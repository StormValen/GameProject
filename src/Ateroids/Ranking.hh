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

	Player posicion1 = { "  ---  ",0 };
	Player posicion2 = { "  ---  ",0 };
	Player posicion3 = { "  ---  ",0 };
	Player posicion4 = { "  ---  ",0 };
	Player posicion5 = { "  ---  ",0 };
	Player posicion6 = { "  ---  ",0 };
	Player posicion7 = { "  ---  ",0 };
	Player posicion8 = { "  ---  ",0 };
	Player posicion9 = { "  ---  ",0 };
	Player posicion10 = { "  ---  ",0 };

	Player ranking[10] = { posicion1,
						   posicion2,
						   posicion3,
						   posicion4,
						   posicion5,
						   posicion6,
						   posicion7,	
						   posicion8,
						   posicion9,
						   posicion10 };

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