#include "LaberintoManager.h"
#include "Muro.h"
#include "Perla.h"
#include "Config.h"
#include <fstream>


LaberintoManager::LaberintoManager(SceneNode* s, SceneManager* sM) : mLabNode(s), mSM(sM)
{
}
LaberintoManager::LaberintoManager(SceneNode* s, SceneManager* sM, std::string file) : mLabNode(s), mSM(sM)
{
	loadLevelFromFile(file);
}


LaberintoManager::~LaberintoManager()
{
}

void LaberintoManager::loadLevelFromFile(std::string file)
{	
	std::string s = "../media/maps/";
	s += file;
	ifstream reader(s);
	if (!reader.is_open()) throw "Error al abrir el archivo";

	int nFils;
	int nCols;
	reader >> nFils;
	reader >> nCols;
	char c;
	for (int i = 0; i < nFils; i++) {
		for (int j = 0; j < nCols; j++) {			
			reader >> c;
			readChars(c, i, j);
		}
	}
	reader.close();
	mLabNode->setPosition(CentraLab(nFils), 0, CentraLab(nCols));
}

void LaberintoManager::readChars(char c, int i, int j)
{
	IG2Object* obj;
	switch (c) {
	case 'x':
		obj = new Muro(Ogre::Vector3(CUBE_SIZE*j,0, CUBE_SIZE*i), mLabNode->createChildSceneNode(), mSM);
		break;
	case 'o':
		obj = new Perla(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE *i), mLabNode->createChildSceneNode(), mSM);
		obj->setScale(Ogre::Vector3(PERLA_SCALE, PERLA_SCALE, PERLA_SCALE));
		break;
	default:
		break;
	}
}
double LaberintoManager::CentraLab(int a) {
	a -= 1;
	return (-1 * a * CUBE_SIZE) / 2;
}
