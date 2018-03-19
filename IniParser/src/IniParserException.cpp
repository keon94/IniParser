#include "IniParserException.h"

IniParserException::IniParserException(const std::string & message) : exception(message.c_str()) {}

