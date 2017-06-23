#include <gtest/gtest.h>
#include <Engine.h>
#include <IO/FileManager.h>
#include <Mock/MockLoader.h>
#include <chrono>
#include "IO/Serialization/Serialization.h"
#include <fstream>

USING_NS_FT

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

    ttvfs::File *fp = Engine::getFileManager()->getOrCreateFile("Test.hex");
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


struct TestStruct2 {
    std::vector<std::vector<int>> foo;
    std::vector<std::string> bar;
    std::unordered_map<int, std::string> foobar;
    int bas[5];
    uint32_t length;
    int* var_array;
};

template <typename Archiver>
struct Serializer <Archiver, TestStruct2> {
    static void serialize(Archiver &s, TestStruct2 &val) {
        s & val.foo;
        s & val.bar;
        s & val.foobar;
        s & val.bas;
        s & val.length;
        if (Archiver::is_input) {
            val.var_array = new int[val.length];
        }
        s.serializePrimitiveArray(val.var_array, val.length);
    }
};

TEST(TestBTF, TestNewAPI2) {
    MockLoader loader;

    ttvfs::File *fp = Engine::getFileManager()->getOrCreateFile("Test.hex");
    fp->open("wb");

    const int num_tests = 1000;

    TestStruct2 t;

    t.length = 100;
    t.var_array = new int[100];

    for (int i = 0; i < 100; i++)
        t.var_array[i] = rand();

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

    for (int i = 0; i < 5; i++)
        t.bas[i] = rand();

    t.bar = {"Hello", "Helloasd", "Helloasfdg"};

    OutputSerializer out(fp);
    out & t;

    fp->close();

    fp->open("rb");

    InputSerializer in(fp);

    TestStruct2 t2;

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

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(t.bas[i], t2.bas[i]);
    }

    delete [] t.var_array;
    delete [] t2.var_array;
}