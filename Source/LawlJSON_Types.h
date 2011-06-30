#ifndef LAWLJSON_TYPES_H
#define LAWLJSON_TYPES_H

#include "LawlJSON_Settings.h"

#include <map>
#include <vector>
#include <string>

BEGIN_LAWLJSON

// The different types a LJValue can be
//
enum LJType {LJ_STRING, LJ_NUMBER, LJ_OBJECT, LJ_ARRAY, LJ_BOOL, LJ_NULL};

class LJValue;

// For uniformity more than anything else
//
typedef std::map<std::string, LJValue> LJObject;
typedef std::vector<LJValue> LJArray;
typedef std::string LJString;
typedef LJ_NUMBER_TYPE LJNumber;
typedef bool LJBool;

class LJValue
{
public:
	// Management
	//
	LJValue();
	LJValue(const LJString& str);
	LJValue(const char* str);
	LJValue(const LJNumber& num);
	LJValue(const LJObject& obj);
	LJValue(const LJArray& arr);
	LJValue(const LJBool& b);
	LJValue(const LJValue& other);
	~LJValue();

	// Operators
	//
	LJValue& operator=(const LJString& str);
	LJValue& operator=(const char* str);
	LJValue& operator=(const LJNumber& num);
	LJValue& operator=(const LJObject& obj);
	LJValue& operator=(const LJArray& arr);
	LJValue& operator=(const LJBool& b);
	LJValue& operator=(const LJValue& other);
	
	// Setters
	//
	void SetString(const LJString& str);
	void SetString(LJString* str);
	
	void SetNumber(LJNumber num);
	
	void SetObject(const LJObject& obj);
	void SetObject(LJObject* obj);
	
	void SetArray(const LJArray& arr);
	void SetArray(LJArray* arr);
	
	void SetBoolean(LJBool b);
	
	void SetNull();
	
	// Getters
	//
	bool IsNull() const;
	
	// Public properties
	//
	LJType type;
	union 
	{
		LJString*  string;
		LJNumber   number;
		LJObject*  object;
		LJArray*   array;
		LJBool	 boolean;
	};
	
private:
	// Helpers
	//
	void Clean();
};

// Serialization functions
//
void Serialize(const LJString& string, LJString& result, int offset = 0);
void Serialize(const LJNumber& number, LJString& result, int offset = 0);
void Serialize(const LJObject& object, LJString& result, int offset = 0);
void Serialize(const LJArray& array, LJString& result, int offset = 0);
void Serialize(const LJBool& boolean, LJString& result, int offset = 0);
void Serialize(const LJValue& value, LJString& result, int offset = 0);

END_LAWLJSON

#endif