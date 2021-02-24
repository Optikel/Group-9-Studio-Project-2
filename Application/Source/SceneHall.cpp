#include "SceneHall.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneHall::SceneHall() :
	fps(0.f)
{
}

SceneHall::~SceneHall()
{
}

void SceneHall::Init()
{
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 3, -40), Vector3(0, 0, -1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	MeshList* meshlist = MeshList::GetInstance();

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	lights[1] = new Light(Shader::GetInstance()->shaderdata, 1);

	skybox = new Skybox(goManager, meshlist, 3);

	MainChar = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	MainChar->SetColliderBox();
	MainChar->Init(Vector3(0, 3, -40));
	MainChar->SetTranslate(MainChar->GetTranslate() + Vector3(0,30,0));
	//MainChar->SetCamera(&camera);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Cube[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));

	Cube[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[1]->SetColliderBox();

	Collectible = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Collectible->SetTranslate(Vector3(0, 3, 0));

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(Vector3(0, 0, 5), Vector3(0, 0, 0), Vector3(0.2f, 0.2f, 0.2f));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	npc = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_CUBE));
	npc->SetColliderBox();
	npc->Init(meshlist, Ayaka, Vector3(0, 3, -3), Vector3(0, 0, 0));
	//npc->PushPathPoint(Vector3(4, 3, 0));
	//npc->PushPathPoint(Vector3(0, 3, -9));

	ui = new UI();
	ui->Init(Ayaka);

	{
		Environment[EN_FLOOR1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR1]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR1]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_FLOOR2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR2]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR2]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR2]->SetTranslate(Vector3(0, 0, -15));
		Environment[EN_FLOOR2]->SetRotate(Vector3(90, 0, 0));

		Environment[EN_FLOOR3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR3]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR3]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR3]->SetTranslate(Vector3(0, 0, 15));
		Environment[EN_FLOOR3]->SetRotate(Vector3(90, 180, 0));

		Environment[EN_FLOOR4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR4]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR4]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR4]->SetTranslate(Vector3(15, 0, 0));
		Environment[EN_FLOOR4]->SetRotate(Vector3(0, 0, 90));

		Environment[EN_FLOOR5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR5]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR5]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR5]->SetTranslate(Vector3(-15, 0, 0));
		Environment[EN_FLOOR5]->SetRotate(Vector3(0, 0, 270));

		Environment[EN_FLOOR6] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR6]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR6]->SetTranslate(Vector3(0, 15, 0));
		Environment[EN_FLOOR6]->SetRotate(Vector3(180, 0, 0));

		Environment[EN_TABLE] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TABLE));
		Environment[EN_TABLE]->SetColliderBox(Vector3(4, 2.5, 1.6));
		Environment[EN_TABLE]->SetScale(Vector3(2, 2.5, 1.5));
		Environment[EN_TABLE]->SetTranslate(Vector3(0, 0.025, 0));
		
		Environment[EN_PLANT1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT1]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT1]->SetTranslate(Vector3(14, 0, 14));

		Environment[EN_PLANT2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT2]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT2]->SetTranslate(Vector3(-14, 0, 14));

		Environment[EN_PLANT3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT3]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT3]->SetTranslate(Vector3(-14, 0, -14));

		Environment[EN_PLANT4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT4]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT4]->SetTranslate(Vector3(14, 0, -14));
	}
}

