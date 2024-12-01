#include "Heroe.h"
#include <string>


Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr, IG2App*app, uint luz):Mob(initPos,node,sceneMng,nlifes,meshName,arr, PLAYER_SPEED)
{	
	app->addInputListener(this);
	mTextBox = app->getTextBox();
	updateTextBox();
	createLight(luz);
}

void Heroe::init()
{
}

void Heroe::takeDamage()
{
	if (!invencible) {
		numVidas--;
		updateTextBox();
		invencible = true;
		invencibleTime = INVENCIBLE_TIME;
	}
}

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& ev)
{
	switch (ev.keysym.sym) {
	case SDLK_LEFT:
		changeDirection(Vector3(-1, 0, 0));		
		break;
	case SDLK_RIGHT:
		changeDirection(Vector3(1, 0, 0));		
		break;
	case SDLK_UP:
		changeDirection(Vector3(0, 0, -1));		
		break;
	case SDLK_DOWN:
		changeDirection(Vector3(0, 0, 1));					
		break;
	default:
		break;
	}
	return true;
}

void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	walk(true);
	if (invencible) {
		invencibleTime--;
		if (invencibleTime <= 0)
			invencible = false;
	}
}

void Heroe::updateTextBox()
{	
	std::string st = "Vidas: ";
	st += std::to_string(numVidas);	
	st += "\nPuntos: ";
	st += std::to_string(numPerls * PUNTOS_POR_PERLA);
	mTextBox->setText(st);
}

void Heroe::createLight(uint i)
{
	Light* luz = mSM->createLight("LuzHeroe");
	mLightNode = mNode->createChildSceneNode("nLuzHeroe");
	switch (i) {
	case 0:		
		luz->setType(Ogre::Light::LT_DIRECTIONAL);
		luz->setDiffuseColour(0.75, 0.75, 0.75);
			
		mLightNode->attachObject(luz);
		mLightNode->setDirection(Ogre::Vector3(-0.25, -0.5, -1));
		break;
	case 1:		
		luz->setType(Ogre::Light::LT_SPOTLIGHT);
		luz->setDiffuseColour(0.75, 0.75, 0.75);
		
		mLightNode->attachObject(luz);
		mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
		mLightNode->setPosition(Ogre::Vector3(0, 30, 0));
		break;
	case 2:		
		luz->setType(Ogre::Light::LT_POINT);
		luz->setDiffuseColour(1, 1, 1);
		
		mLightNode->attachObject(luz);				
		break;
	default:
		break;
	}
}
