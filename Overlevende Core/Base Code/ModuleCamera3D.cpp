#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ComponentTransform.h"
#include "ModuleGameObject.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

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
	vec3 CameraLocation = { 10, 10, 10 };
	Look((CameraLocation), AxisLocation, false);

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

	vec3 newPos(0, 0, 0);
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
				vec3 center(c_trans->position.x, c_trans->position.y, c_trans->position.z);
				LookAt(center);
			}
		}
	}

	/////////// CAMERA MOVEMENT ////////////
	if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))
		newPos -= Z * move_speed * speed_multiplier * dt;
	if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT))
		newPos += Z * move_speed * speed_multiplier * dt;
	if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
		newPos += X * move_speed * speed_multiplier * dt;
	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))
		newPos -= X * move_speed * speed_multiplier * dt;

	/////////// DRAG ////////////
	if ((App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT))
	{
		newPos -= X * App->input->GetMouseXMotion() * speed_multiplier * drag_speed * dt;
		newPos += Y * App->input->GetMouseYMotion() * speed_multiplier * drag_speed * dt;
	}

	/////////// ZOOOOM ////////////
	if (App->input->GetMouseZ() > 0)
		newPos -= Z * zoom_speed * dt;
	else if (App->input->GetMouseZ() < 0)
		newPos += Z * zoom_speed * dt;

	Position += newPos;
	Reference += newPos;

	/////////// CAMERAS NORMAL ROTATION ////////////
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		if (dx != 0)
		{
			float DeltaX = (float)dx * sensitivity * dt;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * sensitivity * dt;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}
	}

	/////////// ALT CAMERAS OPTIONS ////////////
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		//Reset View to 0,0,0
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
			LookAt(vec3(0, 0, 0));
		}

		//Orbit around the geometry
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			Position -= Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * sensitivity * dt;

				X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * sensitivity * dt;

				Y = rotate(Y, DeltaY, X);
				Z = rotate(Z, DeltaY, X);

				if (Y.y < 0.0f)
				{
					Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Y = cross(Z, X);
				}
			}

			Position = Reference + Z * length(Position);
		}
	}

	CalculateViewMatrix();
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

void ModuleCamera3D::SetBackgroundColor(float r, float g, float b, float w)
{
	background = { r,g,b,w };
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}