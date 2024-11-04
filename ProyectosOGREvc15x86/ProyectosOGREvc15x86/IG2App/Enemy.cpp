#include "Enemy.h"
#include "Config.h"

Enemy::Enemy(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app):Mob(initPos, node, sceneMng, ENEMY_LIFES, meshName, arr, ENEMY_SPEED)
{
	/*Light* luz = mSM->createLight("LuzHeroe");
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mNode->createChildSceneNode("nLuzHeroe");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
	mLightNode->setPosition(Ogre::Vector3(0, 80, 0));*/

	app->addInputListener(this);
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
}

void Enemy::calculateDirection()
{
}

bool Enemy::EstaEnCruce()
{	
	double margenX = (dirAct.x * CUBE_SIZE) / -2;
	double margenZ = (dirAct.z * CUBE_SIZE) / -2;
	uint _x = (PosX + margenX) / CUBE_SIZE;
	uint _y = (PosZ + margenZ) / CUBE_SIZE;
	if (_x != cruceX && _y != cruceY) {
		cruceX = _x;
		cruceY = _y;
		return (labArray[_x][_y + 1] || labArray[_x][_y - 1]) && (labArray[_x + 1][_y] || labArray[_x - 1][_y]);
	}
	else return false;
}

