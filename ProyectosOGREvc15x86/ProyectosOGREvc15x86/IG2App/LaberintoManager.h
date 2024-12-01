#pragma once
#include <OgreSceneManager.h>
#include "IG2ApplicationContext.h"
#include <vector>
#include <string>
using namespace Ogre;
class IG2App;
class Heroe;
class Perla;
class Enemy;
class Muro;

class LaberintoManager : public OgreBites::InputListener
{
public:	
	LaberintoManager(IG2App*, SceneNode*, SceneManager*, std::string file);
	~LaberintoManager();

	void loadLevelFromFile(std::string file);
	void frameRendered(const Ogre::FrameEvent& evt);
private:
	Ogre::Entity* Suel;
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	void ReadChar(char c, int i, int j);
	double CentraLab(int a);
	bool** labArray;
	IG2App* app;
	std::vector<Perla*> perlas;
	std::vector<Enemy*> enemigos;
	std::vector<Muro*> muros;
	Heroe* mH;
	std::string matBolas;
	std::string matMuro;
	std::string matSuelo;
	uint luz;
	void CreateSky();
};

