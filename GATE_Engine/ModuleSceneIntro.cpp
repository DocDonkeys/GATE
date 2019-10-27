#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "GeometryLoader.h"
#include <math.h>
#include "Application.h"
#include "ComponentMaterial.h"


#ifdef _DEBUG
#ifdef _MMGR_MEM_LEAK
#include "libs/mmgr/mmgr.h"
#endif
#endif

ModuleSceneIntro::ModuleSceneIntro(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	//LOG("Loading Intro assets");
	LOG("Loading Intro assets");
	bool ret = true;

	//Setup camera
	App->camera->Move(vec3(1.0f, 1.0f, 1.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//Create an empty gameobject for test purposes
	CreateEmptyGameObject(10);
	App->geometry_loader->Load3DFile("Assets\\3D_Objects\\Baker_house\\BakerHouse.fbx");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	for (int i = 0; i < game_objects.size(); ++i)
		delete game_objects[i];
	
	game_objects.clear();

	return true;
}

GameObject* ModuleSceneIntro::CreateEmptyGameObject()
{
	GameObject* go = new GameObject();

	game_objects.push_back(go);
	return go;
}

GameObject* ModuleSceneIntro::CreateEmptyGameObject(const char* name)
{
	GameObject* go = new GameObject(name);

	game_objects.push_back(go);
	return go;
}

void ModuleSceneIntro::CreateEmptyGameObject(int num_of_go)
{
	for (int i = 0; i < num_of_go; ++i)
	{
		CreateEmptyGameObject();
	}
}

void ModuleSceneIntro::DestroyGameObject(GameObject * go)
{
	//Set all possible references to the gaemObject to nullptr or out of the array
	if (selected_go == go)
		selected_go = nullptr;

	
	for (int i = 0; i < game_objects.size(); ++i)
	{
		if (game_objects[i] == go)
		{
			game_objects.erase(game_objects.begin() + i);
			break;
		}	
	}

	delete go;
}

bool ModuleSceneIntro::AddTextureToGameObject(GameObject * go, const char* path)
{
	bool has_material_component = false;

	Texture* texture = App->texture_loader->LoadTextureFile(path);

	for (int i = 0; i < go->components.size(); ++i)
	{
		if (go->components[i]->type == COMPONENT_TYPE::MATERIAL)
		{
			ComponentMaterial* material = (ComponentMaterial*)go->GetComponent(COMPONENT_TYPE::MATERIAL);
			material->AssignTexture(texture);
			return true;
		}
	}

	if (!has_material_component)
	{
		ComponentMaterial* material = (ComponentMaterial*)go->CreateComponent(COMPONENT_TYPE::MATERIAL);
		material->AssignTexture(texture);
		return true;
	}

	return false;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	toolMode = CheckToolMode();

	//Ground Render	(Used the Primitives Container)
	/*Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();*/

	for (int i = 0; i < game_objects.size(); ++i)
		game_objects[i]->Update();

	return UPDATE_CONTINUE;
}

// Update
update_status ModuleSceneIntro::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

int ModuleSceneIntro::CheckToolMode() const
{
	int ret = toolMode;

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		ret = (int)tool_mode::DRAG;
	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		ret = (int)tool_mode::MOVE;
	else if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		ret = (int)tool_mode::ROTATE;
	else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		ret = (int)tool_mode::SCALE;
	else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		ret = (int)tool_mode::RECT;
	else if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_IDLE)	// To avoid calling on Redo (CTRL+Y)
		ret = (int)tool_mode::MULTI;

	return ret;
}