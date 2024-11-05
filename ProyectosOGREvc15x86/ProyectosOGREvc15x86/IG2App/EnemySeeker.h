#pragma once
#include "Enemy.h"
#include <queue>
#include <OgreTimer.h>
class Heroe;
class EnemySeeker: public Enemy
{
public:
	EnemySeeker(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string meshName, bool** arr, IG2App* app);
	virtual ~EnemySeeker();
	virtual void init();
	virtual void takeDamage() {};
	virtual void calculateDirection();
	virtual void addHeroe(Heroe* h) { hero = h; };
	void frameRendered(const Ogre::FrameEvent& evt);
private:
	Vector3 chooseDir();
	void crearCabeza(string s, Vector3 pos, Vector3 scale, Quaternion rot );
	void creaEntidad();
	Heroe* hero;
	Ogre::SceneNode* rotador;
	Ogre::Timer* timer;
	float rotationSpeed = 0.0523599f;
	int rotDir = 1;
};

