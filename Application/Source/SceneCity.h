#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Skybox.h"
#include "TextureList.h"
#include "Text.h"
#include "WayPoint.h"

class SceneCity : public Scene
{
public:
	enum Environment_Type
	{
		EN_FLOOR = 0,
		EN_HOUSE1,
		EN_HOUSE2,
		EN_HOUSE3,
		EN_HOUSE4,
		EN_HOUSE5,
		EN_TOWER1,
		EN_STADIUM,
		EN_TOTAL
	};

	enum LIGHT_LOCATION
	{
		LIGHT_MIDDLE,
		LIGHT_TEST,
		LIGHT_TOTAL
	};

	enum TEXT_TYPE
	{
		TEXT_FPS,
		TEXT_POSITION,
		TEXT_TOTAL
	};

	enum WP_TYPE //USED TO SET EMPTY GAMEOBJECTS (NOMESH) as way points for us to see where we can change scenes
	{
		WP_STADIUM,
		WP_TOTAL
	};
	SceneCity();
	~SceneCity();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

private:
	double fps;

	Renderer* renderer;

	CameraVer2 camera;

	GOManager goManager;
	GameObject* Axis;
	Character* MainChar;
	Character* Ayaka;
	GameObject* Environment[EN_TOTAL];
	WayPoint* Waypoints[WP_TOTAL]; //For a switching scenes
	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;
	Text* textarr[TEXT_TOTAL];

	//Temp
	GameObject* Cube[2];
};

#endif