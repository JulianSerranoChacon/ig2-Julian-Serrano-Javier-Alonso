#include "Heroe.h"

Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr, IG2App*app):Mob(initPos,node,sceneMng,nlifes,meshName,arr)
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
		changeDirection(Vector3(-3, 0, 0));
		std::cout << "left";
		break;
	case SDLK_RIGHT:
		changeDirection(Vector3(3, 0, 0));
		std::cout << "right";
		break;
	case SDLK_UP:
		changeDirection(Vector3(0, 0, -3));
		std::cout << "up";
		break;
	case SDLK_DOWN:
		changeDirection(Vector3(0, 0, 3));
		std::cout << "down";
		break;
	case SDLK_0:
		walk();		
		break;
	default:
		break;
	}
	return true;
}
