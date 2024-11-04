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

