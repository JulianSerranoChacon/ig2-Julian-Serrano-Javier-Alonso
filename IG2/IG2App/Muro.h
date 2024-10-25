#pragma once
#include "IG2Object.h"
class Muro: public IG2Object
{
public:
	Muro() {};
	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	virtual void init();
};

