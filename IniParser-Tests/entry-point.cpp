#include <gmock\gmock.h>


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	const int status = RUN_ALL_TESTS();
	std::cin.get();
	return status;
}

