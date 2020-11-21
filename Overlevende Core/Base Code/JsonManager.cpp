#include "JsonManager.h"

JsonManager::JsonManager(JSON_Object* _object)
{
	bObject = _object;
}

JsonManager::~JsonManager()
{
}

void JsonManager::AddFloat(const char* name, float value)
{
	json_object_set_number(bObject, name, value);
}

float JsonManager::GetFloat(const char* name)
{
	return 	json_object_get_number(bObject, name);
}

void JsonManager::AddInt(const char* name, int value)
{
	json_object_set_number(bObject, name, value);
}

int JsonManager::GetInt(const char* name)
{
	return 	json_object_get_number(bObject, name);
}

void JsonManager::AddString(const char* name, const char* value)
{
	json_object_set_string(bObject, name, value);
}

const char* JsonManager::GetString(const char* name)
{
	return 	json_object_get_string(bObject, name);
}

void JsonManager::AddBool(const char* name, bool value)
{
	json_object_set_boolean(bObject, name, value);
}

bool JsonManager::GetBool(const char* name)
{
	return 	json_object_get_boolean(bObject, name);
}

void JsonManager::AddVector3(const char* name, float3 value)
{
	JSON_Value* valAr = json_value_init_array();
	JSON_Array* vecArray = json_value_get_array(valAr);

	for (size_t i = 0; i < 3; i++)
	{
		json_array_append_number(vecArray, value[i]);
	}

	json_object_set_value(bObject, name, valAr);
}

float3 JsonManager::GetVector3(const char* name)
{
	JSON_Array* lmaoArray = json_object_get_array(bObject, name);
	return float3(json_array_get_number(lmaoArray, 0), json_array_get_number(lmaoArray, 1), json_array_get_number(lmaoArray, 2));
}

void JsonManager::AddQuaternion(const char* name, Quat value)
{
	JSON_Value* valAr = json_value_init_array();
	JSON_Array* vecArray = json_value_get_array(valAr);

	for (size_t i = 0; i < 4; i++)
	{
		json_array_append_number(vecArray, value.ptr()[i]);
	}

	json_object_set_value(bObject, name, valAr);
}

Quat JsonManager::GetQuaternion(const char* name)
{
	JSON_Array* lmaoArray = json_object_get_array(bObject, name);
	return Quat(json_array_get_number(lmaoArray, 0), json_array_get_number(lmaoArray, 1), json_array_get_number(lmaoArray, 2), json_array_get_number(lmaoArray, 3));
}

JSON_Array* JsonManager::GetArray(const char* name)
{
	return json_object_get_array(bObject, name);
}
