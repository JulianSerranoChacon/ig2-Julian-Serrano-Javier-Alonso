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
		SUBDIVISION_LUZ_PLANO, SUBDIVISION_LUZ_PLANO, true, 1, 20, 20, Vector3::UNIT_Z);
	//Creación del suelo
	Ogre::Entity* Suel = mSM->createEntity("suelo");
	Suel->setMaterialName(DIR_MAT_SUELO_ANIM);
	Ogre::SceneNode* nodoSuelo = mNode->createChildSceneNode();

	Vector3 result;

	if (mSinbadNode->getAttachedObjects().size() > 0) {
		Entity* mEntity = static_cast<Entity*>(mSinbadNode->getAttachedObject(0));
		const AxisAlignedBox& aab = mEntity->getBoundingBox();
		Vector3 min = aab.getMinimum() * mSinbadNode->getScale();
		Vector3 max = aab.getMaximum() * mSinbadNode->getScale();
		Real paddingFactor = MeshManager::getSingleton().getBoundsPaddingFactor();

		// adjust min & max to exclude the padding factor..
		Vector3 newMin = min + (max - min) * paddingFactor;
		Vector3 newMax = max + (min - max) * paddingFactor;
		result = newMax - newMin;
	}
	else
		result = { 0,0,0 };

	nodoSuelo->setPosition(0, result.y * -0.56 , 0);
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
