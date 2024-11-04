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
	Heroe* hero = (Heroe*)obj;
	cout << hero->getPosition().x;

}

void EnemySeeker::frameRendered(const Ogre::FrameEvent& evt)
{
	calculateDirection();
	walk();
}

Vector3 EnemySeeker::chooseDir()
{
	return Vector3();
}
