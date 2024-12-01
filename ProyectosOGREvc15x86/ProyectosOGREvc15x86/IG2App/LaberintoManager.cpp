#include "LaberintoManager.h"
#include "Muro.h"
#include "Perla.h"
#include "Heroe.h"
#include "Config.h"
#include <fstream>
#include "EnemyRandom.h"
#include "EnemySeeker.h"


LaberintoManager::LaberintoManager(IG2App* _app, SceneNode* sn, SceneManager* sm, std::string file) : app(_app), mNode(sn), mSM(sm)							
{
	app->addInputListener(this);	
	CreateSky();
	loadLevelFromFile(file);
}


LaberintoManager::~LaberintoManager()
{
	for (int i = 0; i < perlas.size(); i++) {
		if (perlas[i] != nullptr) perlas[i]->removeEntity();
	}
	for (int i = 0; i < enemigos.size(); i++) {
		if (enemigos[i] != nullptr) enemigos[i]->removeEntity();
	}
	for (int i = 0; i < muros.size(); i++) {
		if (muros[i] != nullptr) muros[i]->removeEntity();
	}
	if (Suel != nullptr) {
		mSM->destroyEntity(Suel);
		Suel = nullptr;
	}
	mH->removeEntity();
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
	reader >> matBolas;	
	reader >> matMuro;
	reader >> matSuelo;
	reader >> luz;
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
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->addHeroe(mH);
	}
	reader.close();
	Ogre::MeshManager::getSingleton().createPlane("suelo", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1,1, 
													SUBDIVISION_LUZ_PLANO, SUBDIVISION_LUZ_PLANO,true, 1, nFils, nCols, Vector3::UNIT_Z);
	//Creación del suelo
	Suel = mSM->createEntity("suelo");	
	Suel->setMaterialName(matSuelo);
	Ogre::SceneNode* nodoSuelo = mNode->createChildSceneNode();
	nodoSuelo->setPosition((nCols-1)*CUBE_SIZE/2, (float)CUBE_SIZE/-2,(nFils-1)*CUBE_SIZE/2);
	nodoSuelo->setScale(nCols*CUBE_SIZE,1, nFils*CUBE_SIZE);
	nodoSuelo->attachObject(Suel);

	mNode->setPosition(CentraLab(nFils), 0, CentraLab(nCols));
}

void LaberintoManager::frameRendered(const Ogre::FrameEvent& evt)
{	
	for (int i = 0; i < perlas.size(); i++) {
		if (mH->getAABB().intersects(perlas[i]->getAABB())) {
			mH->addPerl();			
			Perla* p = perlas[i];
			perlas.erase(perlas.begin() + i);
			p->removeEntity();
		}
	}

	for (int i = 0; i < enemigos.size(); i++) {
		if (mH->getAABB().intersects(enemigos[i]->getAABB())) {
			mH->takeDamage();
		}
	}
}

void LaberintoManager::ReadChar(char c, int i, int j)
{
	IG2Object* obj;
	ParticleSystem* humo;
	Ogre::SceneNode* n;
	switch (c) {
	case 'x':		
		labArray[i][j] = false;
		obj = new Muro(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		obj->setMaterialName(matMuro);
		muros.push_back((Muro*)obj);
		break;
	case 'o':		
		labArray[i][j] = true;
		obj = new Perla(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		obj->setScale(Ogre::Vector3(PERLA_SCALE, PERLA_SCALE, PERLA_SCALE));
		perlas.push_back((Perla*)obj);
		obj->setMaterialName(matBolas);
		break;
	case 'h':
		labArray[i][j] = true;
		obj = new Heroe(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode("Heroe"), mSM, VIDAS, "Sinbad.mesh", labArray, app, luz);
		obj->setScale(Ogre::Vector3(OGRE_SCALE, OGRE_SCALE, OGRE_SCALE));
		mH = (Heroe*)obj;
		break;
	case 'r':
		labArray[i][j] = true;
		obj = new EnemyRandom(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE* i), mNode->createChildSceneNode(), mSM, "ogrehead.mesh", labArray, app);
		enemigos.push_back((Enemy*)obj);
		break;
	case 'v':
		labArray[i][j] = true;
		obj = new EnemySeeker(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM, "RZR-002.mesh", labArray, app);
		enemigos.push_back((Enemy*)obj);
		break;

	case 's':
		labArray[i][j] = true;
		obj = new Perla(Ogre::Vector3(CUBE_SIZE * j, 0, CUBE_SIZE * i), mNode->createChildSceneNode(), mSM);
		obj->setScale(Ogre::Vector3(PERLA_SCALE, PERLA_SCALE, PERLA_SCALE));
		perlas.push_back((Perla*)obj);
		obj->setMaterialName(matBolas);

		humo = mSM->createParticleSystem("Humo" + to_string(i) + to_string(j), DIRECCION_PART_HUMO_MAPA);
		humo->setEmitting(true);
		n = mSM->getRootSceneNode()->createChildSceneNode();
		n->setPosition(CentraLab(j+2), 0, CentraLab(i+2));
		n->attachObject(humo);
		humo = nullptr;
		n = nullptr;
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

void LaberintoManager::CreateSky()
{
	Ogre::Plane plane;
	plane.d = 1000;
	plane.normal = Ogre::Vector3::UNIT_Y;

	mSM->setSkyPlane(true, plane, DIRECCION_MAT_CIELO, 1500, 50, true, 1.5, 50, 50);
}
