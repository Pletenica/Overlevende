#ifndef __ComponentTransform_H__
#define __ComponentTransform_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"

class aiNode;
#include "lib/Assimp/include/vector3.h"
#include "lib/Assimp/include/quaternion.h"
#include "lib/MathGeoLib/Math/float4x4.h"

class ComponentTransform : public Component
{
public:

	ComponentTransform(GameObject* _go);
	virtual ~ComponentTransform();

	bool Enable();
	bool Update(float dt);
	bool Disable();
	void OnEditor(GameObject* _go);

	void SetTransform(float3 pos, Quat rot, float3 scale);
	void RecursiveUpdateTransform(float3 _pos, Quat _rot, float3 _scale);

	void ResetTransform();

public:
	float4x4 local_transform;
	float4x4 global_transform;

public:
	float3 position;
	float3 rotation;
	float3 scale;
};

#endif // __ComponentTransform_H__