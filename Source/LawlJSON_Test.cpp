#include "LawlJSON_Test.h"
#include "LawlJSON.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

BEGIN_LAWLJSON

// Management
//

LawlJSON_Test::LawlJSON_Test()
: _message(0)
{}

LawlJSON_Test& LawlJSON_Test::Inst()
{
    static LawlJSON_Test inst;
    return inst;
}

LawlJSON_Test::~LawlJSON_Test()
{
    if(0 != _message)
    {
        delete[] _message;
    }
}

// Methods
//

bool LawlJSON_Test::Verify(bool outputToConsole)
{
    _outputToConsole = outputToConsole;
    
    if(!TestSerialization())
        return false;
    
    return true;
}

const char* LawlJSON_Test::ErrorMessage() const
{
    return _message;
}

// Helpers
//

bool LawlJSON_Test::TestSerialization()
{
    SetErrorMessage("Begin testing serialization");
    
    SetErrorMessage("Constructing JSON tree");
    
    LJValue root = LJObject();
    (*root.object)["name"] = LJString("Chaos");
    (*root.object)["function"] = LJString("Be Awesome");
    (*root.object)["howHigh?"] = 9001.0;
    (*root.object)["tooTrue?"] = false;
    (*root.object)["true"] = true;
    (*root.object)["isNull"] = LJValue();
    
    LJString result;
    Serialize(root, result);
    SetErrorMessage(result.c_str());
    
    return true;
}

void LawlJSON_Test::SetErrorMessage(const char *message)
{
    assert(0 != message);
    
    if(0 != _message)
    {
        delete[] _message;
    }
    
    _message = new char[strlen(message)];
    strcpy(_message, message);
    
    if(_outputToConsole)
    {
        printf("%s\n", _message);
    }
}

END_LAWLJSON