#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <fstream>

class IniParser {
public:
	IniParser();
	IniParser(const std::string& fileName);

private:

	std::string _fileName;
	std::ifstream _iniFile;

};

#endif
