#include "EnemySeeker.h"
#include "Heroe.h"

EnemySeeker::EnemySeeker(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app):
	Enemy(initPos, node, sceneMng, meshName, arr, app)
{	
	creaEntidad();
	timer = new Ogre::Timer();
}

EnemySeeker::~EnemySeeker()
{
}

void EnemySeeker::init()
{
}

void EnemySeeker::calculateDirection()
{
	if (checkWallCollision(dirAct) || EstaEnCruce() || dirAct == Vector3(0, 0, 0)) {
		dirNueva = chooseDir();
	}
}

void EnemySeeker::frameRendered(const Ogre::FrameEvent& evt)
{
	calculateDirection();
	walk(false);
	rotador->rotate(Quaternion(Ogre::Radian(rotationSpeed), Vector3(0, rotDir, 0)));
	if (timer->getMilliseconds() >= 5000) {
		timer->reset();
		rotDir*= -1;
	}
}

Vector3 EnemySeeker::chooseDir()
{		
	Vector3 hP = hero->getPosition();
	Vector3 mP = getPosition();
	std::vector<Vector3> v = getDirections();	
	int sol = 0;
	double dist = hP.distance(mP + (v[0] * CUBE_SIZE));	
	if (dist < 0) dist = dist * -1;
	for (int i = 1; i < v.size(); i++) {
		double aux = hP.distance(mP + (v[i] * CUBE_SIZE));				
		if (aux < dist) {
			dist = aux;
			sol = i;
		}
	}
	return v[sol];
}

void EnemySeeker::crearCabeza(string s, Vector3 pos, Vector3 scale, Quaternion rot)
{
	Ogre::Entity* ent = mSM->createEntity("ogrehead.mesh"); 
	rotador->createChildSceneNode(s)->attachObject(ent);
	rotador->getChild(s)->translate(pos);
	rotador->getChild(s)->setScale(scale);
	rotador->getChild(s)->rotate(rot);
}

void EnemySeeker::creaEntidad()
{
	mNode->setScale(Vector3(7, 7, 7));
	Ogre::Entity* ent = mSM->createEntity("penguin.mesh");

	Ogre::SceneNode* pN = mNode->createChildSceneNode("ninja");
	pN->attachObject(ent);
	Ogre::Node* penguin = mNode->getChild("ninja");
	penguin->translate(Vector3(0, 3, 0));
	penguin->setScale(Vector3(0.1, 0.1, 0.1));

	rotador = pN->createChildSceneNode();
	crearCabeza("h1", Vector3(0, 0, 30), Vector3(0.4, 0.4, 0.4), Quaternion(Ogre::Radian(0.0f), Vector3(0, 0, 0)));
	crearCabeza("h2", Vector3(0, 0, -30), Vector3(0.4, 0.4, -0.4), Quaternion(Ogre::Radian(0.0f), Vector3(0, 0, 0)));

	crearCabeza("h3", Vector3(30, 0, 0), Vector3(0.4, 0.4, 0.4), Quaternion(Ogre::Radian(1.5708f), Vector3(0, 1, 0)));
	crearCabeza("h4", Vector3(-30, 0, 0), Vector3(0.4, 0.4, -0.4), Quaternion(Ogre::Radian(4.71239f), Vector3(0, -1, 0)));


	crearCabeza("h5", Vector3(20, 0, 20), Vector3(0.4, 0.4, 0.4), Quaternion(Ogre::Radian(0.785398), Vector3(0, 1, 0)));
	crearCabeza("h6", Vector3(-20, 0, -20), Vector3(0.4, 0.4, -0.4), Quaternion(Ogre::Radian(5.49779f), Vector3(0, -1, 0)));

	crearCabeza("h7", Vector3(-20, 0, 20), Vector3(0.4, 0.4, 0.4), Quaternion(Ogre::Radian(5.49779f), Vector3(0, 1, 0)));
	crearCabeza("h8", Vector3(20, 0, -20), Vector3(0.4, 0.4, -0.4), Quaternion(Ogre::Radian(0.785398), Vector3(0, -1, 0)));
}
