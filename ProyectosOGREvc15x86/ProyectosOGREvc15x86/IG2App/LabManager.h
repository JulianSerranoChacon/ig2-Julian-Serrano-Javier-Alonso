#pragma once
#include "OgreSceneManager.h"
#include <string>
using namespace Ogre;

class LabManager
{
public: 
	LabManager(SceneNode*, SceneManager*);
	LabManager(SceneNode*, SceneManager*, std::string);
	~LabManager();

	void loadLevelFromFile(std::string);
private:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	void ReadChar(char c, int i, int j);
	double CentraLab(int a);
};

