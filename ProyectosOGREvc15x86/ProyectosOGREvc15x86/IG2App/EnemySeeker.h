#pragma once
#include "Enemy.h"
class EnemySeeker: public Enemy
{
public:
	EnemySeeker(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app);
	virtual ~EnemySeeker();
	virtual void init();
	virtual void takeDamage() {};
	virtual void calculateDirection();
	void frameRendered(const Ogre::FrameEvent& evt);
private:
	Vector3 chooseDir();
};

