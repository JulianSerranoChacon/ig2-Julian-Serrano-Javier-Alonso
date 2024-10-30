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
		if (checkDir()) {
			dirAct = dirNueva;
			Quaternion q = getOrientation().getRotationTo(dirNueva);
			//rotate(q);
		}
	}	
	//Aquí comprueba si se va a chocar con un muro
	double margenX = (dirAct.x* CUBE_SIZE)/-2;
	double margenZ = (dirAct.z * CUBE_SIZE)/-2;	
	uint _x = (PosX+margenX) / CUBE_SIZE;
	uint _y = (PosZ+margenZ) / CUBE_SIZE;
	uint aux = _x + dirAct.x;
	uint aux2 = _y + dirAct.z;
	uint frenador = 1;
	if (!labArray[aux2][aux]) {
		frenador = 0;
	}

	move(dirAct*speed*frenador);
	PosX += dirAct.x*speed*frenador;
	PosZ += dirAct.z*speed*frenador;
}

bool Mob::checkDir()
{		
	if (dirAct == dirNueva * -1) return false;
	else {
		double margenX = (dirAct.x * CUBE_SIZE) / -2;
		double margenZ = (dirAct.z * CUBE_SIZE) / -2;
		uint _x = (PosX + margenX) / CUBE_SIZE;
		uint _y = (PosZ + margenZ) / CUBE_SIZE;
		if (dirNueva.x != 0) {
			uint aux = _x + dirNueva.x;
			if (labArray[_y][aux]) {
				return true;
			}
			else return false;
		}
		else
		{
			if (dirNueva.z != 0) {
				uint aux = _y + dirNueva.z;
				if (labArray[aux][_x]) {
					return true;
				}
				else return false;
			}
			else return false;
		}
	}	
}

void Mob::frameRendered(const Ogre::FrameEvent& evt)
{
	walk();
}
