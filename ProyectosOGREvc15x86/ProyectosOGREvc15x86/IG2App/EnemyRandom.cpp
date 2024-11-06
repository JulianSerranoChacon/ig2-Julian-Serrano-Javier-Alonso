#include "EnemyRandom.h"
#include <cstdlib>
//#include <fstream>

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
	if (checkWallCollision(dirAct) ||  EstaEnCruce() || dirAct == Vector3(0, 0, 0)) {
		dirNueva = chooseDir();		
	}
}

void EnemyRandom::frameRendered(const Ogre::FrameEvent& evt)
{
	calculateDirection();
	walk(false);
}

Vector3 EnemyRandom::chooseDir()
{	
	std::vector<Vector3> v = getDirections();
	if (v.empty()) {
		return dirAct * -1;
	}
	else
	if (v.size() <= 1) {		
		 return v[0];
	}
	else {
		int r1 = rand() % v.size();
		if (v[r1] == dirAct * -1) {
			return chooseDir();
		}
		else {
			return v[r1];
		}
	}	
}
