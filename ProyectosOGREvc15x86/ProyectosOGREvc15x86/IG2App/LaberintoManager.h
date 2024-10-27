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
private:
	Ogre::SceneNode* mLabNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	void readChars(char c, int i, int j);
	double CentraLab(int a);
};

