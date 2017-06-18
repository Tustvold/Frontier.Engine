#include <Util/BTF/Tag.h>
#include <gtest/gtest.h>
#include <FTEngine.h>
#include <Util/FTFileManager.h>
#include <Mock/MockLoader.h>
#include <chrono>
#include "Util/BTF/Serialization.h"

TEST(TestBTF, BigTest) {
    MockLoader loader;

    auto master = new Tag(Tag::TAG_Compound);

    auto nestedCompound = new Tag(Tag::TAG_Compound);
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(nestedCompound), 1);

    auto egg = new Tag(Tag::TAG_Compound);
    nestedCompound->payload_tagCompound->addTag(std::unique_ptr<Tag>(egg), 1);

    auto name = new Tag(Tag::TAG_String);
    name->payload_string->data = "Eggbert";
    egg->payload_tagCompound->addTag(std::unique_ptr<Tag>(name), 1);
    auto value = new Tag(Tag::TAG_Float);
    value->payload_float = 0.5f;
    egg->payload_tagCompound->addTag(std::unique_ptr<Tag>(value), 2);

    auto ham = new Tag(Tag::TAG_Compound);
    nestedCompound->payload_tagCompound->addTag(std::unique_ptr<Tag>(ham), 2);

    auto name2 = new Tag(Tag::TAG_String);
    name2->payload_string->data = "Hampus";
    ham->payload_tagCompound->addTag(std::unique_ptr<Tag>(name2), 1);
    auto value2 = new Tag(Tag::TAG_Float);
    value2->payload_float = 0.75f;
    ham->payload_tagCompound->addTag(std::unique_ptr<Tag>(value2), 2);

    auto shortTest = new Tag(Tag::TAG_Int16);
    shortTest->payload_short = 32345;
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(shortTest), 2);

    auto intTest = new Tag(Tag::TAG_Int32);
    intTest->payload_int = 2147483647;
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(intTest), 3);

    auto byteTest = new Tag(Tag::TAG_Byte);
    byteTest->payload_int = 127;
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(byteTest), 4);

    auto stringTest = new Tag(Tag::TAG_String);
    stringTest->payload_string->data = "HELLO WORLD THIS IS A TEST STRING";
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(stringTest), 5);

    auto listTest = new Tag(Tag::TAG_List);
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(listTest), 6);

    auto intTest1 = new Tag(Tag::TAG_Int32);
    intTest1->payload_int = 11;
    listTest->payload_tagList->addTag(std::unique_ptr<Tag>(intTest1));

    auto intTest2 = new Tag(Tag::TAG_Int32);
    intTest2->payload_int = 12;
    listTest->payload_tagList->addTag(std::unique_ptr<Tag>(intTest2));

    auto intTest3 = new Tag(Tag::TAG_Int32);
    intTest3->payload_int = 13;
    listTest->payload_tagList->addTag(std::unique_ptr<Tag>(intTest3));

    auto intTest4 = new Tag(Tag::TAG_Int32);
    intTest4->payload_int = 14;
    listTest->payload_tagList->addTag(std::unique_ptr<Tag>(intTest4));

    auto intTest5 = new Tag(Tag::TAG_Int32);
    intTest5->payload_int = 15;
    listTest->payload_tagList->addTag(std::unique_ptr<Tag>(intTest5));

    auto floatTest = new Tag(Tag::TAG_Float);
    floatTest->payload_float = 0.49823147058486938f;
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(floatTest), 7);

    auto compoundListTest = new Tag(Tag::TAG_List);
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(compoundListTest), 8);

    auto tagComp1 = new Tag(Tag::TAG_Compound);
    compoundListTest->payload_tagList->addTag(std::unique_ptr<Tag>(tagComp1));

    auto floatTest1 = new Tag(Tag::TAG_Float);
    floatTest1->payload_float = 20.54f;
    tagComp1->payload_tagCompound->addTag(std::unique_ptr<Tag>(floatTest1), 1);

    auto stringTest1 = new Tag(Tag::TAG_String);
    stringTest1->payload_string->data = "Compound #1";
    tagComp1->payload_tagCompound->addTag(std::unique_ptr<Tag>(stringTest1), 2);

    auto tagComp2 = new Tag(Tag::TAG_Compound);
    compoundListTest->payload_tagList->addTag(std::unique_ptr<Tag>(tagComp2));

    auto floatTest2 = new Tag(Tag::TAG_Float);
    floatTest2->payload_float = 21.54f;
    tagComp2->payload_tagCompound->addTag(std::unique_ptr<Tag>(floatTest2), 1);

    auto stringTest2 = new Tag(Tag::TAG_String);
    stringTest2->payload_string->data = "Compound #2";
    tagComp2->payload_tagCompound->addTag(std::unique_ptr<Tag>(stringTest2), 2);


    auto byteArray = new Tag(Tag::TAG_Byte_Array);
    byteArray->payload_byteArray->data.resize(10);
    for (int i = 0; i < 10; i++)
        byteArray->payload_byteArray->data[i] = (uint8_t) ((i * i * 255 + i * 7) % 100);
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(byteArray), 9);

    auto ubyteTest = new Tag(Tag::TAG_UByte);
    ubyteTest->payload_ubyte = 232;
    master->payload_tagCompound->addTag(std::unique_ptr<Tag>(ubyteTest), 10);

    std::stringstream out_ss;
    master->logStructure(out_ss);

    FTLOG("\n%s", out_ss.str().c_str());

    auto buffer = std::make_unique<CompressionBuffer>();

    master->writeToBuffer(buffer.get());

    remove("TestResources/btf-output");
    ttvfs::File *fp = FTEngine::getFileManager()->getOrCreateFile("TestResources/btf-output");
    fp->open("wb");
    buffer->writeFile(fp);
    fp->close();

    delete master;

    ttvfs::File *fr = FTEngine::getFileManager()->getOrCreateFile("TestResources/btf-output");
    fr->open("r");
    auto readBuffer = CompressionBuffer::readFile(fr);
    fr->close();

    std::stringstream in_ss;

    auto readMaster = new Tag(readBuffer.get());
    readMaster->logStructure(in_ss);

    delete readMaster;

    EXPECT_STREQ(in_ss.str().c_str(), out_ss.str().c_str());
}

