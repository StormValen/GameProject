#pragma once
#include "ID.hh"
#include "Renderer.hh"
#include "Transform.hh"

// Sprite class that serves as part of the Model
class Sprite {
public:
	Transform transform;
	ObjectID objectID;
	virtual void Draw() { R.Push(objectID, transform); };
};