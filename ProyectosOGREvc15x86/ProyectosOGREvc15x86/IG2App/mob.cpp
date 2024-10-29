#include "Mob.h"
#include "Config.h"

Mob::Mob(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName) : IG2Object(initPos, node, sceneMng, meshName),
numVidas(nlifes)
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

bool Mob::checkDir()
{
	return false;
}
