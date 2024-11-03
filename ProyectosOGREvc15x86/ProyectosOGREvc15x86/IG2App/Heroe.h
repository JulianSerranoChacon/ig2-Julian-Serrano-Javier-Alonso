#pragma once
#include "Mob.h"
#include "IG2App.h"
#include "Perla.h"
#include <vector>
class Heroe : public Mob
{
public:
	Heroe() {};
	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr,IG2App*);
	virtual void init();
	virtual void takeDamage();	
	virtual bool keyPressed(const OgreBites::KeyboardEvent& ev);
	void frameRendered(const Ogre::FrameEvent& evt);	
	void addPerl() { numPerls++; updateTextBox(); };
	int getPerl() { return numPerls; };

private:
	void updateTextBox();
	int numPerls;
	OgreBites::TextBox* mTextBox;
};

