#include "Heroe.h"

Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr, IG2App*app):Mob(initPos,node,sceneMng,nlifes,meshName,arr, PLAYER_SPEED)
{
	app->addInputListener(this);
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
