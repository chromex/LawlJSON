#include "LawlJSON_Types.h"

#include <assert.h>

BEGIN_LAWLJSON

// Begin LJValue
//

LJValue::LJValue() : type(LJ_NO_VALUE)
{}

LJValue::LJValue(const LJValue& other) : type(LJ_NO_VALUE)
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
        case LJ_NO_VALUE:
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
        case LJ_NO_VALUE:
            break;
        default:
            assert(false /* Should have one of LJType */);
    }
}

// End LJValue
//

END_LAWLJSON