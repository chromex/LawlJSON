#include "LawlJSON_Types.h"
#include "LawlJSON_Exception.h"

#include <assert.h>

BEGIN_LAWLJSON

// Begin LJValue
//

LJValue::LJValue() : _type(LJ_NULL), _lineNumber(-1)
{}

LJValue::LJValue(const LJString& str) : _type(LJ_NULL)
{
	SetString(str);
}

LJValue::LJValue(const char* str) : _type(LJ_NULL)
{
	SetString(str);
}

LJValue::LJValue(const LJNumber& num) : _type(LJ_NULL)
{
	SetNumber(num);
}

LJValue::LJValue(const LJObject& obj) : _type(LJ_NULL)
{
	SetObject(obj);
}

LJValue::LJValue(const LJArray& arr) : _type(LJ_NULL)
{
	SetArray(arr);
}

LJValue::LJValue(const LJBool& b) : _type(LJ_NULL)
{
	SetBoolean(b);
}

LJValue::LJValue(const LJValue& other) : _type(LJ_NULL)
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

	_type = other._type;

	switch(_type)
	{
	case LJ_STRING:
		_string = new LJString(*other._string);
		break;
	case LJ_NUMBER:
		_number = other._number;
		break;
	case LJ_OBJECT:
		_object = new LJObject(*other._object);
		break;
	case LJ_ARRAY:
		_array = new LJArray(*other._array);
		break;
	case LJ_BOOL:
		_boolean = other._boolean;
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
	_type = LJ_STRING;
	_string = new LJString(str);
}

void LJValue::SetString(LJString* str)
{
	Clean();
	_type = LJ_STRING;
	_string = str;
}

void LJValue::SetString()
{
	SetString("");
}

void LJValue::SetNumber(LJNumber num)
{
	Clean();
	_type = LJ_NUMBER;
	_number = num;
}

void LJValue::SetObject(const LJObject &obj)
{
	Clean();
	_type = LJ_OBJECT;
	_object = new LJObject(obj);
}

void LJValue::SetObject(LJObject *obj)
{
	Clean();
	_type = LJ_OBJECT;
	_object = obj;
}

void LJValue::SetObject()
{
	Clean();
	_type = LJ_OBJECT;
	_object = new LJObject();
}

void LJValue::SetArray(const LJArray &arr)
{
	Clean();
	_type = LJ_ARRAY;
	_array = new LJArray(arr);
}

void LJValue::SetArray(LJArray *arr)
{
	Clean();
	_type = LJ_ARRAY;
	_array = arr;
}

void LJValue::SetArray()
{
	Clean();
	_type = LJ_ARRAY;
	_array = new LJArray();
}

void LJValue::SetBoolean(LJBool b)
{
	Clean();
	_type = LJ_BOOL;
	_boolean = b;
}

void LJValue::SetNull()
{
	Clean();
	_type = LJ_NULL;
}

LJString& LJValue::string()
{
	if(LJ_STRING != _type) {
		throw LJException("Type is not a string");
	}
	assert(_string);
	return *_string;
}

const LJString& LJValue::string() const
{
	return const_cast<LJValue*>(this)->string();
}

LJNumber& LJValue::number()
{
	if(LJ_NUMBER != _type) {
		throw LJException("Type is not a number");
	}
	return _number;
}

const LJNumber& LJValue::number() const
{
	return const_cast<LJValue*>(this)->number();
}

LJObject& LJValue::object()
{
	if(LJ_OBJECT != _type) {
		throw LJException("Type is not an object");
	}
	assert(_object);
	return *_object;
}

const LJObject& LJValue::object() const
{
	return const_cast<LJValue*>(this)->object();
}

LJArray& LJValue::array()
{
	if(LJ_ARRAY != _type) {
		throw LJException("Type is not an array");
	}
	assert(_array);
	return *_array;
}

const LJArray& LJValue::array() const
{
	return const_cast<LJValue*>(this)->array();
}

LJBool& LJValue::boolean()
{
	if(LJ_BOOL != _type) {
		throw LJException("Type is not a boolean");
	}
	return _boolean;
}

const LJBool& LJValue::boolean() const
{
	return const_cast<LJValue*>(this)->boolean();
}

LJType LJValue::type() const
{
	return _type;
}

int LJValue::LineNumber() const
{
	return _lineNumber;
}

void LJValue::SetLineNumber(int lineNumber)
{
	_lineNumber = lineNumber;
}

bool LJValue::IsString() const
{
	return LJ_STRING == _type;
}

bool LJValue::IsNumber() const
{
	return LJ_NUMBER == _type;
}

bool LJValue::IsObject() const
{
	return LJ_OBJECT == _type;
}

bool LJValue::IsArray() const
{
	return LJ_ARRAY == _type;
}

bool LJValue::IsBoolean() const
{
	return LJ_BOOL == _type;
}

bool LJValue::IsNull() const
{
	return LJ_NULL == _type;
}

bool LJValue::IsNumberArray() const
{
	if(!IsArray())
		return false;

	const LJArray& arr = array();
	for(LJArray::const_iterator entry = arr.begin(); entry != arr.end(); ++entry) 
	{
		if(!entry->IsNumber())
			return false;
	}

	return true;
}

bool LJValue::IsStringArray() const
{
	if(!IsArray())
		return false;

	const LJArray& arr = array();
	for(LJArray::const_iterator entry = arr.begin(); entry != arr.end(); ++entry) 
	{
		if(!entry->IsString())
			return false;
	}

	return true;
}

void LJValue::Clean()
{
	switch(_type)
	{
		case LJ_STRING:
			assert(0 != _string);
			delete _string;
			_string = 0;
			break;
		case LJ_NUMBER:
			break;
		case LJ_OBJECT:
			assert(0 != _object);
			delete _object;
			_object = 0;
			break;
		case LJ_ARRAY:
			assert(0 != _array);
			delete _array;
			_array = 0;
			break;
		case LJ_BOOL:
			break;
		case LJ_NULL:
			break;
		default:
			assert(false /* Should have one of LJType */);
	}
}

END_LAWLJSON
