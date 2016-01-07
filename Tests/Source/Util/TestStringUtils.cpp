#include <Mock/MockLoader.h>
#include <Util/FTStringUtils.h>


TEST(TestStringUtils, TestConversion) {
    const std::string a = "Foo";
    const std::wstring wa = L"Foo";

    auto converted = FTStringUtil<wchar_t>::convertString(wa);
    EXPECT_EQ(converted, a);

    auto converted2 = FTStringUtil<char>::convertString(a);
    EXPECT_EQ(converted2, wa);
}

