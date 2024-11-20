#include "AnimaIniManager.h"
#include "IG2App.h"
#include "Config.h"
using namespace Ogre;

AnimaIniManager::AnimaIniManager(IG2App* _app, SceneNode* sn, SceneManager* sm) : app(_app), mNode(sn), mSM(sm)
{
	app->addInputListener(this);
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	SceneNode* mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("SinbadAnim");
	mSinbadNode->attachObject(ent);
	mSinbadNode->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	entities.push_back(ent);

	Ogre::MeshManager::getSingleton().createPlane("suelo", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1, 1,
		SUBDIVISION_LUZ_PLANO, SUBDIVISION_LUZ_PLANO, true, 1, 100, 100, Vector3::UNIT_Z);
	//Creación del suelo
	Ogre::Entity* Suel = mSM->createEntity("suelo");
	Suel->setMaterialName(DIR_MAT_SUELO_ANIM);
	Ogre::SceneNode* nodoSuelo = mNode->createChildSceneNode();
	nodoSuelo->setPosition(0, mSinbadNode->getScale().y * -0.5 , 0);
	nodoSuelo->setScale(SUELO_SCALE_ANIM,0, SUELO_SCALE_ANIM);
	nodoSuelo->attachObject(Suel);

	entities.push_back(Suel);
}

AnimaIniManager::~AnimaIniManager()
{
	clear();
}

void AnimaIniManager::clear()
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			mSM->destroyEntity(entities[i]);
			entities[i] = nullptr;
		}
	}
}
