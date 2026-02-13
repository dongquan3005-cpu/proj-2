#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

TEST(CleanTokens, PunctuationBothEnds) {
  string input = "!!Hello!!";
  EXPECT_THAT(cleanToken(input), StrEq("hello")) << "input=\"" << input << "\"";
}

TEST(CleanTokens, PunctuationInMiddle) {
  string input = "co-op";
  EXPECT_THAT(cleanToken(input), StrEq("co-op")) << "input=\"" << input << "\"";
}
TEST(CleanTokens, OnlyNumbers) {
  string input = "12345";
  EXPECT_THAT(cleanToken(input), StrEq("")) << "input=\"" << input << "\"";
}
TEST(CleanTokens, SingleLetter) {
  string input = "X";
  EXPECT_THAT(cleanToken(input), StrEq("x")) << "input=\"" << input << "\"";
}
TEST(CleanTokens, ManyPunctuation) {
  string input = "......a......";
  EXPECT_THAT(cleanToken(input), StrEq("a")) << "input=\"" << input << "\"";
}
TEST(CleanTokens, NumbersAreNotPunctuation) {
  string input = "1.abc.1";
  EXPECT_THAT(cleanToken(input), StrEq("1.abc.1"))
      << "input=\"" << input << "\"";
}

TEST(GatherTokens, LeadingSpaces) {
  string text = "   to be or not to be";
  set<string> expected = {"to", "be", "or", "not"};
  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, TrailingSpaces) {
  string text = "to be or not to be   ";
  set<string> expected = {"to", "be", "or", "not"};
  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, MultipleSpacesBetweenWords) {
  string text = "to   be  or      not   to   be";
  set<string> expected = {"to", "be", "or", "not"};
  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(buildIndex, FileNotFoundReturnsZero) {
  map<string, set<string>> index;
  int page = buildIndex("this_file_does_not_exist.txt", index);
  EXPECT_THAT(page, Eq(0));
  EXPECT_TRUE(index.empty());
}

TEST(buildIndex, TinyFilePageCountAndSomeWords) {
  map<string, set<string>> index;
  int page = buildIndex("data/tiny.txt", index);
  EXPECT_THAT(page, Eq(4));
  EXPECT_TRUE(index.count("milk"));
  EXPECT_TRUE(index.count("eggs"));
  EXPECT_FALSE(index["milk"].empty());
  EXPECT_FALSE(index["eggs"].empty());
}
