#include "LawlJSON_Test.h"

#include <iostream>

using namespace std;
using namespace LawlJSON;

int main(int argc, char **argv)
{
	cout << "Begin LawlJSON Tests" << endl;
	cout << "====================" << endl << endl;
	
	if(LawlJSON_Test::Inst().Verify(true))
	{
        cout << endl;
		cout << "*** LawlJSON successfully verified ***" << endl;
	}
	else
	{
        cout << endl;
		cout << "*** LawlJSON failed to verify ***" << endl;
        cout << "Failed with:" << endl;
        cout << LawlJSON_Test::Inst().ErrorMessage() << endl;
	}
	
    cout << endl;
	cout << "=================" << endl;
	cout << "End LawlJSON Test" << endl;
	
	return 0;
}