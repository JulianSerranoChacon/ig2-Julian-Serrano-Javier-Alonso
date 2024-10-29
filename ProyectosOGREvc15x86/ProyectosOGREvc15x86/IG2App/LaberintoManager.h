#pragma once
#include <OgreSceneManager.h>
#include <string>
using namespace Ogre;
class IG2App;

class LaberintoManager
{
public:	
	LaberintoManager(IG2App*, SceneNode*, SceneManager*, std::string file);
	~LaberintoManager();

	void loadLevelFromFile(std::string file);
private:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	void ReadChar(char c, int i, int j);
	double CentraLab(int a);
	bool** labArray;
	IG2App* app;
};

