#include "LawlJSON_Lexer.h"
#include "LawlJSON_Exception.h"

#include <string.h>
#include <stdlib.h>
#include <exception>
#include <assert.h>
#include <sstream>

BEGIN_LAWLJSON

/* Local macros */
#define WHITESPACE(C) ((C) == ' ' || (C) == '\t' || (C) == '\n' || (C) == '\r')
#define SINGLE(T) {_token = (T);++_src;}
#define RESERVED(S, T) if(len == strlen(S) && strncmp(_src, (S), len) == 0) { _token = (T); _src+=len; return true; }

LJLexer::LJLexer(const char *src)
	: _src(src), _line(1), _token(TOKEN_EOF)
{
	assert(src);

	Next();
}

LJLexer::~LJLexer()
{}

void LJLexer::Next()
{
	while(*_src != '\0')
	{
		// Burn whitespace
		while(WHITESPACE(*_src) || IsComment())
		{
			if(IsComment())
			{
				while(*_src != '\n')
				{
					++_src;
				}
			}

			if(*_src == '\n')
				++_line;
			++_src;
		}

		switch(*_src)
		{
		case '[': SINGLE(TOKEN_LSQBRACKET); return;
		case ']': SINGLE(TOKEN_RSQBRACKET); return;
		case '{': SINGLE(TOKEN_LBRACKET); return;
		case '}': SINGLE(TOKEN_RBRACKET); return;
		case ':': SINGLE(TOKEN_COLON); return;
		case ',': SINGLE(TOKEN_COMMA); return;
		case '\0': SINGLE(TOKEN_EOF); return;
		default:
			if(!ParseIdent() && !ParseNum())
			{
				std::stringstream ss;
				ss << "lexical analyzer failed at: " << _src;
				++_src;
				throw LJException(ss.str().c_str());
			}
			else
			{
				return;
			}
		};
	}
	_token = TOKEN_EOF;
}


LJTOKEN LJLexer::Token() const
{
	return _token;
}

int LJLexer::Line() const
{
	return _line;
}

bool LJLexer::ParseNum()
{
	const char* valid = "0123456789.Ee+";
	const char* reset = _src;

	double mult = 1;
	if('-' == *_src)
	{
		mult = -1;
		++_src;
	}

	int len = strspn(_src, valid);
	if(len == 0)
	{
		_src = reset;
		return false;
	}
	_number = atof(_src) * mult;
	_token = TOKEN_NUMBER;
	_src += len;

	return true;
}

LJString UnEscape(const LJString& str)
{
	LJString result;

	for(const char* cstr = str.c_str(); *cstr != 0; ++cstr)
	{
		if('\\' == *cstr)
		{
			char n = *(++cstr);
			switch(n)
			{
			case 'b':
				result += '\b';
				break;
			case 'f':
				result += '\f';
				break;
			case 'n':
				result += '\n';
				break;
			case 'r':
				result += '\r';
				break;
			case 't':
				result += '\t';
				break;
			case '"':
				result += '"';
				break;
			case '/':
				result += '/';
				break;
			case '\\':
				result += '\\';
				break;
			default:
				std::stringstream ss;
				ss << "lexical analyzer failed while un-escaping string: " << str;
				throw LJException(ss.str().c_str());
			}
		}
		else
		{
			result += *cstr;
		}
	}

	return result;
}

bool LJLexer::ParseIdent()
{
	const char* reset = _src;

	// Check begin quote
	char firstChar = *_src;
	if('"' != firstChar)
	{
		if(firstChar == 't' || firstChar == 'f' || firstChar == 'n')
		{
			const char* chars = "truefalsnu";
			int len = strspn(_src, chars);

			// Check reserved words
			RESERVED("true", TOKEN_TRUE);
			RESERVED("false", TOKEN_FALSE);
			RESERVED("null", TOKEN_NULL);
		}

		return false;
	}
	++_src;

	// Find the end, verify along the way
	int nLines = 0;
	const char* ptr;
	bool escaped = false;
	for(ptr = _src; ptr != 0; ++ptr)
	{
		char c = *ptr;
		if(isprint(c) || (isspace(c) && '\v' != c) || '\b' == c)
		{
			if('\\' == c && !escaped)
			{
				char n = *(ptr+1);
				if('"' != n && '\\' != n && '/' != n && 'b' != n && 'f' != n && 'n' != n && 'r' != n && 't' != n)
				{
					_src = reset;
					return false;
				}
				else
				{
					escaped = true;
					continue;
				}
			}
			else if('"' == c && !escaped)
			{
				// End found
				break;
			}
			else if('n' == c && escaped)
			{
				++nLines;
			}
		}
		else
		{
			_src = reset;
			return false;
		}

		escaped = false;
	}

	if(0 == *ptr)
	{
		_src = reset;
		return false;
	}

	int len = ptr - _src;

	_line += nLines;
	_data = LJString(_src, len);
	_data = UnEscape(_data);
	_src += len+1;
	_token = TOKEN_STRING;

	return true;
}

bool LJLexer::IsComment()
{
	return (*_src == '/' && *(_src+1) == '/');
}

#undef WHITESPACE
#undef SINGLE
#undef RESERVED

END_LAWLJSON