void SceneHall::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 50, 80), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -50, -80));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneHall::Update(double dt)
{
	//have something else update teh cam. to have access to both cam and character
	
	camera.Updatemovement(dt);

	ui->setCamera(&camera);
	ui->Update();

	//Collision
	Ayaka->CollisionResolution(Environment[EN_FLOOR2]);
	Ayaka->CollisionResolution(Environment[EN_FLOOR3]);
	Ayaka->CollisionResolution(Environment[EN_FLOOR4]);
	Ayaka->CollisionResolution(Environment[EN_FLOOR5]);
	Ayaka->CollisionResolution(Environment[EN_TABLE]);
	Ayaka->CollisionResolution(Environment[EN_PLANT1]);
	Ayaka->CollisionResolution(Environment[EN_PLANT2]);
	Ayaka->CollisionResolution(Environment[EN_PLANT3]);
	Ayaka->CollisionResolution(Environment[EN_PLANT4]);
	Ayaka->CollisionResolution(npc);

	//Update Camera after updating collision
	camera.Updateposition();

	{
		if (Application::IsKeyPressed('1'))
		{
			glEnable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('2'))
		{
			glDisable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('3'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (Application::IsKeyPressed('4'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (Application::IsKeyPressed('9'))
		{
			Collision::isRender = true;
		}
		if (Application::IsKeyPressed('0'))
		{
			Collision::isRender = false;
		}
	}

	// Cube Collision Test stuff
	{
		float SPEED = 5.f * dt;
		Vector3 Direction = Vector3(0,0,0);
		if (Application::IsKeyPressed('I'))
			Direction += Vector3(0, 0, 1);
		if (Application::IsKeyPressed('K'))
			Direction += Vector3(0, 0, -1);
		if (Application::IsKeyPressed('J'))
			Direction += Vector3(1, 0, 0);
		if (Application::IsKeyPressed('L'))
			Direction += Vector3(-1, 0, 0);
		if (Application::IsKeyPressed('O'))
			Direction += Vector3(0, 1, 0);
		if (Application::IsKeyPressed('P'))
			Direction += Vector3(0, -1, 0);

		if (Application::IsKeyPressed('E') && ui->getInteractable() == true)
		{
			setQuestStatus(true);
		}
		if (getQuestStatus() == false)
		{
			std::cout << "Scene2 Quest inactive." << std::endl;
		}
		else
		{
			std::cout << "Scene2 Quest active." << std::endl;
		}

		if (Application::IsKeyPressed('T'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(SPEED * 10, 0, 0));
		}
		if (Application::IsKeyPressed('G'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(-SPEED * 10, 0, 0));
		}
		if (Application::IsKeyPressed('F'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, 0, -SPEED * 10));
		}
		if (Application::IsKeyPressed('H'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, 0, SPEED * 10));
		}
		if (Application::IsKeyPressed('R'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, SPEED * 10, 0));
		}
		if (Application::IsKeyPressed('Y'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, -SPEED * 10, 0));
		}

		lights[1]->position += Direction * SPEED;
		Cube[0]->SetTranslate(lights[0]->position);
		Cube[1]->SetTranslate(lights[1]->position);
		//Collision::OBBResolution(Cube[0], Cube[1]);
	}

	Ayaka->IsWithinRangeOf(npc);
	npc->Update(dt);
}

void SceneHall::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());

	for (int i = 0; i < 2; i++)
		renderer->SetLight(lights[i], camera.GetPosition());
	//renderer->SetLight(lights[1]);

	Axis->Draw(renderer, false);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}
		
	/*Cube[0]->Draw(renderer, false);
	Cube[1]->Draw(renderer, false);*/
	Environment[EN_FLOOR1]->Draw(renderer, true);
	Environment[EN_FLOOR2]->Draw(renderer, true);
	Environment[EN_FLOOR3]->Draw(renderer, true);
	Environment[EN_FLOOR4]->Draw(renderer, true);
	Environment[EN_FLOOR5]->Draw(renderer, true);
	Environment[EN_FLOOR6]->Draw(renderer, true);
	Environment[EN_TABLE]->Draw(renderer, true);
	Environment[EN_PLANT1]->Draw(renderer, true);
	Environment[EN_PLANT2]->Draw(renderer, true);
	Environment[EN_PLANT3]->Draw(renderer, true);
	Environment[EN_PLANT4]->Draw(renderer, true);

	//Environment[EN_HOUSE5]->Draw(renderer, true);

	//Environment[EN_TOWER1]->Draw(renderer, true);

	Ayaka->Draw(renderer, true);
	
	npc->Draw(renderer, true);

	Collectible->Draw(renderer, true);
	ui->setItem(Collectible);
	if (Ayaka->GetInRange(Collectible, 4))
	{
		ui->setInteractable(true);
		ui->UpdateInteractions(Collectible);
	}
	else 
	{
		ui->setInteractable(false);
		ui->UpdateInteractions(Collectible);
	}

	ui->Draw(renderer, true);
}

void SceneHall::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneHall::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
