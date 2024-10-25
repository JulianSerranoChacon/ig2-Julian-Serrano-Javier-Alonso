#pragma once
#include "IG2Object.h"
#include "Ogre.h"

using uint = unsigned int;
class Heroe : public IG2Object
{
public:
	Heroe() {};
	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	virtual void init();
	void takeDamage();
	void ChangeDirection(Vector3 newDir);
private:
	uint numVidas;
	Vector3 dirAct;
	Vector3 dirNueva;
};

