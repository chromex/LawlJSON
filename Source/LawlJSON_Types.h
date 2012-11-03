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
	void SetString();
	
	void SetNumber(LJNumber num);
	
	void SetObject(const LJObject& obj);
	void SetObject(LJObject* obj);
	void SetObject();
	
	void SetArray(const LJArray& arr);
	void SetArray(LJArray* arr);
	void SetArray();
	
	void SetBoolean(LJBool b);
	
	void SetNull();
	
	// Public properties
	//
	LJString& string();
	const LJString& string() const;
	LJNumber& number();
	const LJNumber& number() const;
	LJObject& object();
	const LJObject& object() const;
	LJArray& array();
	const LJArray& array() const;
	LJBool& boolean();
	const LJBool& boolean() const;

	LJType type() const;
	int LineNumber() const;
	void SetLineNumber(int lineNumber);

	// Tests
	//
	bool IsString() const;
	bool IsNumber() const;
	bool IsObject() const;
	bool IsArray() const;
	bool IsBoolean() const;
	bool IsNull() const;

	bool IsNumberArray() const;
	bool IsStringArray() const;
	
private:
	// Helpers
	//
	void Clean();

	LJType _type;
	union 
	{
		LJString*  _string;
		LJNumber   _number;
		LJObject*  _object;
		LJArray*   _array;
		LJBool	   _boolean;
	};
	int _lineNumber;
};

END_LAWLJSON

#endif