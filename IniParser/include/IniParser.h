#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <fstream>

#define DEBUG 

class IniParser {
public:
	IniParser();
	IniParser(const std::string& fileName);

private:

	std::string _filePath;
	std::string _iniString;
	std::ifstream _iniFile;

	/**
	 * \brief replaces the commented chars from \ref _iniString with ' '
	 */
	void removeComments();
	/**
	* \brief removes the \a char c from _iniString
	* \param c the char to remove
	*/
	void removeChar(char c);

	/**
	* \brief removes blank lines
	*/
	void removeBlankLines();

};

#endif
