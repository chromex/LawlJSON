#include "LawlJSON_Types.h"

#include <assert.h>
#include <sstream>

BEGIN_LAWLJSON

// Begin LJValue
//

LJValue::LJValue() : type(LJ_NULL)
{}

LJValue::LJValue(const LJString& str) : type(LJ_NULL)
{
	SetString(str);
}

LJValue::LJValue(const char* str) : type(LJ_NULL)
{
	SetString(str);
}

LJValue::LJValue(const LJNumber& num) : type(LJ_NULL)
{
	SetNumber(num);
}

LJValue::LJValue(const LJObject& obj) : type(LJ_NULL)
{
	SetObject(obj);
}

LJValue::LJValue(const LJArray& arr) : type(LJ_NULL)
{
	SetArray(arr);
}

LJValue::LJValue(const LJBool& b) : type(LJ_NULL)
{
	SetBoolean(b);
}

LJValue::LJValue(const LJValue& other) : type(LJ_NULL)
{
	*this = other;
}

LJValue::~LJValue()
{
	Clean();
}

// Operators
//

LJValue& LJValue::operator=( const LJString& str )
{
	SetString(str);
	return *this;
}

LJValue& LJValue::operator=( const char* str )
{
	SetString(str);
	return *this;
}

LJValue& LJValue::operator=( const LJNumber& num )
{
	SetNumber(num);
	return *this;
}

LJValue& LJValue::operator=( const LJObject& obj )
{
	SetObject(obj);
	return *this;
}

LJValue& LJValue::operator=( const LJArray& arr )
{
	SetArray(arr);
	return *this;
}

LJValue& LJValue::operator=( const LJBool& b )
{
	SetBoolean(b);
	return *this;
}

LJValue& LJValue::operator=(const LJValue& other)
{
	Clean();

	type = other.type;

	switch(type)
	{
	case LJ_STRING:
		string = new LJString(*other.string);
		break;
	case LJ_NUMBER:
		number = other.number;
		break;
	case LJ_OBJECT:
		object = new LJObject(*other.object);
		break;
	case LJ_ARRAY:
		array = new LJArray(*other.array);
		break;
	case LJ_BOOL:
		boolean = other.boolean;
		break;
	case LJ_NULL:
		break;
	default:
		assert(false /* Should have one of LJType */);
	}

	return *this;
}

// Setters
//

void LJValue::SetString(const LJString& str)
{
	Clean();
	type = LJ_STRING;
	string = new LJString(str);
}

void LJValue::SetString(LJString* str)
{
	Clean();
	type = LJ_STRING;
	string = str;
}

void LJValue::SetNumber(LJNumber num)
{
	Clean();
	type = LJ_NUMBER;
	number = num;
}

void LJValue::SetObject(const LJObject &obj)
{
	Clean();
	type = LJ_OBJECT;
	object = new LJObject(obj);
}

void LJValue::SetObject(LJObject *obj)
{
	Clean();
	type = LJ_OBJECT;
	object = obj;
}

void LJValue::SetArray(const LJArray &arr)
{
	Clean();
	type = LJ_ARRAY;
	array = new LJArray(arr);
}

void LJValue::SetArray(LJArray *arr)
{
	Clean();
	type = LJ_ARRAY;
	array = arr;
}

void LJValue::SetBoolean(LJBool b)
{
	Clean();
	type = LJ_BOOL;
	boolean = b;
}

void LJValue::SetNull()
{
	Clean();
	type = LJ_NULL;
}

bool LJValue::IsNull() const
{
	return LJ_NULL == type;
}

void LJValue::Clean()
{
	switch(type)
	{
		case LJ_STRING:
			assert(0 != string);
			delete string;
			string = 0;
			break;
		case LJ_NUMBER:
			break;
		case LJ_OBJECT:
			assert(0 != object);
			delete object;
			object = 0;
			break;
		case LJ_ARRAY:
			assert(0 != array);
			delete array;
			array = 0;
			break;
		case LJ_BOOL:
			break;
		case LJ_NULL:
			break;
		default:
			assert(false /* Should have one of LJType */);
	}
}

// End LJValue
//

// Serialization functions
//

LJString OffsetString(int offset, const LJString& str)
{
	return LJString(offset*2, ' ') + str;
}

void Serialize(const LJString& string, LJString& result, int offset)
{
	result += "\"" + string + "\"";
}

void Serialize(const LJNumber& number, LJString& result, int offset)
{
	std::stringstream ss;
	ss << number;
	result += ss.str();
}

void Serialize(const LJObject& object, LJString& result, int offset)
{
	result += OffsetString(offset, "{\n");
	
	for(LJObject::const_iterator entry = object.begin(); entry != object.end(); ++entry)
	{
		if(entry != object.begin())
			result += ",\n";
		
		Serialize((*entry).first, result, offset+1);
		result = OffsetString(offset, result);
		
		result += ":";
		
		Serialize((*entry).second, result, offset+1);
	}

	if(1 == object.size())
		result += "\n";
	
	result += OffsetString(offset, "}");
}

void Serialize(const LJArray& array, LJString& result, int offset)
{
	result += OffsetString(offset, "[\n");
	
	for(LJArray::const_iterator entry = array.begin(); entry != array.end(); ++entry)
	{
		if(entry != array.begin())
			result += ",\n";
		
		Serialize(*entry, result, offset+1);
		result = OffsetString(offset, result);
	}

	if(1 == array.size())
		result += "\n";
	
	result += OffsetString(offset, "]");
}

void Serialize(const LJBool& boolean, LJString& result, int offset)
{
	if(true == boolean)
		result += OffsetString(offset, "true");
	else
		result += OffsetString(offset, "false");
}

void Serialize(const LJValue& value, LJString& result, int offset)
{
	switch(value.type)
	{
		case LJ_STRING:
			Serialize(*value.string, result);
			break;
		case LJ_NUMBER:
			Serialize(value.number, result);
			break;
		case LJ_OBJECT:
			Serialize(*value.object, result);
			break;
		case LJ_ARRAY:
			Serialize(*value.array, result);
			break;
		case LJ_BOOL:
			Serialize(value.boolean, result);
			break;
		case LJ_NULL:
			result += "null";
			break;
		default:
			assert(false /* Should be one of LJType */);
	}
}

// End serialization functions
//

END_LAWLJSON
