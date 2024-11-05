#include "EnemySeeker.h"
#include "Heroe.h"

EnemySeeker::EnemySeeker(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app):
	Enemy(initPos, node, sceneMng, meshName, arr, app)
{	
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
	walk();
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
