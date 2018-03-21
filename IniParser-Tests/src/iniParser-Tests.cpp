#include "IniParser.h"
#include "IniParserException.h"
#include "gtest\gtest.h"
#include <fstream>
#include <filesystem>


class IniParserTestsFixture : public ::testing::Test {

protected:
	
	virtual void SetUp() override;

	virtual void TearDown() override;

	const std::string _FILE_NAME = "IniParser-Tests/configTest.ini";

	std::string& _FILE_PATH = _m_FILE_PATH;;

private: 

	std::string _m_FILE_PATH;

	std::ofstream _outFile;
};

void IniParserTestsFixture::SetUp() {

	_m_FILE_PATH = std::experimental::filesystem::current_path().parent_path().generic_string() + "/" + _FILE_NAME;
	_outFile.open(_m_FILE_PATH);
	if (!_outFile.is_open())
		FAIL() << _m_FILE_PATH + " could not be created.\n";
	_outFile <<
		"# comment\\##   #comment#\n" <<
		"[SECTION1]\n" <<
		"Key1=Value1 #comment1#\n" <<
		"#comment2  \n " <<
		"\n" <<
		"Key2 =Val2\n" <<
		"Key3= Val3\n" <<
		" \n" <<
		"[SECTION2]\n" <<
		"Key1 = \n" <<
		"Key2=val2\n" <<
		" \n" <<
		"\n" <<
		"#comment \\# comment\n" <<
		"key3 = val3" <<
		std::flush;
	_outFile.close();
}

void IniParserTestsFixture::TearDown() {
	//std::remove(_FILE_NAME.c_str());
}

TEST_F(IniParserTestsFixture, NoIniFileExceptionTest) {
	ASSERT_THROW(IniParser("abc.ini"), IniParserException);
}

TEST_F(IniParserTestsFixture, Test2) {
	IniParser iniParser;
	ASSERT_NO_THROW(iniParser = IniParser(_FILE_NAME));
}