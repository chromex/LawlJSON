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
    LJValue(const LJNumber& num);
    LJValue(const LJObject& obj);
    LJValue(const LJArray& arr);
    LJValue(const LJBool& b);
    LJValue(const LJValue& other);
    LJValue& operator=(const LJValue& other);
    ~LJValue();
    
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
        LJBool     boolean;
    };
    
private:
    // Helpers
    //
    void Clean();
};

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