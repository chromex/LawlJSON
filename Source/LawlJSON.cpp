#include "LawlJSON.h"
#include "LawlJSON_Lexer.h"

#include <assert.h>
#include <sstream>

BEGIN_LAWLJSON

#define BURN_COMMA if(TOKEN_COMMA == lexer.Token()) lexer.Next();

void ParseJSON_Helper( LJValue& result, LJLexer& lexer );

void ParseJSON_Array( LJValue& array, LJLexer& lexer )
{
	assert(array.IsArray());
	while(TOKEN_RSQBRACKET != lexer.Token())
	{
		array.array().push_back(LJValue());
		ParseJSON_Helper(array.array().back(), lexer);

		BURN_COMMA;
	}
	lexer.Next();
}

void ParseJSON_Object( LJValue& object, LJLexer& lexer )
{
	assert(object.IsObject());
	while(TOKEN_RBRACKET != lexer.Token())
	{
		if(TOKEN_STRING != lexer.Token())
		{
			throw LJException("expected string key for object");
		}
		LJString key = lexer.Data();
		lexer.Next();

		if(TOKEN_COLON != lexer.Token())
		{
			throw LJException("expected colon separator for object");
		}
		lexer.Next();

		object.object()[key] = LJValue();
		ParseJSON_Helper(object.object()[key], lexer);

		BURN_COMMA;
	}
	lexer.Next();
}

void ParseJSON_Helper( LJValue& result, LJLexer& lexer )
{
	LJTOKEN token = lexer.Token();
	switch(token)
	{
	case TOKEN_LSQBRACKET:
		result.SetArray();
		lexer.Next();
		ParseJSON_Array(result, lexer);
		break;
	case TOKEN_LBRACKET:
		result.SetObject();
		lexer.Next();
		ParseJSON_Object(result, lexer);
		break;
	case TOKEN_STRING:
		result = lexer.Data();
		lexer.Next();
		break;
	case TOKEN_NUMBER:
		result = lexer.Number();
		lexer.Next();
		break;
	case TOKEN_TRUE:
		result = true;
		lexer.Next();
		break;
	case TOKEN_FALSE:
		result = false;
		lexer.Next();
		break;
	case TOKEN_NULL:
		result.SetNull();
		lexer.Next();
		break;
	default:
		throw LJException("bad token encountered");
		break;
	}
}

void ParseJSON( const char* json, LJValue& result )
{
	assert(json);
	LJLexer lexer(json);
	return ParseJSON_Helper(result, lexer);
}

// Serialization functions
//

void Serialize(const LJString& string, LJString& result)
{
	result += "\"";

	size_t len = string.length();
	const char* cstr = string.c_str();
	for(size_t idx = 0; idx < len; ++idx)
	{
		char c = cstr[idx];

		switch(c)
		{
		case '\b':
			result += "\\b";
			break;
		case '\f':
			result += "\\f";
			break;
		case '\n':
			result += "\\n";
			break;
		case '\r':
			result += "\\r";
			break;
		case '\t':
			result += "\\t";
			break;
		case '"':
		case '/':
		case '\\':
			result += '\\';
		default:
			result += c;
		}
	}

	result += "\"";
}

void Serialize(const LJNumber& number, LJString& result)
{
	std::stringstream ss;
	ss << number;
	result += ss.str();
}

void Serialize(const LJObject& object, LJString& result)
{
	result += "{";

	for(LJObject::const_iterator entry = object.begin(); entry != object.end(); ++entry)
	{
		if(entry != object.begin())
			result += ",";

		Serialize((*entry).first, result);

		result += ":";

		Serialize((*entry).second, result);
	}

	result += "}";
}

void Serialize(const LJArray& array, LJString& result)
{
	result += "[";

	for(LJArray::const_iterator entry = array.begin(); entry != array.end(); ++entry)
	{
		if(entry != array.begin())
			result += ",";

		Serialize(*entry, result);
	}

	result += "]";
}

void Serialize(const LJBool& boolean, LJString& result)
{
	if(true == boolean)
		result += "true";
	else
		result += "false";
}

void Serialize(const LJValue& value, LJString& result)
{
	switch(value.type())
	{
	case LJ_STRING:
		Serialize(value.string(), result);
		break;
	case LJ_NUMBER:
		Serialize(value.number(), result);
		break;
	case LJ_OBJECT:
		Serialize(value.object(), result);
		break;
	case LJ_ARRAY:
		Serialize(value.array(), result);
		break;
	case LJ_BOOL:
		Serialize(value.boolean(), result);
		break;
	case LJ_NULL:
		result += "null";
		break;
	default:
		assert(false /* Should be one of LJType */);
	}
}

END_LAWLJSON