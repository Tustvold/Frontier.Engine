#include <gtest/gtest.h>
#include <FTEngine.h>
#include <Util/FTFileManager.h>
#include <Mock/MockLoader.h>
#include <chrono>
#include "Util/Serialization/Serialization.h"
#include <fstream>

struct TestStruct {
    std::vector<std::vector<int>> foo;
    std::vector<std::string> bar;
    std::unordered_map<int, std::string> foobar;

    template<typename T>
    void serialize(T &s) {
        s & foo;
        s & bar;
        s & foobar;
    }
};

TEST(TestBTF, TestNewAPI) {
    MockLoader loader;

    ttvfs::File *fp = FTEngine::getFileManager()->getOrCreateFile("Test.hex");
    fp->open("wb");

    const int num_tests = 1000;

    TestStruct t;

    std::vector<int> a;
    std::vector<int> b;
    for (int i = 0; i < num_tests; i++) {
        a.push_back(rand());
        b.push_back(rand());
    }

    t.foo.emplace_back(std::move(a));
    t.foo.emplace_back(std::move(b));

    t.foobar[rand()] = "asdf";
    t.foobar[rand()] = "asdfgs";
    t.foobar[rand()] = "afsghjwsjs";

    t.bar = {"Hello", "Helloasd", "Helloasfdg"};

    OutputSerializer out(fp);
    out & t;

    fp->close();

    fp->open("rb");

    InputSerializer in(fp);

    TestStruct t2;

    in & t2;

    for (int i = 0; i < num_tests; i++) {
        EXPECT_EQ(t.foo[0][i],t2.foo[0][i]);
        EXPECT_EQ(t.foo[1][i],t2.foo[1][i]);
    }

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(t.bar[i], t2.bar[i]);
    }

    for (auto& el : t.foobar) {
        EXPECT_EQ(t2.foobar[el.first], el.second);
    }
}