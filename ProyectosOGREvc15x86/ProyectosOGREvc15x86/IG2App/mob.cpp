#include "Mob.h"
#include "Config.h"

Mob::Mob(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr, float _speed) : IG2Object(initPos, node, sceneMng, meshName),
numVidas(nlifes), labArray(arr), speed(_speed)
{
	PosX = initPos.x + CUBE_SIZE * 0.5;
	PosZ = initPos.z + CUBE_SIZE * 0.5;
}

Mob::~Mob()
{
}

void Mob::changeDirection(Vector3 newDir)
{
	dirNueva = newDir;
}

void Mob::walk()
{	
	//Aquí comprueba si hay que hacer algún cambio de dirección
	if (dirAct != dirNueva) {
		if (checkDir()) {
			dirAct = dirNueva;
			Quaternion q = getOrientation().getRotationTo(dirNueva);
			//rotate(q);
			mNode->rotate(q);
		}
	}	
	uint frenador = 1;
	if (checkWallCollision()) {
		frenador = 0;
	}

	move(dirAct*speed*frenador);
	PosX += dirAct.x*speed*frenador;
	PosZ += dirAct.z*speed*frenador;
}

bool Mob::checkDir()
{		
	if (!checkWallCollision() && dirAct == dirNueva * -1)
		return false;

	double margenX = (dirAct.x * CUBE_SIZE) / -2;
	double margenZ = (dirAct.z * CUBE_SIZE) / -2;
	uint _x = (PosX + margenX) / CUBE_SIZE;
	uint _y = (PosZ + margenZ) / CUBE_SIZE;
	if (dirNueva.x != 0) {
		uint aux = _x + dirNueva.x;
		return labArray[_y][aux];
	}
	else if(dirNueva.z != 0) {
		uint aux = _y + dirNueva.z;
		return labArray[aux][_x];
	}
	else
		return false;
}

bool Mob::checkWallCollision()
{
	//Aquí comprueba si se va a chocar con un muro
	double margenX = (dirAct.x * CUBE_SIZE) / -2;
	double margenZ = (dirAct.z * CUBE_SIZE) / -2;
	uint _x = (PosX + margenX) / CUBE_SIZE;
	uint _y = (PosZ + margenZ) / CUBE_SIZE;
	uint aux = _x + dirAct.x;
	uint aux2 = _y + dirAct.z;

	return !labArray[aux2][aux];
}

void Mob::frameRendered(const Ogre::FrameEvent& evt)
{
	walk();
}
