#pragma once
#include <OgreSceneManager.h>
#include "IG2ApplicationContext.h"
#include "OgreAnimation.h"
#include <vector>
#include "OgreTimer.h"

using namespace Ogre;
class IG2App;

class AnimaIniManager : public OgreBites::InputListener
{
public:
	AnimaIniManager(IG2App* _app, SceneNode* sn, SceneManager* sm);
	virtual ~AnimaIniManager();
	void clear();
	void frameRendered(const Ogre::FrameEvent& evt);
	void setRun(bool update = false) {_update = update;
	mSM->setAmbientLight(ColourValue(0, 0, 0));
	}
private:
	void Animate();
	IG2App* app;
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	std::vector<Entity*> entities;
	SceneNode* mSinbadNode;
	Ogre::Entity* sinbad;
	Ogre::Entity* espadadDer;
	Ogre::Entity* espadadIz;	


	Ogre::SceneNode* mOgreHeadNode;
	Ogre::Entity* ogreHead;

	bool Bailando;
	bool Corriendo;

	AnimationState* _dance;
	AnimationState* _runTop;
	AnimationState* _runBottom;
	AnimationState* _movement;

	Ogre::Timer* _timer;
	Animation* _anim;

	Vector3 iniPos = Vector3(0,0,0);
	Vector3 SecondPos = Vector3(500,0,0);
	Vector3 ThirdPos = Vector3(-500,0,0);

	Vector3 headOffset = Vector3(-350, 0, 0);

	//Para dejar de ejecutr el IniAnimatedScene
	bool _update;
};

