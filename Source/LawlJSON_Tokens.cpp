#include "LawlJSON_Tokens.h"

BEGIN_LAWLJSON

LJString Tok2str(LJTOKEN token)
{
#define TOKCASE(T, S) case (T): return (S); break;
	switch(token) {
		TOKCASE(TOKEN_LSQBRACKET, "[");
		TOKCASE(TOKEN_RSQBRACKET, "]");
		TOKCASE(TOKEN_LBRACKET, "{");
		TOKCASE(TOKEN_RBRACKET, "}");
		TOKCASE(TOKEN_COLON, ":");
		TOKCASE(TOKEN_COMMA, ",");
		TOKCASE(TOKEN_NUMBER, "number");
		TOKCASE(TOKEN_TRUE, "true");
		TOKCASE(TOKEN_FALSE, "false");
		TOKCASE(TOKEN_NULL, "null");
		TOKCASE(TOKEN_STRING, "string");
		TOKCASE(TOKEN_EOF, "eof");
	};
#undef TOKCASE
	return "oops";
}

END_LAWLJSON