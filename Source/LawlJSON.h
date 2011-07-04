#ifndef LAWLJSON_H
#define LAWLJSON_H

#include "LawlJSON_Settings.h"
#include "LawlJSON_Types.h"

BEGIN_LAWLJSON

void ParseJSON(LJValue& result, const char* json);

// Serialization functions
//
void Serialize(const LJString& string, LJString& result);
void Serialize(const LJNumber& number, LJString& result);
void Serialize(const LJObject& object, LJString& result);
void Serialize(const LJArray& array, LJString& result);
void Serialize(const LJBool& boolean, LJString& result);
void Serialize(const LJValue& value, LJString& result);

END_LAWLJSON

#endif