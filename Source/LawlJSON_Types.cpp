#include "LawlJSON_Types.h"

#include <assert.h>

BEGIN_LAWLJSON

// Begin LJValue
//

LJValue::LJValue() : type(LJ_NULL)
{}

LJValue::LJValue(const LJString& str) : type(LJ_NULL)
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

LJValue::~LJValue()
{
    Clean();
}

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

void Serialize(const LJString& string, LJString& result)
{
    result += "\"" + string + "\"";
}

void Serialize(const LJNumber& number, LJString& result)
{
    result += number;
}

void Serialize(const LJObject& object, LJString& result)
{
    result += "{";
    
    for(LJObject::const_iterator entry = object.begin(); entry != object.end(); ++entry)
    {
        if(entry != object.begin())
            result += ",";
        
        Serialize((*entry).first, result);
        
        result += ":";
        
        Serialize((*entry).second, result);
    }
    
    result += "}";
}

void Serialize(const LJArray& array, LJString& result)
{
    result += "[";
    
    for(LJArray::const_iterator entry = array.begin(); entry != array.end(); ++entry)
    {
        if(entry != array.begin())
            result += ",";
        
        Serialize(*entry, result);
    }
    
    result += "]";
}

void Serialize(const LJBool& boolean, LJString& result)
{
    if(true == boolean)
        result += "true";
    else
        result += "false";
}

void Serialize(const LJValue& value, LJString& result)
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
