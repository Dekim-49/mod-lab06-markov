// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include "textgen.h"

class GenerateTest : public testing::Test {
protected:
    Generate generate;
};
TEST(GenerateTest, Prefix) {
    Generate generate;

    std::string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    generate.CreateTable(text, prefixLength);

    Generate::prefix pprefix = { "Once", "there" };

    EXPECT_NE(generate.statetab.find(pprefix), generate.statetab.end());
}
TEST(GenerateTest, Prefix_Suffix) {
    Generate generate;

    std::string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    generate.CreateTable(text, prefixLength);

    Generate::prefix pprefix = { "Once", "there" };

    EXPECT_EQ(generate.statetab[pprefix][0], "lived");
}
TEST(GenerateTest, OnceSuffix) {
    Generate generate;

    std::string text = "Once there lived an old man and old woman";
    int prefixLength = 2;
    generate.CreateTable(text, prefixLength);

    int maxgen = 9;
    std::string result = generate.GenerateText(maxgen, 3);

    EXPECT_EQ(result, "Once there lived");
}
TEST(GenerateTest, VectorSuffix) {
    Generate generate;

    std::string text = "qwe rty uio a qwe rty uio b qwe rty uio c";
    int prefixLength = 2;
    generate.CreateTable(text, prefixLength);
    
    int maxgen = 14;

    
    std::string result = generate.GenerateText(maxgen, 302);

    EXPECT_EQ(result, "qwe rty uio c ");
}

TEST(GenerateTest, Table) {
    Generate generate;

    std::string text = "qwe rty uio a qwe rty uio b qwe rty uio c";
    int prefixLength = 2;
    int maxgen = 14;
    std::map< Generate::prefix, std::vector<std::string>> Statetab = {
        {{"qwe", "rty"}, {"uio"}},
        {{"rty", "uio"}, {"a", "b"}},
        {{"uio", "a"}, {"qwe"}},
        {{"a", "qwe"}, {"rty"}}
    };

    generate.trainFromStateTable(Statetab);
    std::string result = generate.GenerateText(maxgen, 302);


    EXPECT_EQ(result, "qwe rty uio c");
}

