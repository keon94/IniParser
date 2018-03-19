#ifndef INI_PARSER_EXCEPTION_H
#define INI_PARSER_EXCEPTION_H

#include <string>

class IniParserException : public std::exception {

public:
	
	IniParserException(const std::string& message);

};

#endif