#include "Mob.h"
#include "Config.h"

Mob::Mob(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes) : IG2Object(initPos, node, sceneMng, "Sinbad.mesh"), numVidas(nlifes)
{

}

Mob::~Mob()
{
}

void Mob::init()
{

}

void Mob::changeDirection(Vector3 newDir)
{
	dirNueva = newDir;
}

void Mob::move()
{
	
}
