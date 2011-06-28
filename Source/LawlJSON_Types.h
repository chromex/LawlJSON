#ifndef LAWLJSON_TYPES_H
#define LAWLJSON_TYPES_H

#include "LawlJSON_Settings.h"

#include <map>
#include <vector>
#include <string>

BEGIN_LAWLJSON

// The different types a LJValue can be
//
enum LJType {LJ_STRING, LJ_NUMBER, LJ_OBJECT, LJ_ARRAY, LJ_BOOL, LJ_NULL, LJ_NO_VALUE};

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

END_LAWLJSON

#endif