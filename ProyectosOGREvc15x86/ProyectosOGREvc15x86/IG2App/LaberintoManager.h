#pragma once
#include <OgreSceneManager.h>
#include <string>
using namespace Ogre;

class LaberintoManager
{
public:
	LaberintoManager(SceneNode*, SceneManager*);
	LaberintoManager(SceneNode*, SceneManager*, std::string file);
	~LaberintoManager();

	void loadLevelFromFile(std::string file);
private:private:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	void ReadChar(char c, int i, int j);
	double CentraLab(int a);
};

