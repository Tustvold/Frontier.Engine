#include <Util/BTF/Tag.h>
#include <gtest/gtest.h>
#include <FTEngine.h>
#include <Util/FTFileManager.h>
#include <Mock/MockLoader.h>
#include <chrono>
#include "Util/Serialization/Serialization.h"
#include <fstream>

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