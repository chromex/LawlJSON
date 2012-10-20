#ifndef LAWLJSON_EXCEPTION_H
#define LAWLJSON_EXCEPTION_H

#include <exception>

class LJException : public std::exception 
{
public:
	LJException() throw() : _what("") {}
	LJException(const char* w) throw() : _what(w) {}
	~LJException() throw() {}
	
	virtual const char* what() const throw() {return _what.c_str();}
	
private:
	std::string _what;
};

#endif
