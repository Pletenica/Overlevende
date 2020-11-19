#pragma once

#include"Parson/parson.h"
#include"MathGeoLib/Math/float3.h"
#include"MathGeoLib/Math/Quat.h"

class JsonManager
{
public:
	JsonManager(JSON_Object* _object);
	~JsonManager();

	void AddFloat(const char* name, float value);
	float GetFloat(const char* name);

	void AddInt(const char* name, int value);
	int GetInt(const char* name);

	void AddString(const char* name, const char* value);
	const char* GetString(const char* name);

	void AddBool(const char* name, bool value);
	bool GetBool(const char* name);

	void AddVector3(const char* name, float3 value);
	float3 GetVector3(const char* name);

	void AddQuaternion(const char* name, Quat value);
	Quat GetQuaternion(const char* name);

	JSON_Object* GetbObject() { return bObject; }

private:
	JSON_Object* bObject;

};