#pragma once
#include "Mob.h"
#include "IG2App.h"
class Heroe : public Mob
{
public:
	Heroe() {};
	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr,IG2App*);
	virtual void init();
	virtual void takeDamage();	
	virtual bool keyPressed(const OgreBites::KeyboardEvent& ev);
};

