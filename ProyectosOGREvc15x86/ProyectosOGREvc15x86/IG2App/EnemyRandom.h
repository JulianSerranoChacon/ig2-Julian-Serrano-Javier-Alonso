#pragma once
#include "Enemy.h"
class EnemyRandom: public Enemy
{
public:
	EnemyRandom(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App*);
	virtual ~EnemyRandom();
	virtual void init();
	virtual void takeDamage() {};
	virtual void calculateDirection();
	void frameRendered(const Ogre::FrameEvent& evt);
private:
	Vector3 chooseDir();
};

