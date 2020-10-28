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

	ComponentTransform();
	virtual ~ComponentTransform();

	bool Enable();
	bool Update(float dt);
	bool Disable();

public:
	float4x4 local_transform;
	float4x4 global_transform;
	aiNode* node;
	//aiVector3D translation;
	//aiVector3D scaling;
	//aiQuaternion rotation;
};

#endif // __ComponentTransform_H__