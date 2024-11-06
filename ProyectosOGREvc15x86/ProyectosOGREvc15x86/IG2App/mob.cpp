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

void Mob::walk(bool heroe)
{	
	//Aquí comprueba si hay que hacer algún cambio de dirección
	if (dirAct != dirNueva) {
		if (checkDir(heroe)) {
			dirAct = dirNueva;
			Quaternion q = getOrientation().getRotationTo(dirNueva);
			//rotate(q);
			mNode->rotate(q);
		}
	}	
	uint frenador = 1;
	if (checkWallCollision(dirAct)) {
		frenador = 0;
	}

	move(dirAct*speed*frenador);
	PosX += dirAct.x*speed*frenador;
	PosZ += dirAct.z*speed*frenador;
}

bool Mob::checkDir(bool heroe)
{		
	if (!checkWallCollision(dirAct) && dirAct == dirNueva * -1)
		return heroe;

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

bool Mob::checkWallCollision(Vector3 v)
{
	//Aquí comprueba si se va a chocar con un muro
	double margenX = (v.x * CUBE_SIZE) / -2;
	double margenZ = (v.z * CUBE_SIZE) / -2;
	uint _x = (PosX + margenX) / CUBE_SIZE;
	uint _y = (PosZ + margenZ) / CUBE_SIZE;
	uint aux = _x + v.x;
	uint aux2 = _y + v.z;

	return !labArray[aux2][aux];
}

void Mob::frameRendered(const Ogre::FrameEvent& evt)
{	
}

std::vector<Vector3> Mob::getDirections()
{
	std::vector<Vector3> v;
	Vector3 masAtrás = dirAct*-1;
	if (Vector3(1, 0, 0) != masAtrás &&!checkWallCollision(Vector3(1, 0, 0))) v.push_back(Vector3(1, 0, 0));
	if (Vector3(-1, 0, 0) != masAtrás && !checkWallCollision(Vector3(-1, 0, 0))) v.push_back(Vector3(-1, 0, 0));
	if (Vector3(0, 0, 1) != masAtrás && !checkWallCollision(Vector3(0, 0, 1))) v.push_back(Vector3(0, 0, 1));
	if (Vector3(0, 0, -1) != masAtrás && !checkWallCollision(Vector3(0, 0, -1))) v.push_back(Vector3(0, 0, -1));

	//v.push_back(masAtrás);
	return v;
}
