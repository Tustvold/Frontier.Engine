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

TEST(TestStringUtils, TestToLowerCase) {
    std::string a = "LfgewfJUsfSnfhgKedfhS";
    std::wstring b = L"LfgewfJUsfSnfhgKedfhS";

    FTStringUtil<char>::toLowerCase(a);
    FTStringUtil<wchar_t>::toLowerCase(b);

    EXPECT_EQ(a, "lfgewfjusfsnfhgkedfhs");
    EXPECT_EQ(b, L"lfgewfjusfsnfhgkedfhs");
}

TEST(TestStringUtils, TestReplace) {
    std::string a = "asd\n dkfks grfesasd\nghs djgfjgawjx";
    std::wstring b = L"asd\n dkfks grfesasd\nghs djgfjgawjx";

    FTStringUtil<char>::replaceAll(a, "asd\n", "foo");
    FTStringUtil<wchar_t>::replaceAll(b, L"asd\n", L"foo");

    EXPECT_EQ(a, "foo dkfks grfesfooghs djgfjgawjx");
    EXPECT_EQ(b, L"foo dkfks grfesfooghs djgfjgawjx");
}


TEST(TestStringUtils, TestSplit) {
    std::string a = "asda,gusef, sadf,y \n,sdfsd";
    std::wstring b = L"asda,gusef, sadf,y \n,sdfsd";

    auto av = FTStringUtil<char>::splitString(a, ',');
    auto bv = FTStringUtil<wchar_t>::splitString(b, ',');

    std::vector<std::string> av_correct = { "asda","gusef"," sadf","y \n","sdfsd" };
    std::vector<std::wstring> bv_correct = { L"asda",L"gusef",L" sadf",L"y \n",L"sdfsd" };

    EXPECT_EQ(av.size(), av_correct.size());
    EXPECT_EQ(bv.size(), bv_correct.size());
    EXPECT_EQ(av.size(), bv.size());

    for (int i = 0; i < av.size(); i++) {
        EXPECT_EQ(av[i], av_correct[i]);
        EXPECT_EQ(bv[i], bv_correct[i]);
    }
}