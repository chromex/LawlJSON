#ifndef LAWLJSON_TEST_H
#define LAWLJSON_TEST_H

#include "LawlJSON_Settings.h"

BEGIN_LAWLJSON

class LawlJSON_Test
{
public:
	// Management
	//
	static LawlJSON_Test& Inst();
	~LawlJSON_Test();
	
	// Methods
	//
	bool Verify(bool outputToConsole);
	const char* ErrorMessage() const;
	
private:
	// Singleton protection
	//
	LawlJSON_Test();
	LawlJSON_Test(const LawlJSON_Test& other) {}
	LawlJSON_Test& operator=(const LawlJSON_Test& other) {return *this;}
	
	// Helpers
	//
	bool TestSerialization();
	void SetErrorMessage(const char* message);
	
	// Members
	//
	char* _message;
	bool _outputToConsole;
};

END_LAWLJSON

#endif