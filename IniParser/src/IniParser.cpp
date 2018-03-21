#include "IniParser.h"
#include "IniParserException.h"
#include <algorithm>
#include <filesystem>
#include <vld.h>


#if DEBUG 1
#include <iostream>
#endif

#define OPTIMIZED 1

IniParser::IniParser() {}

IniParser::IniParser(const std::string& fileName)
{
	const std::string solutionDir = std::experimental::filesystem::current_path().parent_path().generic_string() + "/";
	_filePath = solutionDir + fileName;
	_iniFile.open(_filePath);
	if (!_iniFile.is_open())
		throw IniParserException(_filePath + " could not be opened.\n");
	
	_iniFile.seekg(0, std::ios::end);
	size_t size = _iniFile.tellg();
	_iniString = std::string(size, ' ');
	_iniFile.seekg(0);
	_iniFile.read(&_iniString[0], size);

	removeComments();
	removeChar(' ');
	removeBlankLines();


#if DEBUG 1
	std::cout << _iniString << std::endl;
#endif

}

void IniParser::removeChar(char c) {
	_iniString.erase(std::remove(_iniString.begin(), _iniString.end(), c), _iniString.end());
}

void IniParser::removeComments() {	
	
	const char* end = &_iniString[_iniString.length()-1];
	
	bool inCommentBlock = false;
	char* c = &_iniString[0];

	for (; c != end; ++c) {
		if (inCommentBlock) {
			if (*c == '\n') //end of line of the comment
				inCommentBlock = false;
			else if (*c == '\\' && *(c + 1) == '#') { // \# was used in the comment
				*c = ' ';
				*(++c) = ' ';
				continue;
			}
			else
				*c = ' ';
		}
		if (*c == '#') {
			inCommentBlock = !inCommentBlock;
			*c = ' ';
		}
	}
	if (*c == '#') {
		*c = ' ';
	}

}

#if DEBUG 1
void printArray(const char* str, const unsigned int size, const char* message = nullptr) {
	std::cout << "\n------------" + std::string(message ? message : "") + "------------------\n";
	for (int i = 0; i < size; ++i)
		std::cout << str[i];
	std::cout << "\n------------------------------\n";
}
#endif

#if !OPTIMIZED
void IniParser::removeBlankLines() {
#if DEBUG 1
	printArray(_iniString.c_str(), _iniString.length());
#endif
	char* prunedString = (char*)malloc(_iniString.length()*sizeof(char));
	char* prunedStringIter = &prunedString[0];
	char* _iniStringIter = &_iniString[0];
	//get rid of all blank lines on top of file
	while (*_iniStringIter == '\n') {
		++_iniStringIter;
	}
	bool consecutiveBlankLinesFound = false;
	//while not eof
	while( *(_iniStringIter + 1) != '\0' ) {
		//if \n\n found
		if (*_iniStringIter == '\n' && *(_iniStringIter + 1) == '\n') {
			if(!consecutiveBlankLinesFound)
				*prunedStringIter = '\n';
			consecutiveBlankLinesFound = true;
		}
		else {
			consecutiveBlankLinesFound = false;
			*prunedStringIter = *_iniStringIter;
			++prunedStringIter;
		}
		++_iniStringIter;
	}
	*prunedStringIter = '\0';
	prunedString = (char*)realloc(prunedString, prunedStringIter - prunedString + 1);
	_iniString = prunedString;
	free(prunedString);
#if DEBUG 1
	printArray(_iniString.c_str(), _iniString.length());
#endif
}

#else
void IniParser::removeBlankLines() {
#if DEBUG 1
	printArray(_iniString.c_str(), _iniString.length());
#endif
	char* _iniStringIter = &_iniString[0];
	char* prunedStringIter = _iniStringIter;
	
	//get rid of all blank lines on top of file
	while (*_iniStringIter == '\n') {
		++_iniStringIter;
	}
	bool consecutiveBlankLinesFound = false;
	//while not eof
	while (*(_iniStringIter + 1) != '\0') {
		//if \n\n found
		if (*_iniStringIter == '\n' && *(_iniStringIter + 1) == '\n') {
			if (!consecutiveBlankLinesFound) {
				*prunedStringIter = '\n';
			}
			consecutiveBlankLinesFound = true;
		}
		else {
			consecutiveBlankLinesFound = false;
			*prunedStringIter = *_iniStringIter;
			++prunedStringIter;
		}
		++_iniStringIter;
	}
	if(*_iniStringIter != '\n');
		*prunedStringIter = *_iniStringIter;

	_iniString = _iniString.substr(0, prunedStringIter-&_iniString[0]+1);
#if DEBUG 1
	printArray(_iniString.c_str(), _iniString.length());
#endif
}
#endif