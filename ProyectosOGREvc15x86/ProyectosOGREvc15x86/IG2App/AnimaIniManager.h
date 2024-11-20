#pragma once
#include <OgreSceneManager.h>
#include "IG2ApplicationContext.h"
#include <vector>
using namespace Ogre;
class IG2App;

class AnimaIniManager : public OgreBites::InputListener
{
public:
	AnimaIniManager(IG2App* _app, SceneNode* sn, SceneManager* sm);
	~AnimaIniManager();
	void clear();
private:
	IG2App* app;
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	std::vector<Entity*> entities;
};

