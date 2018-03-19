#include "IniParser.h"
#include "IniParserException.h"
#include "gtest\gtest.h"
#include <fstream>

class IniParserTestsFixture : public ::testing::Test {

protected:
	virtual void SetUp() override;

	virtual void TearDown() override;

private: 

	const std::string _FILE_NAME = "configTest.ini";
	std::ofstream _outFile;
};

void IniParserTestsFixture::SetUp() {
	_outFile.open(_FILE_NAME);
	if (!_outFile.is_open())
		FAIL() << _FILE_NAME + " could not be opened.\n";
	_outFile <<
		"[SECTION1]\n" <<
		"Key1=Value1\n" <<
		"Key2 =Val2\n" <<
		"Key3= Val3\n" <<
		" \n" <<
		"[SECTION2]\n" <<
		"Key1 = \n" <<
		std::flush;
	_outFile.close();
}

void IniParserTestsFixture::TearDown() {
	//std::remove(_FILE_NAME.c_str());
}

TEST_F(IniParserTestsFixture, NoIniFileExceptionTest) {
	ASSERT_THROW(IniParser("abc.ini"), IniParserException);
}