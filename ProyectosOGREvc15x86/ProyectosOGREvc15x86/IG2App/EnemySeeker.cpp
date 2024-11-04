#include "EnemySeeker.h"
#include "Heroe.h"

EnemySeeker::EnemySeeker(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app):
	Enemy(initPos, node, sceneMng, meshName, arr, app)
{
	//dirNueva = chooseDir();
}

EnemySeeker::~EnemySeeker()
{
}

void EnemySeeker::init()
{
}

void EnemySeeker::calculateDirection()
{
	Entity* obj = mSM->getEntity("Heroe");
	hero = (Heroe*)obj;
	Vector3 hP = hero->getPosition();
	Vector3 mP = getPosition();

	//chooseDir(v);
}

void EnemySeeker::frameRendered(const Ogre::FrameEvent& evt)
{
	calculateDirection();
	walk();
}

Vector3 EnemySeeker::chooseDir(Vector3 v)
{
	return Vector3();
}

bool EnemySeeker::checkCruce()
{

	return false;
}
