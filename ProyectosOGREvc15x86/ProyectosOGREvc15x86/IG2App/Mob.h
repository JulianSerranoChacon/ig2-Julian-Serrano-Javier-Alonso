#pragma once
#include "IG2Object.h"
#include "Ogre.h"

using uint = unsigned int;
class Mob : public IG2Object
{
public:
	Mob() {};
	Mob(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr, float _speed);
	virtual ~Mob();
	virtual void init() = 0;
	virtual void takeDamage() = 0;
	virtual void changeDirection(Vector3 newDir);
	virtual void walk();
	virtual bool checkDir();
	virtual bool checkWallCollision(Vector3);
	void frameRendered(const Ogre::FrameEvent& evt);
	std::vector<Vector3> getDirections();
protected:
	float speed;
	uint numVidas;
	Vector3 dirAct;
	Vector3 dirNueva;
	double PosX;
	double PosZ;	
	bool** labArray;
};

