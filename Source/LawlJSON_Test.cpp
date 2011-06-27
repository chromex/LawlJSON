#include "LawlJSON_Test.h"
#include "LawlJSON.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

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
    
    SetErrorMessage("No implemented tests");
    
    return false;
}

const char* LawlJSON_Test::ErrorMessage() const
{
    return _message;
}

// Helpers
//

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