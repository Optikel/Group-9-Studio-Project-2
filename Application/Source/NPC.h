//Child of GameObject
/*
=== NPCs HAVE ===
1. MOVEMENT
2. APPEARANCE
3. DIALOGUE

=================
*/
#pragma once
#include "GameObject.h"
#include "MeshList.h"
#include <string>

class NPC : public GameObject 
{
public:
	//NPC is the body
	NPC(unsigned int id, Mesh* mesh);
	~NPC();
	
	bool inRadius;
	
	enum BODYPART
	{
		HEAD,
		LARM,
		RARM,
		TOTALPART
	};

private:
	bool canMove, talking;
	float radius;
	Vector3 direction;
	std::string speech;
	GameObject* BodyArr[TOTALPART];
	MeshList meshlist;
};