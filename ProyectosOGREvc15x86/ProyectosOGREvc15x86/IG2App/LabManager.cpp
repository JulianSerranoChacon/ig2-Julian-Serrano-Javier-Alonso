#include "LabManager.h"
#include "Muro.h"
#include "Perla.h"
#include <fstream>


LabManager::LabManager(SceneNode* sn, SceneManager* sm): mNode(sn), mSM(sm)
{
	//Muro* m = new Muro(Ogre::Vector3(0, 0, 0), mSM->getRootSceneNode()->createChildSceneNode("mur"), mSM);
}
LabManager::LabManager(SceneNode* sn, SceneManager* sm, std::string str) : mNode(sn), mSM(sm)
{
	loadLevelFromFile(str);
}

LabManager::~LabManager()
{

}

void LabManager::loadLevelFromFile(std::string str) {
	std::string s = "../media/maps/";
	s += str;
	std::ifstream reader(s);
	if (!reader.is_open()) throw "Error al abrir el archivo";
	int nFils;
	int nCols;
	reader >> nFils;
	reader >> nCols;
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

void LabManager::ReadChar(char c, int i, int j)
{
	IG2Object* obj;
	switch (c) {
	case 'x':
		obj = new Muro(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		break;
	case 'o':
		obj = new Perla(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		obj->setScale(Ogre::Vector3(PERLA_SCALE, PERLA_SCALE, PERLA_SCALE));
		break;
	default:
		break;
	}
}
double LabManager::CentraLab(int a) {
	double b = a-1;	
	b = b * CUBE_SIZE;
	b = b * -1;
	b = b / 2;
	return b;
}