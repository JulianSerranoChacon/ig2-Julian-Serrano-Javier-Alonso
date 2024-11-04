#include "Heroe.h"
#include <string>


Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr, IG2App*app):Mob(initPos,node,sceneMng,nlifes,meshName,arr, PLAYER_SPEED)
{	
	app->addInputListener(this);
	mTextBox = app->getTextBox();
	updateTextBox();
	
	Light* luz = mSM->createLight("LuzHeroe");
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mNode->createChildSceneNode("nLuzHeroe");			
	mLightNode->attachObject(luz);	
	mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
	mLightNode->setPosition(Ogre::Vector3(0, 80, 0));
}

void Heroe::init()
{
}

void Heroe::takeDamage()
{
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
	walk();

}

void Heroe::updateTextBox()
{	
	std::string st = "Vidas: ";
	st += std::to_string(numVidas);	
	st += "\nPuntos: ";
	st += std::to_string(numPerls * PUNTOS_POR_PERLA);
	mTextBox->setText(st);
}
