#pragma once
#include "IG2Object.h"
#include "Ogre.h"

using uint = unsigned int;
class Mob : public IG2Object
{
public:
	Mob() {};
	Mob(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr);
	virtual ~Mob();
	virtual void init();
	virtual void takeDamage() = 0;
	virtual void changeDirection(Vector3 newDir);
	virtual void walk();
	virtual bool checkDir();
protected:
	uint numVidas;
	Vector3 dirAct;
	Vector3 dirNueva;
	Vector3 myPos;
	float speed;
	bool** labArray;
};

