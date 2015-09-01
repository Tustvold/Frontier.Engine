#include "gtest/gtest.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// Memory leak detector from https://github.com/ymx/gtest_mem
class MemoryLeakDetector : public testing::EmptyTestEventListener {

public:
	virtual void OnTestStart(const testing::TestInfo&) override {
		_CrtMemCheckpoint(&memState_);
	}

	virtual void OnTestEnd(const testing::TestInfo& test_info) override {
		if (test_info.result()->Passed())
		{
			_CrtMemState stateNow, stateDiff;
			_CrtMemCheckpoint(&stateNow);
			int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
			if (diffResult)
			{
				FAIL() << "Memory leak of " << stateDiff.lSizes[1] << " byte(s) detected.";
			}
		}
	}

private:
	_CrtMemState memState_;
};


#endif

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

#ifdef _WIN32
	testing::UnitTest::GetInstance()->listeners().Append(new MemoryLeakDetector());
#endif

	return RUN_ALL_TESTS();

}