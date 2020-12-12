#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ComponentTransform.h"
#include "ModuleGameObject.h"
#include "ModuleInput.h"
#include "ModuleBaseMotor.h"
#include "InspectorWindow.h"

#include"JsonManager.h"
#include"MathGeoLib/src/Math/Quat.h"
#include "MathGeoLib/src/Math/float3.h"
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "MathGeoLib/src/Math/float4x4.h"
#include "glmath.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled), _cam(float3::zero)
{
	Position = float3(0.0f, 0.0f, 0.0f);
	Reference = float3(0.0f, 0.0f, 0.0f);

	background = { 0.1f, 0.1f, 0.1f, 1.0f };
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;
	vec3 AxisLocation = { 0, 0, 0 };
	/*vec3 CameraLocation = { 10, 10, 10 };*/
	/*Look((CameraLocation), AxisLocation, false);*/

	move_speed = 5;
	drag_speed = 0.75f;
	zoom_speed = 30;
	sensitivity = 5;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}


// -----------------------------------------------------------------
update_status ModuleCamera3D::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}


// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
		// Now we can make this movememnt frame rate independant!

	float3 newPos(0, 0, 0);
	int speed_multiplier = 1;

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed_multiplier = 2;

	/////////// FOCUS CAMERA ////////////
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		if (App->base_motor->inspector_window->_selectedGO != nullptr)
		{
			ComponentTransform* c_trans = (ComponentTransform*)App->base_motor->inspector_window->_selectedGO->GetComponent(ComponentType::C_Transform);
			if (c_trans != nullptr) {
				float3 pos, scale;
				Quat rot;
				c_trans->global_transform.Decompose(pos, rot, scale);
				float3 center(pos.x, pos.y, pos.z);
				LookAt(center);
			}
		}
	}

	/////////// CAMERA MOVEMENT ////////////
	if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))
		newPos += _cam.frustum.front * move_speed * speed_multiplier * dt;
	if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT))
		newPos -= _cam.frustum.front * move_speed * speed_multiplier * dt;
	if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
		newPos += _cam.frustum.WorldRight() * move_speed * speed_multiplier * dt;
	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))
		newPos -= _cam.frustum.WorldRight() * move_speed * speed_multiplier * dt;

	/////////// DRAG ////////////
	if ((App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT))
	{
		newPos -= _cam.frustum.WorldRight() * App->input->GetMouseXMotion() * speed_multiplier * drag_speed * dt;
		newPos += _cam.frustum.up * App->input->GetMouseYMotion() * speed_multiplier * drag_speed * dt;
	}

	/////////// ZOOOOM ////////////
	if (App->input->GetMouseZ() > 0)
		newPos += _cam.frustum.front * zoom_speed * dt;
	else if (App->input->GetMouseZ() < 0)
		newPos -= _cam.frustum.front * zoom_speed * dt;

	///////// CAMERAS NORMAL ROTATION ////////////
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion() / sensitivity;
		int dy = -App->input->GetMouseYMotion() / sensitivity;

		Quat dir;
		_cam.frustum.WorldMatrix().Decompose(float3(), dir, float3());

		Quat Y;
		Y.SetFromAxisAngle(float3(1, 0, 0), dy * DEGTORAD);
		dir = dir * Y;

		Quat X;
		X.SetFromAxisAngle(float3(0, 1, 0), dx * DEGTORAD);
		dir = X * dir;

		float4x4 changedMatrix = _cam.frustum.WorldMatrix();
		changedMatrix.SetRotatePart(dir.Normalized());
		_cam.frustum.SetWorldMatrix(changedMatrix.Float3x4Part());


	}


	/////////// ALT CAMERAS OPTIONS ////////////
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		//Reset View to 0,0,0
		//if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) 
		//{
		//	LookAt(float3(0, 0, 0));
		//}

		//Orbit around the geometry
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float3 point = float3(0, 0, 0);
			if (App->base_motor->inspector_window->_selectedGO != nullptr) {
				point = App->base_motor->inspector_window->_selectedGO->transform->position;
			}

			float dist = _cam.frustum.pos.Distance(point);

			Quat dir = Quat::identity;
			_cam.frustum.WorldMatrix().Decompose(float3(), dir, float3());

			if (dy != 0)
			{
				float DeltaY = (float)dy * sensitivity * dt;

				Quat y;
				y.SetFromAxisAngle(float3(1, 0, 0), DeltaY * DEGTORAD);
				dir = dir * y;
			}

			if (dx != 0)
			{
				float DeltaX = (float)dx * sensitivity * dt;

				Quat x;
				x.SetFromAxisAngle(float3(0, 1, 0), DeltaX * DEGTORAD);
				dir = x * dir;
			}

			float4x4 changeMatrix = _cam.frustum.WorldMatrix();
			changeMatrix.SetRotatePart(dir.Normalized());
			_cam.frustum.SetWorldMatrix(changeMatrix.Float3x4Part());

			_cam.frustum.pos = point + (_cam.frustum.front * -dist);
			LookAt(point);
		}
	}

	_cam.frustum.pos += newPos;
	Reference += newPos;

	return UPDATE_CONTINUE;
}

//// -----------------------------------------------------------------
//void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
//{
//	this->Position = Position;
//	this->Reference = Reference;
//
//	Z = normalize(Position - Reference);
//	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
//	Y = cross(Z, X);
//
//	if(!RotateAroundReference)
//	{
//		this->Reference = this->Position;
//		this->Position += Z * 0.05f;
//	}
//
//}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const float3 &Spot)
{
	_cam.frustum.front = (Spot - _cam.frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(_cam.frustum.front).Normalized();
	_cam.frustum.up = _cam.frustum.front.Cross(X);
	Reference = Spot;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3 &Movement)
{
	_cam.frustum.pos += Movement;
	Reference += Movement;
}



void ModuleCamera3D::SetBackgroundColor(float r, float g, float b, float w)
{
	background = { r,g,b,w };
}

void ModuleCamera3D::SaveCamera(JSON_Array* _goArray)
{
	JSON_Value* _val = json_value_init_object();
	JsonManager _man(json_value_get_object(_val));

	json_array_append_value(_goArray, _val);

	_man.AddVector3("Camera Position", _cam.frustum.pos);

	Quat rot = Quat::identity;
	_cam.frustum.WorldMatrix().Decompose(float3(), rot, float3());
	_man.AddQuaternion("Camera Rotation", rot);
}

void ModuleCamera3D::LoadCamera(JsonManager* _man)
{
	_cam.frustum.pos = _man->GetVector3("Camera Position");

	Quat rot = Quat::identity;
	rot = _man->GetQuaternion("Camera Rotation");

	float4x4 changeMatrix = _cam.frustum.WorldMatrix();
	changeMatrix.SetRotatePart(rot.Normalized());
	_cam.frustum.SetWorldMatrix(changeMatrix.Float3x4Part());
}