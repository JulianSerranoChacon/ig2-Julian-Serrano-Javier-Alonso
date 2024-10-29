#include "Mob.h"
#include "Config.h"

Mob::Mob(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, uint nlifes, string meshName, bool** arr) : IG2Object(initPos, node, sceneMng, meshName),
numVidas(nlifes), labArray(arr)
{
	myPos = initPos;
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

void Mob::walk()
{
	//Aquí comprueba si hay que hacer algún cambio de dirección
	if (dirAct != dirNueva) {
		if (checkDir()) dirAct = dirNueva;				
	}
	//Aquí comprueba si se va a chocar con un muro
	uint _x = myPos.x / CUBE_SIZE;
	uint _y = myPos.z / CUBE_SIZE;
	uint aux = _x + dirAct.x;
	uint aux2 = _y + dirAct.z;
	if (!labArray[aux][aux2]) {
		dirAct = Vector3(0, 0, 0);		
	}	
	std::cout << dirAct.z;
	move(dirAct);
	myPos.x += dirAct.x;
	myPos.z += dirAct.z;
}

bool Mob::checkDir()
{
	
	uint _x = myPos.x / CUBE_SIZE;		
	uint _y = myPos.z / CUBE_SIZE;
	if (dirNueva.x != 0) {
		uint aux = _x + dirNueva.x;
		if (labArray[aux][_y]) {
			return true;
		}
		else return false;
	}
	else
	{
		if (dirNueva.z != 0) {			
			uint aux = _y + dirNueva.z;
			if (labArray[_x][aux]) {				
				return true;
			}
			else return false;
		}
		else return false;
	}
}
