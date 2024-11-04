#include "EnemyRandom.h"
#include <cstdlib>
#include <fstream>

EnemyRandom::EnemyRandom(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app): Enemy(initPos, node, sceneMng, meshName, arr, app)
{
	dirNueva = chooseDir();
}

EnemyRandom::~EnemyRandom()
{
}

void EnemyRandom::init()
{
}

void EnemyRandom::calculateDirection()
{
	if (checkWallCollision()) {
		dirNueva = chooseDir();
	}
}

void EnemyRandom::frameRendered(const Ogre::FrameEvent& evt)
{
	calculateDirection();
	walk();
}

Vector3 EnemyRandom::chooseDir()
{
	int r1 = rand() % 2;
	int r2 = rand() % 2;

	int x = 0, y = 0, z = 0;
	Vector3 v;

	switch (r1)
	{
		case 1:
			if (r2 == 0)
				v = Vector3(1, 0, 0);
			else
				v = Vector3(-1, 0, 0);
			break;
		case 0:
			if (r2 == 0)
				v = Vector3(0, 0, 1);
			  else
				v = Vector3(0, 0, -1);
			break;
		default:
			break;
	}
	cout << v.x << " " << v.z << " " << endl;
	return v;
}
