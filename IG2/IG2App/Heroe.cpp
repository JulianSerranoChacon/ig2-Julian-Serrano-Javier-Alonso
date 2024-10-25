#include "Heroe.h"
#include "Config.h"

Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng, "Sinbad.mesh"), numVidas(VIDAS)
{

}

void Heroe::init()
{

}

void Heroe::takeDamage()
{
	if (numVidas > 0)numVidas--;	
}

void Heroe::ChangeDirection(Vector3 newDir)
{
	dirNueva = newDir;
}
