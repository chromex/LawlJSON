#ifndef LAWLJSON_LEXER_H
#define LAWLJSON_LEXER_H

#include "LawlJSON_Settings.h"
#include "LawlJSON_Tokens.h"
#include "LawlJSON_Types.h"

BEGIN_LAWLJSON

class LJLexer
{
public:
	LJLexer(const char *src);
	~LJLexer();

	/* Modifiers */
	void         Next();

	/* Accessors */
	LJTOKEN      Token() const;
	int          Line() const;

	const LJString& Data() const { return _data; }
	double Number() const { return _number; }

private:
	/* Helpers */
	bool ParseIdent();
	bool ParseNum();
	bool IsComment();

	const char*  _src;
	std::string  _data;
	int          _line;
	LJTOKEN      _token;
	double       _number;
};

END_LAWLJSON

#endif
