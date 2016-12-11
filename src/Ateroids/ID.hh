#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	PLAYER, GREAT_AST, MIDDLE_AST, LITTLE_AST, //Tipos de asteroides
	SHOOT,
	BG_00  // Background IDs
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int { 
	ARIAL,
	ASTEROIDS,
	FACTORY, 
	MAX 
};