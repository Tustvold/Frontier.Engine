#include <Mock/MockLoader.h>
#include <Util/FTStringUtils.h>


TEST(TestStringUtils, TestConversion) {
    const std::string a = "Foo";
    const std::wstring wa = L"Foo";

    auto converted = FTStringUtil<char>::convertString(wa);
    EXPECT_EQ(converted, a);

    auto converted2 = FTStringUtil<wchar_t>::convertString(a);
    EXPECT_EQ(converted2, wa);
}

TEST(TestStringUtils, TestConversionLong) {
    const std::string a = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec a diam lectus. Sed sit amet ipsum mauris. Maecenas congue ligula ac quam viverra nec consectetur ante hendrerit. Donec et mollis dolor. Praesent et diam eget libero egestas mattis sit amet vitae augue. Nam tincidunt congue enim, ut porta lorem lacinia consectetur.";
    const std::wstring wa = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec a diam lectus. Sed sit amet ipsum mauris. Maecenas congue ligula ac quam viverra nec consectetur ante hendrerit. Donec et mollis dolor. Praesent et diam eget libero egestas mattis sit amet vitae augue. Nam tincidunt congue enim, ut porta lorem lacinia consectetur.";

    auto converted = FTStringUtil<char>::convertString(wa);
    EXPECT_EQ(converted, a);

    auto converted2 = FTStringUtil<wchar_t>::convertString(a);
    EXPECT_EQ(converted2, wa);
}

