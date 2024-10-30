#include "LaberintoManager.h"
#include "Muro.h"
#include "Perla.h"
#include "Heroe.h"
#include "Config.h"
#include <fstream>


LaberintoManager::LaberintoManager(IG2App* _app, SceneNode* sn, SceneManager* sm, std::string file) : app(_app), mNode(sn), mSM(sm)
{
	loadLevelFromFile(file);
}


LaberintoManager::~LaberintoManager()
{
}

void LaberintoManager::loadLevelFromFile(std::string str)
{	
	std::string s = "../media/maps/";
	s += str;
	std::ifstream reader(s);
	if (!reader.is_open()) throw "Error al abrir el archivo";
	int nFils;
	int nCols;
	reader >> nFils;
	reader >> nCols;
	labArray = new bool*[nFils];
	for (int i = 0; i < nFils; i++) {
		labArray[i] = new bool[nCols];
	}
	char c;
	for (int i = 0; i < nFils; i++) {		
		for (int j = 0; j < nCols; j++) {
			reader >> c;
			ReadChar(c, i, j);
		}
	}
	reader.close();
	mNode->setPosition(CentraLab(nFils), 0, CentraLab(nCols));
}

void LaberintoManager::ReadChar(char c, int i, int j)
{
	IG2Object* obj;
	switch (c) {
	case 'x':		
		labArray[i][j] = false;
		obj = new Muro(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		break;
	case 'o':		
		labArray[i][j] = true;
		obj = new Perla(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		obj->setScale(Ogre::Vector3(PERLA_SCALE, PERLA_SCALE, PERLA_SCALE));
		break;
	case 'h':
		labArray[i][j] = true;
		obj = new Heroe(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM, VIDAS,"Sinbad.mesh",labArray,app);
		obj->setScale(Ogre::Vector3(OGRE_SCALE, OGRE_SCALE, OGRE_SCALE));
		break;
	default:
		break;
	}
}
double LaberintoManager::CentraLab(int a) {
	double b = a - 1;
	b = b * CUBE_SIZE;
	b = b * -1;
	b = b / 2;
	return b;
}
