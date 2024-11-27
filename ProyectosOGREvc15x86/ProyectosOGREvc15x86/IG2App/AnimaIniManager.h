#pragma once
#include <OgreSceneManager.h>
#include "IG2ApplicationContext.h"
#include "OgreAnimation.h"
#include <vector>
using namespace Ogre;
class IG2App;

class AnimaIniManager : public OgreBites::InputListener
{
public:
	AnimaIniManager(IG2App* _app, SceneNode* sn, SceneManager* sm);
	~AnimaIniManager();
	void clear();
	void frameRendered(const Ogre::FrameEvent& evt);
private:
	void Animate();
	IG2App* app;
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	std::vector<Entity*> entities;
	SceneNode* mSinbadNode;

	AnimationState* _dance;
	AnimationState* _runTop;
	AnimationState* _runBottom;

	Animation* _anim;
};

