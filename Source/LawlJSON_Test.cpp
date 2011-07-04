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
	root.object()["name"] = "Chaos \"is epic\"";
	root.object()["function"] = "Be\t Awesome\\";
	root.object()["howHigh?"] = 9001.0;
	root.object()["tooTrue?"] = false;
	root.object()["true"] = true;
	root.object()["isNull"] = LJValue();
	LJArray arr;
	arr.push_back(99.234);
	arr.push_back("Who");
	arr.push_back(true);
	arr.push_back(root);
	arr.push_back(LJArray());
	root.object()["Arr!"] = arr;
	
	SetErrorMessage("Serializing tree");
	LJString result;
	Serialize(root, result);
	SetErrorMessage("Serialization results:");
	SetErrorMessage(result.c_str());
	if(LJString("{\"Arr!\":[99.234,\"Who\",true,{\"function\":\"Be Awesome\",\"howHigh?\":9001,\"isNull\":null,\"name\":\"Chaos\",\"tooTrue?\":false,\"true\":true},[]],\"function\":\"Be Awesome\",\"howHigh?\":9001,\"isNull\":null,\"name\":\"Chaos\",\"tooTrue?\":false,\"true\":true}").compare(result) == 0)
	{
		SetErrorMessage("Generated correct serialization");
	}
	else
	{
		SetErrorMessage("Generated incorrect serialization");
	}

	LJValue parsedFile;
	try
	{
		ParseJSON(parsedFile, result.c_str());
		LJString r2;
		Serialize(parsedFile, r2);
		SetErrorMessage("Parsing results:");
		SetErrorMessage(r2.c_str());
	}
	catch(std::exception& e)
	{
		SetErrorMessage(e.what());
	}
	
	return true;
}

void LawlJSON_Test::SetErrorMessage(const char *message)
{
	if(0 != _message)
	{
		delete[] _message;
	}
	
	_message = new char[strlen(message)+1];
	strcpy(_message, message);
	
	if(_outputToConsole)
	{
		printf("%s\n", _message);
	}
}

END_LAWLJSON