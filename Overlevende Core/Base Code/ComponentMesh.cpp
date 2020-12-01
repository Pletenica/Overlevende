#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "Mesh.h"

#include <vector>
#include "FBXManager.h"
#include "MathGeoLib/src/Geometry/Plane.h"

///WINDOW NOW
ComponentMesh::ComponentMesh(GameObject* _go) :Component(_go)
{
	gameobject = _go;
	type = ComponentType::C_Mesh;
}

// Destructor
ComponentMesh::~ComponentMesh()
{
}

// Called before render is available
bool ComponentMesh::Enable()
{

	return true;
}

// Called before quitting
bool ComponentMesh::Disable()
{

	return true;
}

// Called before quitting
bool ComponentMesh::Update(float dt)
{
	glPushMatrix();
	glMultMatrixf(gameobject->transform->global_transform.Transposed().ptr());
	//////// DRAW NORMALS //////////
	if (drawFaceNormals==true) DrawFaceNormals(mesh);
	if (drawVertexNormals == true) DrawVertexNormals(mesh);

	if (active == true) {
		if (mesh != nullptr) {
			if (ExternalApp->scene_intro->GetActualCameraToCull(ExternalApp->scene_intro->rootGO) == nullptr) {
				mesh->Render();
			}
			else {
				Frustum* _frustum = ExternalApp->scene_intro->GetActualCameraToCull(ExternalApp->scene_intro->rootGO);
				Plane planes[8];
				_frustum->GetPlanes(planes);

				if (isInsideFrustrumOptimized(planes)) {
					mesh->Render();
				}
			}
		}
	}
	glPopMatrix();
	return true;
}

void ComponentMesh::OnEditor(GameObject* _go)
{
	ImVec4 color = ImVec4(0.5f, 0.5f, 1, 1);

	if (ImGui::CollapsingHeader("Mesh Renderer")) {
		ImGui::Checkbox("Active", &this->active);

		ImGui::Separator();

		//Mesh Info
		ImGui::TextColored(color, "Mesh name: ");
		ImGui::SameLine();
		ImGui::Text(mesh->name.c_str());
		ImGui::TextColored(color, "Vertices Count: ");
		ImGui::SameLine();
		ImGui::Text("%i", mesh->num_vertices);
		ImGui::TextColored(color, "Normals Count: ");
		ImGui::SameLine();
		ImGui::Text("%i", mesh->num_normals);
		ImGui::TextColored(color, "Tris Count: ");
		ImGui::SameLine();
		ImGui::Text("%i", mesh->num_indices);
		ImGui::TextColored(color, "Textures Count: ");
		ImGui::SameLine();
		ImGui::Text("%i", mesh->num_textures);
		ImGui::Text(mesh->meshPath.c_str());

		ImGui::Separator();

		//Normals Checkers
		ImGui::Checkbox("Vertex Normals", &drawVertexNormals);
		ImGui::SameLine();
		ImGui::Checkbox("Face Normals", &drawFaceNormals);
	}
}

bool ComponentMesh::isInsideFrustrum(Frustum *_frustrum)
{
	if (_frustrum->Intersects(gameobject->aabb)) return true;
	else return false;
}

bool ComponentMesh::isInsideFrustrumOptimized(const Plane* planes)
{
	AABB* _aabbToUse = &gameobject->aabb;
	for (uint i = 0; i < 6; i++)
	{
		float3 farPoint = float3::zero;
		float3 normal = planes[i].normal;
		farPoint.x = -normal.x >= 0 ? _aabbToUse->maxPoint.x : _aabbToUse->minPoint.x;
		farPoint.y = -normal.y >= 0 ? _aabbToUse->maxPoint.y : _aabbToUse->minPoint.y;
		farPoint.z = -normal.z >= 0 ? _aabbToUse->maxPoint.z : _aabbToUse->minPoint.z;

		if (planes[i].normal.Dot(farPoint) - planes[i].d >= 0.f)
		{
			return false;
		}
	}
	return true;
}

void ComponentMesh::SaveComponent(JsonManager* _man)
{
	Component::SaveComponent(_man);
	
	_man->AddString("Mesh Path", mesh->meshPath.c_str());
}

void ComponentMesh::LoadComponent(JsonManager* _man)
{
	std::string mPath=_man->GetString("Mesh Path");
	mesh = FBXLoader::LoadMeshFromOwnFormat(mPath);
	mesh->GenBuffers(MeshType::FBXNone);
}

void ComponentMesh::DrawVertexNormals(Mesh* _mesh)
{
	float length = 0.2f;
	glBegin(GL_LINES);
	for (size_t a = 0; a < mesh->num_vertices * 3; a += 3)
	{
		glColor3f(0.5f, 0.5f, 1.0f);
		glVertex3f(mesh->vertices[a], mesh->vertices[a + 1], mesh->vertices[a + 2]);

		glVertex3f(mesh->vertices[a] + (mesh->normals[a] * length),
			mesh->vertices[a + 1] + (mesh->normals[a + 1] * length),
			mesh->vertices[a + 2] + (mesh->normals[a + 2]) * length);
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
}

void ComponentMesh::DrawFaceNormals(Mesh* _mesh)
{
	float length = 0.2f;
	glBegin(GL_LINES);
	for (size_t a = 0; a < mesh->num_vertices * 3; a += 3)
	{
		glColor3f(1.0f,0.5f, 0.5f);
		float vx = (mesh->vertices[a] + mesh->vertices[a + 3] + mesh->vertices[a + 6]) / 3;
		float vy = (mesh->vertices[a + 1] + mesh->vertices[a + 4] + mesh->vertices[a + 7]) / 3;
		float vz = (mesh->vertices[a + 2] + mesh->vertices[a + 5] + mesh->vertices[a + 8]) / 3;

		float nx = (mesh->normals[a] + mesh->normals[a + 3] + mesh->normals[a + 6]) / 3;
		float ny = (mesh->normals[a + 1] + mesh->normals[a + 4] + mesh->normals[a + 7]) / 3;
		float nz = (mesh->normals[a + 2] + mesh->normals[a + 5] + mesh->normals[a + 8]) / 3;

		glVertex3f(vx, vy, vz);

		glVertex3f(vx + (mesh->normals[a] * length),
			vy + (mesh->normals[a + 1] * length),
			vz + (mesh->normals[a + 2]) * length);
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
}