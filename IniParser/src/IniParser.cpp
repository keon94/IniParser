#include "IniParser.h"
#include "IniParserException.h"

IniParser::IniParser() {}

IniParser::IniParser(const std::string& fileName) : _fileName(fileName)
{
	_iniFile.open(_fileName);	
	if (!_iniFile.is_open())
		throw IniParserException(_fileName + " was not opened.\n");
}