TEST(TestBTF, TestNewAPI) {
    Buffer *buffer = new Buffer();

    std::vector<int> foo({23, 52, 14, 56});

    std::vector<std::vector<int>> foo2({{23, 52, 14, 56},
                                        {23, 52, 14, 56}});

    OutputSerializer out(buffer);
    out & foo2;
    out & foo2;

    buffer->seek(0);

    InputSerializer in(buffer);

    std::vector<std::vector<int>> foo3;
    std::vector<std::vector<int>> foo4;

    in & foo3;
    in & foo4;

    for (auto& a : foo3)
        for (auto& b : a)
            printf("%i\n", b);

    printf("Asd\n");

    for (auto& a : foo4)
        for (auto& b : a)
            printf("%i\n", b);

    delete buffer;

}
//
//TEST(TestBTF, TestNewAPI2) {
//    Buffer *buffer = new Buffer();
//
//    std::vector<std::string> foo({"Hello", "Helloasd", "Helloasfdg"});
//
//    TagBase::write(foo, buffer);
//
//    buffer->seek(0);
//    auto bar = TagBase::read<std::vector<std::string>>(buffer);
//
//    delete buffer;
//
//}
//
//TEST(TestBTF, TestNewAPI3) {
//    Buffer *buffer = new Buffer();
//
//    std::vector<std::string> foo({"Hello", "Helloasd", "Helloasfdg"});
//
//    std::vector<int> foo2({23, 52, 14, 56});
//
//    std::tuple<std::vector<std::string>, std::vector<int>> foo3 = std::make_pair(foo, foo2);
//
//    TagBase::write(foo3, buffer);
//
//    buffer->seek(0);
//    auto bar = TagBase::read<std::tuple<std::vector<std::string>, std::vector<int>>>(buffer);
//
//    delete buffer;
//
//}
//
//struct CustomTest {
//    std::vector<float> a;
//    float b;
//
//    CustomTest(const std::vector<float> &a, float b) : a(a), b(b) {}
//
//    CustomTest(std::vector<float> &&a, float b) : a(std::move(a)), b(b) {}
//};
//
//TEST(TestBTF, TestNewAPI4) {
//
//    Buffer *buffer = new Buffer();
//
//    std::vector<float> foo;
//    for (int i = 0; i < 10000; i++)
//        foo.push_back(rand());
//
//
//    std::unordered_map<std::string, std::vector<float>> map_test = {{"Hello", foo},
//                                                                    {"foo",   foo}};
//
//
//    TagBase::write(map_test, buffer);
//
//    buffer->seek(0);
//    auto begin = std::chrono::high_resolution_clock::now();
//
//    auto bar = TagBase::read<std::unordered_map<std::string, std::vector<float>>>(buffer);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    delete buffer;
//
//    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
//
//}