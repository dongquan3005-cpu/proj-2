#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

TEST(CleanToken, PunctuationBothEnds) {
  string input = "!!Hello!!";
  EXPECT_THAT(cleanToken(input), StrEq("hello")) << "input=\"" << input << "\"";
}

TEST(CleanToken, PunctuationInMiddle) {
  string input = "co-op";
  EXPECT_THAT(cleanToken(input), StrEq("co-op")) << "input=\"" << input << "\"";
}
TEST(CleanToken, OnlyNumbers) {
  string input = "12345";
  EXPECT_THAT(cleanToken(input), StrEq("")) << "input=\"" << input << "\"";
}
TEST(CleanToken, SingleLetter) {
  string input = "X";
  EXPECT_THAT(cleanToken(input), StrEq("x")) << "input=\"" << input << "\"";
}
TEST(CleanToken, ManyPunctuation) {
  string input = "......a......";
  EXPECT_THAT(cleanToken(input), StrEq("a")) << "input=\"" << input << "\"";
}
TEST(CleanToken, NumbersAreNotPunctuation) {
  string input = "1.abc.1";
  EXPECT_THAT(cleanToken(input), StrEq("1.abc.1"))
      << "input=\"" << input << "\"";
}

TEST(GatherToken, LeadingSpaces) {
  string text = "   to be or not to be";
  set<string> expected = {"to", "be", "or", "not"};
  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherToken, TrailingSpaces) {
  string text = "to be or not to be   ";
  set<string> expected = {"to", "be", "or", "not"};
  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherToken, MultipleSpacesBetweenWords) {
  string text = "to   be  or      not   to   be";
  set<string> expected = {"to", "be", "or", "not"};
  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}
