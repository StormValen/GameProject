#pragma once
#include <iostream>

//IDs usados en objetos y fuentes.
enum class ObjectID : const int {
	PLAYER, GREAT_AST, MIDDLE_AST, LITTLE_AST, //Tipos de asteroides
	SHOOT,
	BG_00,	//Fondo negro.
	BG_01   //Fondo finguras.
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

enum class FontID : int {
	ARIAL,
	ASTEROIDS,
	ASTEROIDS01,
	FACTORY, 
	MAX 
};