#pragma once
#include "Mob.h"
#include "IG2App.h"
class Enemy: public Mob
{
public:
	Enemy(Vector3 initPos, SceneNode* node, SceneManager* sceneMng,string meshName, bool** arr, IG2App*);
	virtual ~Enemy();
	virtual void init();
	virtual void takeDamage() {};
	virtual void calculateDirection();
	void frameRendered(const Ogre::FrameEvent& evt) = 0;
	bool EstaEnCruce();

protected:

	Ogre::SceneNode* mLightNode;
};

