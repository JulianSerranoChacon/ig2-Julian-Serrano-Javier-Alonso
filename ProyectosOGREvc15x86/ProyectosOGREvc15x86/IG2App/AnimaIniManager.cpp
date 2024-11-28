#include "AnimaIniManager.h"
#include "IG2App.h"
#include "Config.h"
#include "OgreKeyFrame.h"

using namespace Ogre;

AnimaIniManager::AnimaIniManager(IG2App* _app, SceneNode* sn, SceneManager* sm) : app(_app), mNode(sn), mSM(sm), Bailando(false), Corriendo(false), _update(true)
{
	app->addInputListener(this);
	sinbad = mSM->createEntity("Sinbad.mesh");
	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("SinbadAnim");
	mSinbadNode->attachObject(sinbad);
	mSinbadNode->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	entities.push_back(sinbad);

	espadadDer = mSM->createEntity("Sword.mesh");
	sinbad->attachObjectToBone("Handle.R", espadadDer);
	espadadIz = mSM->createEntity("Sword.mesh");	
	sinbad->attachObjectToBone("Handle.L", espadadIz);

	Ogre::MeshManager::getSingleton().createPlane("sueloAnim", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1, 1,
		SUBDIVISION_LUZ_PLANO, SUBDIVISION_LUZ_PLANO, true, 1, 20, 20, Vector3::UNIT_Z);
	//Creación del suelo
	Ogre::Entity* Suel = mSM->createEntity("sueloAnim");
	Suel->setMaterialName(DIR_MAT_SUELO_ANIM);
	Ogre::SceneNode* nodoSuelo = mNode->createChildSceneNode();
	//Ogre::SceneNode* nodoSuelo = mSM->getRootSceneNode()->createChildSceneNode("SueloAnim");

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

	nodoSuelo->attachObject(Suel);
	nodoSuelo->setPosition(0, result.y * -0.56 , 0);
	nodoSuelo->setScale(SUELO_SCALE_ANIM,0, SUELO_SCALE_ANIM);

	entities.push_back(Suel);

	ogreHead = mSM->createEntity("ogrehead.mesh");
	mOgreHeadNode = mSM->getRootSceneNode()->createChildSceneNode();
	mOgreHeadNode->attachObject(ogreHead);
	mOgreHeadNode->setScale(Vector3(5, 5, 5));
	entities.push_back(ogreHead);


	_dance = sinbad->getAnimationState("Dance");
	_runTop = sinbad->getAnimationState("RunTop");
	_runBottom = sinbad->getAnimationState("RunBase");
	_dance->setLoop(true);
	_runTop->setLoop(true);
	_runBottom->setLoop(true);		

	Animate();
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
	//sinbad->getAllAnimationStates()->removeAllAnimationStates();
}

void AnimaIniManager::frameRendered(const Ogre::FrameEvent& evt)
{		
	if (!_update)
		return;

	_movement->addTime(evt.timeSinceLastFrame);
	if (_timer->getMilliseconds() < TIEMPO_BAILE) {
		_dance->addTime(evt.timeSinceLastFrame);
		if (!Bailando) {
			_dance->setTimePosition(0);
			_dance->setEnabled(true);
			_runBottom->setEnabled(false);
			_runTop->setEnabled(false);
			Bailando = true;
			Corriendo = false;
		}		
	}
	else {
		if (_timer->getMilliseconds() >= TIEMPO_BAILE) {
			_runTop->addTime(evt.timeSinceLastFrame);
			_runBottom->addTime(evt.timeSinceLastFrame);
			if (!Corriendo) {
				_dance->setEnabled(false);
				_runBottom->setTimePosition(0);
				_runBottom->setEnabled(true);
				_runTop->setTimePosition(0);
				_runTop->setEnabled(true);
				Bailando = false;
				Corriendo = true;
			}			
		}
	}
	espadadDer->setVisible(_timer->getMilliseconds() > MUESTRA_ESPADAS);
	espadadIz->setVisible(_timer->getMilliseconds() > MUESTRA_ESPADAS);


	if (_timer->getMilliseconds() >= TIEMPO_MAX) {
		_timer->reset();
		_dance->setTimePosition(0);
		_runTop->setTimePosition(0);
		_runBottom->setTimePosition(0);
	}
}

void AnimaIniManager::Animate()
{
	_timer = new Ogre::Timer();
	_timer->reset();
	_anim = mSM->createAnimation("AnimSinbad", ANIM_DURATION);
	_anim->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = _anim->createNodeTrack(0);	
	track->setAssociatedNode(mSinbadNode);
	NodeAnimationTrack* trackHead = _anim->createNodeTrack(1);
	trackHead->setAssociatedNode(mOgreHeadNode);
	TransformKeyFrame* kf;

	kf = track->createNodeKeyFrame(STOP_DANCING);
	kf->setTranslate(iniPos);	
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(0.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(STOP_DANCING);
	kf->setTranslate(iniPos + headOffset);
	kf->setScale(Vector3(0, 0, 0));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(STOP_DANCING + TIME_FOR_SPIN);
	kf->setTranslate(iniPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(STOP_DANCING + TIME_FOR_SPIN);
	kf->setTranslate(iniPos + headOffset);
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(SPIN);
	kf->setTranslate(SecondPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(SPIN);
	kf->setTranslate(SecondPos + headOffset);
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(SPIN + TIME_FOR_SPIN);
	kf->setTranslate(SecondPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(-90.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(SPIN + TIME_FOR_SPIN);
	kf->setTranslate(SecondPos + headOffset);
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(Quaternion(Degree(-90.0), Vector3(0, 1, 0)));


	kf = track->createNodeKeyFrame(SECOND_SPIN);
	kf->setTranslate(ThirdPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(-90.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(SECOND_SPIN);
	kf->setTranslate(ThirdPos + headOffset);
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(Quaternion(Degree(-90.0), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(SECOND_SPIN + TIME_FOR_SPIN);
	kf->setTranslate(ThirdPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(SECOND_SPIN + TIME_FOR_SPIN);
	kf->setTranslate(ThirdPos + headOffset);
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));


	kf = track->createNodeKeyFrame(ANIM_DURATION- TIME_FOR_SPIN);
	kf->setTranslate(iniPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = trackHead->createNodeKeyFrame(ANIM_DURATION - TIME_FOR_SPIN);
	kf->setTranslate(iniPos + headOffset);
	kf->setScale(Vector3(0, 0, 0));
	kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(ANIM_DURATION);
	kf->setTranslate(iniPos);
	kf->setScale(Vector3(OGRE_SCALE_ANIM, OGRE_SCALE_ANIM, OGRE_SCALE_ANIM));
	kf->setRotation(Quaternion(Degree(0.0), Vector3(0, 1, 0)));
	


	_movement = mSM->createAnimationState("AnimSinbad");
	_movement->setLoop(true);
	_movement->setEnabled(true);
}
